#include <iostream>
#include <thread>
#include <future>   // Para std::future y std::promise
#include <chrono>
#include <stdexcept>

// --- 1. La Tarea del Hilo (El Productor) ---
// Esta funcion recibe la promesa (el mecanismo para establecer el valor).
void calcular_asincrono(int a, int b, std::promise<int>& promesa) {
    try {
        std::cout << "Hilo Trabajador: Iniciando calculo (" << a << " * " << b << ")." << std::endl;
        
        // Simular un trabajo largo
        std::this_thread::sleep_for(std::chrono::seconds(2)); 

        if (b == 0) {
            // Lanza una excepcion localmente
            throw std::runtime_error("No se permiten multiplicaciones por cero.");
        }

        int resultado = a * b;
        
        // TODO: Usa el objeto 'promesa' para ESTABLECER el resultado
        // Pista: El método para guardar el valor es set_value()
        
        // TU CÓDIGO AQUÍ:
        promesa.set_value(resultado);
        
        std::cout << "Hilo Trabajador: Resultado establecido en la promesa." << std::endl;

    } catch (...) {
        // MUY IMPORTANTE: Si ocurre una excepcion en el hilo, DEBEMOS pasarla
        // a la promesa para que el 'future' en el hilo principal pueda capturarla.
        // Pista: Usa el metodo set_exception() con la excepcion actual.
        try {
            promesa.set_exception(std::current_exception());
        } catch (...) {} // Evitar cualquier excepción adicional
    }
}

int main() {
    std::cout << "--- Inicio del Programa con std::future/std::promise ---" << std::endl;

    // 1. Crear el objeto std::promise (el contenedor donde se guardará el resultado)
    std::promise<int> promesa_resultado;

    // 2. Obtener el std::future asociado a la promesa (el boleto para acceder al resultado)
    std::future<int> futuro = promesa_resultado.get_future();

    // 3. Lanzar el hilo, pasando la promesa por referencia
    std::thread t1(calcular_asincrono, 15, 20, std::ref(promesa_resultado));
    
    // El hilo principal puede seguir haciendo otras cosas
    std::cout << "Hilo Principal: El calculo esta en curso. Esperando..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 

    try {
        // 4. Obtener el valor: future.get() BLOQUEA el hilo hasta que el valor es establecido
        // (es decir, hasta que calcular_asincrono llama a set_value()).
        std::cout << "Hilo Principal: Llamando a futuro.get() para obtener el resultado..." << std::endl;
        int valor_final = futuro.get();

        std::cout << "Hilo Principal: Resultado Final Obtenido: " << valor_final << std::endl;

    } catch (const std::exception& e) {
        // Captura cualquier excepcion que haya sido pasada desde el hilo trabajador
        std::cerr << "\n!!! ERROR CAPTURADO DESDE HILO TRABAJADOR: " << e.what() << std::endl;
    }

    t1.join(); // Esperar a que el hilo termine su ejecución (limpieza)
    std::cout << "\n--- Fin del Programa ---" << std::endl;
    return 0;
}