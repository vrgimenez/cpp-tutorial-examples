#include <iostream>
#include <stdexcept>
#include <string>
#include <memory> // Incluimos unique_ptr para ver la diferencia

// --- 1. Clase para Rastreo de Ciclo de Vida (Simulación de un Recurso) ---
class Rastreador {
private:
    std::string nombre;
public:
    Rastreador(const std::string& n) : nombre(n) {
        std::cout << "--> " << nombre << " ha sido CONSTRUIDO." << std::endl;
    }
    ~Rastreador() {
        std::cout << "<-- " << nombre << " ha sido DESTRUIDO." << std::endl;
    }
    void usar() const {
        std::cout << "    Usando recurso: " << nombre << std::endl;
    }
};

// --- 2. Función que Lanza la Excepción ---
void trabajoPeligroso(int valor) {
    // Rastreador creado en el stack de esta funcion
    Rastreador r2("Rastreador_Funcion"); 
    r2.usar();
    
    // Simulación de una condición de error
    if (valor == 0) {
        std::cout << "!!! Lanzando std::runtime_error !!!" << std::endl;
        // Lanzamos la excepcion. El control salta del 'try' al 'catch'.
        throw std::runtime_error("Fallo critico: Valor es cero.");
    }
    
    std::cout << "    Trabajo peligroso completado con exito." << std::endl;
}

int main() {
    std::cout << "--- Inicio del Programa ---" << std::endl;
    
    // Recurso 1: Manejado de forma segura (RAII)
    std::unique_ptr<Rastreador> recurso_inteligente = 
        std::make_unique<Rastreador>("Recurso_Inteligente_Heap");

    try {
        // Rastreador 3: Creado dentro del bloque try
        Rastreador r3("Rastreador_Try_Stack");
        r3.usar();

        // ----------------------------------------------------
        // Llama a la funcion que LANZA una excepcion si es 0
        trabajoPeligroso(0); 
        // ----------------------------------------------------

        // Esta línea es inaccesible si se lanza la excepción.
        std::cout << "SUCCESS: Fin del bloque try." << std::endl; 

    } catch (const std::runtime_error& e) {
        // Bloque de captura
        std::cerr << "\n!!! Capturado: " << e.what() << std::endl;

    } catch (...) {
        std::cerr << "!!! Capturado: Excepcion desconocida." << std::endl;
    }

    std::cout << "\n--- Programa ha continuado despues del catch ---" << std::endl;
    // El destructor de recurso_inteligente se llama AQUI, al final del main.
    return 0;
}