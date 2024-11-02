#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <iomanip>
#include<conio.h>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
using namespace std;
const std::string archivoCategorias = "categorias.txt";
const std::string pathUsuarios = "../data/usuarios.csv";

struct Plato{
    char categoria[30];
    char nombre[30];
    float precio=0;
    int cantidad = 0;
    char comentario[30]= {'\0'};
};
struct Fecha{
    long segreales;
    short dias, meses, anios, minutos, horas, seg;
};

struct Orden {

    int numeroMesa;
    Fecha hora;
    char estado[15];
    std::vector<Plato> platos;

};


inline string to_string(short x) {
    ostringstream oss;
    oss << x;
    return oss.str();
}

inline Fecha definir_fecha(short d, short h, short m, short s){
    Fecha aux;
    time_t hoy = time(nullptr) + d*86400 + h*3600 + m*60 + s;
    struct tm *f = localtime(&hoy);

    aux.dias = f->tm_mday;
    aux.meses = f->tm_mon+1;
    aux.anios = f->tm_year+1900;
    aux.minutos = f->tm_min;
    aux.horas = f->tm_hour;
    aux.seg = f->tm_sec;
    aux.segreales = time(nullptr) + d*86400 + h*3600 + m*60 + s;
    return (aux);
}



inline string formato_hora(Fecha x){
    string corregir_min;

    if(x.minutos<10){
        corregir_min = "0" + to_string(x.minutos);
    }else{
        corregir_min = to_string(x.minutos);
    }

    return (to_string(x.dias) + "/" + to_string(x.meses) + "/" + to_string(x.anios) + " a las " + to_string(x.horas) + ":" + corregir_min);
}



// Carga las categorías desde el archivo al inicio
inline void cargarCategorias(vector<string>& categorias) {
    ifstream archivo(archivoCategorias);
    if (archivo.is_open()) {
        string categoria;
        while (getline(archivo, categoria)) {
            if (!categoria.empty()) {
                categorias.push_back(categoria);
            }
        }
        archivo.close();
    }
}


inline void guardarCategoria(const std::string& categoria) {
    ofstream archivo(archivoCategorias, ios::app);
    if (archivo.is_open()) {
        archivo << categoria << "\n";
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo de categorias para guardar.\n";
    }
}

inline void agregarCategoria(const string& nuevaCategoria, vector<string>& categorias) {
    if (find(categorias.begin(), categorias.end(), nuevaCategoria) == categorias.end()) {
        categorias.push_back(nuevaCategoria);
        guardarCategoria(nuevaCategoria);
    }
}
inline void mostrarCategorias(const vector<string>& categorias) {
    const int width = 20;
    cout << "\n> Categorias disponibles:\n";
    for (size_t i = 0; i < categorias.size(); ++i) {
        cout << "[" << setw(width) << left << categorias[i].substr(0, 15) << "]";
        if ((i + 1) % 4 == 0) {
            cout << "\n";
        }
    }
    cout << "\n";
}
inline void mostrarPlatosPorCategoria(const string &categoria, Orden &o, bool &flag ) {
    int continuar;
    //esta variable se usa solo para recorrer el archivo
    Plato p;
    vector<Plato> platosDisponibles;
    cout << "\nPlatos en la categoria " << categoria  << endl;


    FILE *archivo2 = fopen("Platos.dat", "rb");
    if (!archivo2) {
        cout << "Error al abrir el archivo de platos." << endl;
        return;
    }


    while (fread(&p, sizeof(Plato), 1, archivo2)) {

        if (strcmp(p.categoria, categoria.c_str()) == 0) {
            cout << "- " << p.nombre << " ($" << p.precio << ")" << endl;
            platosDisponibles.push_back(p);
        }
    }


    string nombrePlatoSeleccionado;
    do {
        cout << "Ingrese el nombre del plato que desea seleccionar: ";
        fflush(stdin);
        getline(cin, nombrePlatoSeleccionado);

        // Buscar el plato
        Plato platoSeleccionado;
        bool encontrado = false;
        for (const auto &plato : platosDisponibles) {
            if (strcmp(plato.nombre, nombrePlatoSeleccionado.c_str()) == 0) {
                platoSeleccionado = plato;
                encontrado = true;
                break; // Salir del bucle si se encuentra el plato
            }
        }

        // Si el plato fue encontrado, actualizar cantidad y comentario
        if (encontrado) {
            cout << "Ingrese la cantidad: ";
            cin >> platoSeleccionado.cantidad;
            fflush(stdin); // Limpiar el buffer
            cout << "Ingrese un comentario: ";
            cin.getline(platoSeleccionado.comentario, sizeof(platoSeleccionado.comentario));

            // Añadir el plato a la orden
            o.platos.push_back(platoSeleccionado);
            cout << "Plato agregado a la orden con exito." << endl;
        } else {
            cout << "Plato no encontrado." << endl;
            flag = true;
            return;
        }



        // Preguntar si desea agregar otro plato de la misma categoria
        cout << "¿Desea agregar otro plato a la orden, de la misma categoria? (1: Sí | 0: No): ";
        cin >> continuar;

    } while (continuar == 1);
    fclose(archivo2);

}
inline void mostrarMesas(int filas, int columnas) {
    int mesa = 1;

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (mesa <= 15) {
                cout << "+-----+  ";
            }
        }
        cout << endl;

        for (int j = 0; j < columnas; j++) {
            if (mesa <= 15) {
                cout << "|  " << setw(2) << mesa << "  |  ";
                mesa++;
            }
        }
        cout << endl;

        for (int j = 0; j < columnas; j++) {
            if (mesa - 1 <= 15) {
                cout << "+-----+  ";
            }
        }
        cout << endl;
    }
}




// Función que imprime el menú de cocina
inline void menuCocina() {
    cout << "Cargando menú cocina..." << endl;
    // Aquí puedes agregar más funcionalidades más adelante
}

#endif //UTILS_H
