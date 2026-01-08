#include <iostream>
#include <algorithm> // For std::copy
#include <string>

// --- Class Template Definition ---
template <typename T>
class ColeccionGenerica {
private:
    T* datos;
    int tamano;

public:
    // Parametrized Constructor: Allocates dynamic memory for type T
    ColeccionGenerica(int n) : tamano(n) {
        if (tamano > 0) {
            datos = new T[tamano];
            std::cout << "DEBUG: Constructor. Memory allocated for " << tamano << " elements of type T." << std::endl;
        } else {
            datos = nullptr;
        }
    }

    // Destructor: Frees dynamic memory
    ~ColeccionGenerica() {
        if (datos != nullptr) {
            delete[] datos;
            std::cout << "DEBUG: Destructor. Memory freed." << std::endl;
        }
    }

    // --- Copy Constructor (Deep Copy) ---
    // This must work for any type T!
    ColeccionGenerica(const ColeccionGenerica<T>& other) : tamano(other.tamano) {
        std::cout << "DEBUG: Copy Constructor called." << std::endl;
        if (tamano > 0) {
            // TODO: 1. Allocate NEW memory for this->datos
            datos = new T[tamano];
            
            // TODO: 2. Copy the CONTENTS from other.datos to this->datos
            // Hint: Use std::copy. The parameters are: 
            //       start_source, end_source, start_destination
            std::copy(other.datos, other.datos + tamano, datos);
        } else {
            datos = nullptr;
        }
    }

    // Setter
    void establecer(int indice, const T& valor) {
        if (indice >= 0 && indice < tamano) {
            datos[indice] = valor;
        }
    }

    // Getter
    T obtener(int indice) const {
        if (indice >= 0 && indice < tamano) {
            return datos[indice];
        }
        // Simplified error handling
        throw std::out_of_range("Index out of bounds");
    }

    // Display (works if T supports << operator)
    void mostrarElementos() const {
        std::cout << "Collection elements (Size: " << tamano << "): [";
        for (int i = 0; i < tamano; ++i) {
            std::cout << datos[i];
            if (i < tamano - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
};

int main() {
    std::cout << "--- 1. Testing with Integers ---" << std::endl;
    
    // Instantiation 1: T is int
    ColeccionGenerica<int> c_int_1(3);
    c_int_1.establecer(0, 10);
    c_int_1.establecer(1, 20);
    c_int_1.establecer(2, 30);
    
    // Test Copy Constructor (Deep Copy)
    ColeccionGenerica<int> c_int_2 = c_int_1; // Calls Copy Constructor
    
    // Modify original to check if copy is independent
    c_int_1.establecer(0, 999);
    
    std::cout << "Original c_int_1: "; c_int_1.mostrarElementos(); // Should show 999
    std::cout << "Copied c_int_2: "; c_int_2.mostrarElementos();   // Should show 10 (Deep Copy)

    std::cout << "\n--- 2. Testing with Strings ---" << std::endl;
    
    // Instantiation 2: T is std::string
    ColeccionGenerica<std::string> c_str_1(2);
    c_str_1.establecer(0, "Apple");
    c_str_1.establecer(1, "Banana");

    // Test Copy Constructor with strings
    ColeccionGenerica<std::string> c_str_2 = c_str_1; // Calls Copy Constructor

    c_str_1.establecer(0, "Zebra");

    std::cout << "Original c_str_1: "; c_str_1.mostrarElementos(); // Should show Zebra
    std::cout << "Copied c_str_2: "; c_str_2.mostrarElementos();   // Should show Apple (Deep Copy)

    std::cout << "\n--- Program End. Destructors called. ---" << std::endl;
    return 0;
}