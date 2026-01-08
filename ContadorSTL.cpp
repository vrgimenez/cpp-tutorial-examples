#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm> // Para std::sort y std::copy
#include <utility>   // Para std::pair

// El tipo de nuestro mapa: Clave (palabra) es string, Valor (frecuencia) es int
using Frecuencias = std::map<std::string, int>;

// --- 1. Contar frecuencias y llenar el mapa ---
Frecuencias contarFrecuencias(const std::vector<std::string>& palabras) {
    Frecuencias conteo;

    // TODO: Itera sobre el vector 'palabras' y actualiza el mapa 'conteo'.
    // Pista: Para añadir o actualizar un elemento en el mapa, usa la notación:
    // conteo[palabra] = conteo[palabra] + 1; 
    // Si la 'palabra' no existe, std::map la crea automáticamente con el valor 0 (lo que simplifica la cuenta).
    
    // Tu código aquí:
    for (const auto& palabra : palabras) {
        // 'palabra' es un std::vector<const std::string>
        conteo[palabra]++;
    }
    return conteo;
}

// Función auxiliar para imprimir el mapa
void imprimirFrecuencias(const Frecuencias& conteo) {
    std::cout << "\n--- Frecuencias Originales (Ordenado por Clave) ---" << std::endl;
    for (const auto& par : conteo) {
        // 'par' es un std::pair<const std::string, int>
        std::cout << "Palabra: '" << par.first << "' -> Frecuencia: " << par.second << std::endl;
    }
}

// --- 2. Comparador para ordenar el vector por frecuencia ---
// Usaremos esta función para decirle a std::sort cómo comparar dos pares.
bool compararParesPorFrecuencia(const std::pair<std::string, int>& a, 
                                const std::pair<std::string, int>& b) {
    // Queremos que los pares con MAYOR frecuencia vayan PRIMERO.
    // Esto se logra devolviendo 'true' si 'a' es MAYOR que 'b'.
    return a.second > b.second; 
}


int main() {
    std::vector<std::string> texto = {
        "manzana", "banana", "pera", "manzana", "banana", "manzana", "uva"
    };
    
    // Parte 1: Uso del contenedor std::map
    Frecuencias conteo_mapa = contarFrecuencias(texto);
    imprimirFrecuencias(conteo_mapa);
    
    // Parte 2: Uso de contenedores y algoritmos
    std::cout << "\n--- Ordenando por Frecuencia (Usando Vector y Algoritmo) ---" << std::endl;
    
    // 2.1 Crear un vector de pares (el contenido de un mapa es una colección de pares)
    using ParPalabraFrecuencia = std::pair<std::string, int>;
    std::vector<ParPalabraFrecuencia> lista_ordenada;

    // TODO: Copia el contenido de 'conteo_mapa' a 'lista_ordenada'.
    // Puedes usar un bucle 'for' normal o el algoritmo std::copy.
    // Pista: Los mapas y vectores se acceden con .begin() y .end().
    
    // Tu código aquí:
    lista_ordenada.resize(conteo_mapa.size());
    std::copy(conteo_mapa.begin(), conteo_mapa.end(), lista_ordenada.begin());
    
    // 2.2 Ordenar el vector con un algoritmo estándar
    // Utilizamos el algoritmo std::sort con nuestro comparador personalizado.
    // TODO: Llama a std::sort para ordenar 'lista_ordenada' usando 'compararParesPorFrecuencia'
    
    // Tu código aquí:
    std::sort(lista_ordenada.begin(), lista_ordenada.end(), compararParesPorFrecuencia);
    
    // 2.3 Imprimir resultados ordenados
    for (const auto& par : lista_ordenada) {
        std::cout << "Palabra: '" << par.first << "' -> Frecuencia: " << par.second << std::endl;
    }

    std::cout << "\n--- Fin del Programa ---" << std::endl;
    return 0;
}