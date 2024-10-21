cmake_minimum_required(VERSION 3.29)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(untitled scr/main.cpp
        scr/login.cpp
        include/misOrdenes.h
        include/menuMesero.h
)
