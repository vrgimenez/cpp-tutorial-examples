#include <iostream>
#include <fstream>  // Para std::ofstream y std::ifstream
#include <string>
#include <vector>
#include <sstream>  // Por si fuera necesario en lectura avanzada

const std::string NOMBRE_ARCHIVO = "lista_clientes.txt";

// --- 1. Escritura de Datos ---
void escribirDatos(const std::vector<std::string>& datos) {
    // std::ofstream: El archivo se abre en el constructor.
    std::ofstream archivo_salida(NOMBRE_ARCHIVO, std::ios::out); 

    // VERIFICACION CRUCIAL: ¿Se abrió el archivo correctamente?
    if (!archivo_salida.is_open()) {
        std::cerr << "ERROR: No se pudo abrir el archivo para escritura: " << NOMBRE_ARCHIVO << std::endl;
        return; 
    }

    // TODO: Escribe cada elemento del vector al archivo.
    // Pista: Usa el operador << y std::endl para saltos de línea.
    
    // Tu código aquí:
    for(std::string nombre : datos)
        archivo_salida << nombre << std::endl;
    
    // El destructor de 'archivo_salida' se llamará automáticamente al salir de esta función (RAII).
    std::cout << "DEBUG: Escritura completada. Archivo cerrado automaticamente." << std::endl;
}

// --- 2. Lectura de Datos ---
std::vector<std::string> leerDatos() {
    std::vector<std::string> datos_leidos;
    // std::ifstream: El archivo se abre en el constructor.
    std::ifstream archivo_entrada(NOMBRE_ARCHIVO); 

    if (!archivo_entrada.is_open()) {
        std::cerr << "ERROR: No se pudo abrir el archivo para lectura: " << NOMBRE_ARCHIVO << std::endl;
        return datos_leidos; 
    }

    std::string linea;
    
    // TODO: Lee línea por línea hasta el final del archivo.
    // Pista: Usa el bucle while(std::getline(stream, string)).
    
    // Tu código aquí:
    while(std::getline(archivo_entrada, linea))
        datos_leidos.push_back(linea);
    
    // El destructor de 'archivo_entrada' se llamará automáticamente al salir de esta función (RAII).
    return datos_leidos;
}

int main() {
    std::vector<std::string> nombres = {"Alicia", "Beto", "Carlos", "Diana"};

    std::cout << "--- 1. Escribiendo al Archivo ---" << std::endl;
    escribirDatos(nombres);

    std::cout << "\n--- 2. Leyendo desde el Archivo ---" << std::endl;
    std::vector<std::string> nombres_leidos = leerDatos();

    std::cout << "\n--- 3. Verificacion de Lectura ---" << std::endl;
    if (nombres_leidos.empty()) {
        std::cout << "El vector de nombres leidos esta vacio." << std::endl;
    } else {
        std::cout << "Nombres leidos exitosamente: " << std::endl;
        for (const std::string& nombre : nombres_leidos) {
            std::cout << "- " << nombre << std::endl;
        }
    }

    std::cout << "\n--- Fin del Programa ---" << std::endl;
    return 0;
}