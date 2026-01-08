#include <iostream>
#include <thread>
#include <future> 
#include <chrono>

// La funcion que queremos ejecutar de forma asincrona
long long calcular_factorial(int n) {
    if (n < 0) return 0;
    long long res = 1;
    for (int i = 2; i <= n; ++i) {
        res *= i;
    }
    std::cout << "Hilo Trabajador: Factorial de " << n << " calculado." << std::endl;
    return res;
}

int main() {
    std::cout << "--- Inicio del Programa con std::async ---" << std::endl;

    // TODO: Llama a std::async para ejecutar calcular_factorial(10) en un hilo nuevo.
    // Pista: Usa std::launch::async como primer argumento para forzar el hilo.
    
    // TU CÓDIGO AQUÍ:
    std::future<long long> futuro = std::async(std::launch::async, calcular_factorial, 10);
    
    
    // El hilo principal puede hacer otras cosas mientras calcula...
    std::cout << "Hilo Principal: Tarea principal en curso..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 

    std::cout << "Hilo Principal: Llamando a futuro.get()..." << std::endl;
    
    // 2. Bloquea y obtiene el resultado
    long long resultado = futuro.get(); 

    std::cout << "Resultado Final (10!): " << resultado << std::endl;

    // Nota: ¡No necesitas ni thread.join() ni promise.set_value()!
    // std::async hace toda la limpieza por vos.
    
    std::cout << "\n--- Fin del Programa ---" << std::endl;
    return 0;
}