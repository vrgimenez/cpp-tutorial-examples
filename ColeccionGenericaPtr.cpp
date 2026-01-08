#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>

// Definición de la Clase Genérica (Primaria)
// Esta versión maneja tipos "normales" (int, string, objetos, etc.) y hace DEEP COPY.
template <typename T>
class ColeccionGenerica {
private:
    T* datos;
    int tamano;

public:
    ColeccionGenerica(int n) : tamano(n) {
        datos = (tamano > 0) ? new T[tamano] : nullptr;
        std::cout << "DEBUG (Primaria): Creada coleccion de " << tamano << " elementos." << std::endl;
    }
    
    // Constructor de Copia (DEEP COPY) - Ya lo completaste
    ColeccionGenerica(const ColeccionGenerica<T>& other) : tamano(other.tamano) {
        datos = (tamano > 0) ? new T[tamano] : nullptr;
        if (tamano > 0) {
            std::copy(other.datos, other.datos + tamano, datos);
        }
        std::cout << "DEBUG (Primaria): Se realizo COPIA PROFUNDA de los datos." << std::endl;
    }

    ~ColeccionGenerica() { delete[] datos; }

    void establecer(int indice, const T& valor) { 
        if (indice >= 0 && indice < tamano) datos[indice] = valor; 
    }
    
    // Getter que devuelve la referencia para poder manipular el contenido de T
    T& obtener(int indice) const {
         if (indice < 0 || indice >= tamano) throw std::out_of_range("Index out of bounds");
         return datos[indice];
    }
    
    void mostrarElementos() const {
        std::cout << "Coleccion (tamano " << tamano << "): [";
        for (int i = 0; i < tamano; ++i) {
            std::cout << datos[i];
            if (i < tamano - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};

// =========================================================================
// !!! ESPECIALIZACIÓN PARCIAL DE CLASE PARA PUNTEROS (Type*) !!!
// Se usa solo cuando el tipo T es de la forma "algo*"
// =========================================================================

template <typename Type>
class ColeccionGenerica<Type*> { // Notar la sintaxis <Type*>. Esto reemplaza a <T>
private:
    Type** datos; // T = Type*, por lo tanto, datos es un puntero de punteros
    int tamano;

public:
    ColeccionGenerica(int n) : tamano(n) {
        datos = (tamano > 0) ? new Type*[tamano] : nullptr;
        std::cout << "DEBUG (Especializada): Creada coleccion de PUNTEROS." << std::endl;
    }

    ~ColeccionGenerica() { delete[] datos; }

    // Setter: acepta un puntero y lo almacena
    void establecer(int indice, Type* valor) { 
        if (indice >= 0 && indice < tamano) datos[indice] = valor; 
    }
    
    // Getter: devuelve el puntero almacenado
    Type* obtener(int indice) const {
         if (indice < 0 || indice >= tamano) throw std::out_of_range("Index out of bounds");
         return datos[indice];
    }

    // --- Constructor de Copia Especializado (SHALLOW COPY) ---
    // !!! TU TAREA: Implementa la lógica de copiado superficial de los punteros.
    ColeccionGenerica(const ColeccionGenerica<Type*>& other) : tamano(other.tamano) {
        datos = (tamano > 0) ? new Type*[tamano] : nullptr;
        
        // TODO: Copia superficial. Usa std::copy para copiar las DIRECCIONES (Type*)
        // desde other.datos a this->datos. 
        // Recuerda: Type* es el tipo de los elementos que se copian.
        
        if (tamano > 0) {
            // TU CÓDIGO AQUÍ:
            std::copy(other.datos, other.datos + tamano, datos);
            // FIN TU CÓDIGO
        }
        std::cout << "DEBUG (Especializada): Se realizo COPIA SUPERFICIAL de los punteros." << std::endl;
    }

    void mostrarElementos() const {
        std::cout << "Coleccion Punteros (tamano " << tamano << "): [";
        for (int i = 0; i < tamano; ++i) {
            if (datos[i]) {
                // Muestra la dirección y el VALOR al que apunta
                std::cout << "ptr(" << datos[i] << ")->val(" << *datos[i] << ")";
            } else {
                std::cout << "nullptr";
            }
            if (i < tamano - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};

int main() {
    // --- 1. Prueba de la versión Primaria (T=int, DEEP COPY) ---
    std::cout << "--- Prueba Primaria (T=int) ---" << std::endl;
    ColeccionGenerica<int> c1(1);
    c1.establecer(0, 100);
    ColeccionGenerica<int> c2 = c1; // DEEP COPY
    c1.establecer(0, 50); // Modifico c1
    
    std::cout << "Original c1: "; c1.mostrarElementos(); // Muestra 50
    std::cout << "Copia c2: "; c2.mostrarElementos();    // Muestra 100 (INDIVIDUAL)
    
    // --- 2. Prueba de la versión Especializada (T=int*, SHALLOW COPY) ---
    std::cout << "\n--- Prueba Especializada (T=int*) ---" << std::endl;
    
    int* valor = new int(200);
    ColeccionGenerica<int*> cp1(1);
    cp1.establecer(0, valor);
    
    ColeccionGenerica<int*> cp2 = cp1; // SHALLOW COPY (Llama a la especialización)
    
    // Modifico el valor a través del puntero ORIGINAL
    *valor = 777; 
    
    std::cout << "Original cp1: "; cp1.mostrarElementos(); // Muestra 777
    std::cout << "Copia cp2: "; cp2.mostrarElementos();    // !!! TU PRUEBA: Debe mostrar 777 (COMPARTEN EL MISMO RECURSO)
    
    delete valor; // Limpio la memoria que asigné con new
    std::cout << "\n--- Fin del Programa. ---" << std::endl;
    return 0;
}