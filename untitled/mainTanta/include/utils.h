#ifndef UTILS_H
#define UTILS_H

#include <iostream>
using namespace std;

const std::string pathUsuarios = "../data/usuarios.csv";
struct Orden {
    int id;
    std::string hora;
    std::string estado;
};

inline Orden ordenes[] = {
    {9, "10:45 a.m.", "Pendiente"},
    {12, "09:23 a.m.", "Completada"}
};

inline void menuAdmin() {
    cout << "Cargando menú admin..." << endl;
    // Aquí puedes agregar más funcionalidades más adelante
}

// Función que imprime el menú de cocina
inline void menuCocina() {
    cout << "Cargando menú cocina..." << endl;
    // Aquí puedes agregar más funcionalidades más adelante
}

#endif //UTILS_H
