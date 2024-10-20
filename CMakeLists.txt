cmake_minimum_required(VERSION 3.29)
project(SistemaGP)

set(CMAKE_CXX_STANDARD 20)

add_executable(SistemaGP main.cpp)

target_include_directories(SistemaGP PRIVATE include)