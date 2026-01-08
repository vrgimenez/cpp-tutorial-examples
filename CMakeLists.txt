# Versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(LearningCPP LANGUAGES CXX) # Indica que es un proyecto C++

# Especifica el estándar C++ a usar (por ejemplo, C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# The example applications
set(EXECUTABLES
    ClasesAbstractas
    ColeccionEnteros
    ColeccionGenerica
    ColeccionGenericaPtr
    ColeccionVector
    ContadorSTL
    ExcepcionesRAII
    FactorialAsync
    FileIO
    FuturePromise
    HerenciaPoliAnimales
    Inventario_IA_solution
    Inventario
    main01
    main02
    multithreading_example
    multithreading_example_detach
    multithreading_example_sharedVector
    MutexRAII
    Notificacion_IA_payload
    Notificacion_IA_solution1
    Notificacion_IA_solution2
    Notificacion
    shared_ptr_example
)

## Build the example apps
foreach(EXECUTABLE ${EXECUTABLES})
    add_executable(${EXECUTABLE} ${EXECUTABLE}.cpp)

    # 1. Modo Debug (por defecto si no se especifica otro)
    # En modo Debug, CMake y el compilador:
    # - Habilitan símbolos de depuración (-g en GCC/Clang)
    # - Deshabilitan optimizaciones (o usan -O0)
    # - No definen NDEBUG
    target_compile_options(${EXECUTABLE} PUBLIC
        $<$<CONFIG:Debug>:-g>
        $<$<CONFIG:Debug>:-O0>
    )

    # 2. Modo Release
    # En modo Release, CMake y el compilador:
    # - Eliminan símbolos de depuración (-s o -g0 en GCC/Clang)
    # - Habilitan optimizaciones (-O2, -O3, -Os)
    # - Definen NDEBUG (que desactiva 'assert' y otras comprobaciones)
    target_compile_options(${EXECUTABLE} PUBLIC
        $<$<CONFIG:Release>:-O3>
        $<$<CONFIG:Release>:-DNDEBUG>
    )

    # Añadir sufijos a los binarios (opcional, pero útil)
    set_target_properties(${EXECUTABLE} PROPERTIES
        DEBUG_POSTFIX "_debug"
        RELEASE_POSTFIX "_release"
    )

    # Usa target_link_options para pasar -s (strip symbols) al linker solo en modo Release.
    target_link_options(${EXECUTABLE} PUBLIC
        $<$<CONFIG:Release>:-s>
    )
endforeach()

# Puedes definir opciones predeterminadas para los flags del compilador
# (Aunque las target_compile_options son más específicas)
# set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
# set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")