cmake_minimum_required(VERSION 3.29)
project(SistemaGP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Agregar los archivos de cabecera (header) si es necesario
# Si tienes más archivos .cpp en el proyecto, agréguelos aquí
add_executable(main main.cpp)

# Especificar el directorio de inclusión
target_include_directories(main PRIVATE include)