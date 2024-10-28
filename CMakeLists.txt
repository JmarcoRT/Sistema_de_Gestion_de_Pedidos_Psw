cmake_minimum_required(VERSION 3.29)
project(SistemaGP)  # El nombre del proyecto puede seguir siendo SistemaGP

set(CMAKE_CXX_STANDARD 20)


add_executable(main main.cpp)

target_include_directories(main PRIVATE include)
