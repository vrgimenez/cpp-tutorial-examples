#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

int contador = 0;
std::mutex mtx; // El candado que debe proteger el recurso

const int NUM_HILOS = 10;
const int INCREMENTOS_POR_HILO = 20000;
const int RESULTADO_ESPERADO = NUM_HILOS * INCREMENTOS_POR_HILO; // 200,000

void incrementar_inseguro() {
    for (int i = 0; i < INCREMENTOS_POR_HILO; ++i) {
        // ERROR: Condición de Carrera
        // El incremento no es atómico; la lectura y escritura pueden ser interrumpidas.
        contador++; 
    }
}

void incrementar_seguro() {
    for (int i = 0; i < INCREMENTOS_POR_HILO; ++i) {
        // TODO: Usa std::lock_guard para proteger el contador
        // Pista: Bloquea el mutex aquí (mtx) usando lock_guard

        // Implementa aquí la protección RAII del mutex
        std::lock_guard<std::mutex> lock(mtx);

        contador++; 
        
        // El mutex se libera automáticamente al salir del ámbito del lock_guard
    }
}

int main() {
    std::vector<std::thread> hilos;
    std::cout << "Resultado esperado: " << RESULTADO_ESPERADO << std::endl;

    // Ejecuta la prueba insegura (condición de carrera)
    std::cout << "\n--- Ejecutando Prueba INSEGURA ---" << std::endl;
    contador = 0;
    for (int i = 0; i < NUM_HILOS; ++i) {
        hilos.emplace_back(incrementar_inseguro);
    }
    for (auto& h : hilos) h.join();
    std::cout << "Resultado INSEGURO: " << contador << " (ERROR)" << std::endl;
    hilos.clear();
    
    // Ejecuta la prueba segura
    std::cout << "\n--- Ejecutando Prueba SEGURA ---" << std::endl;
    contador = 0;
    for (int i = 0; i < NUM_HILOS; ++i) {
        hilos.emplace_back(incrementar_seguro);
    }
    for (auto& h : hilos) h.join();

    std::cout << "Resultado SEGURO: " << contador << std::endl;
    
    std::cout << "\n--- Fin del Programa ---" << std::endl;
    return 0;
}