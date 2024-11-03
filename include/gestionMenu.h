//Submodulo para Gestionar el Menu
#ifndef GESTIONMENU_H
#define GESTIONMENU_H

#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


inline void agregarPlatos(const string& archivo) {
    ofstream file(archivo, ios::app);
    if (!file.is_open()) {
        cout << "Error al abrir el archivo " << archivo << endl;
        return;
    }

    string nombre;
    double precio;
    char opcion;

    do {
        bool estado = true;

        cout << "Ingresa el nombre del plato--> ";
        cin >> ws;
        getline(cin, nombre);

        cout << "Ingresa el precio del plato--> ";
        while (!(cin >> precio)) {
            cout << "Precio inválido. Ingresa un número: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer

        file << nombre << "|" << precio << "|" << estado << endl;

        cout << "Deseas agregar otro plato? (s/n)--> ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer
    } while (opcion == 's' || opcion == 'S');

    file.close();
    cout << "Platos agregados a " << archivo << " correctamente." << endl;
}


inline void leerPlatos(const string& archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cout << "Error al abrir el archivo " << archivo << endl;
        return;
    }

    string linea;
    bool hayContenido = false;

    cout << "Contenido de " << archivo << ":" << endl;

    while (getline(file, linea)) {
        istringstream stream(linea);
        string nombre, precioStr, estadoStr;

        // Usamos '|' como delimitador para separar el nombre, precio y estado
        getline(stream, nombre, '|');
        getline(stream, precioStr, '|');
        getline(stream, estadoStr, '|');

        double precio = stod(precioStr);  // Convertimos precio a double
        bool estado = (estadoStr == "1"); // Convertimos estado a booleano

        cout << "Plato: " << nombre << ", Precio: " << precio << ", Estado: " << (estado ? "Activado" : "Desactivado") << endl;
        hayContenido = true;
    }

    if (!hayContenido) {
        cout << "No hay platos en el archivo." << endl;
    }

    file.close();
}


inline void actualizarPlato(const string& archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cout << "Error al abrir el archivo " << archivo << endl;
        return;
    }

    string linea, nombreBuscado;
    bool encontrado = false;

    cout << "Ingresa el nombre del plato a actualizar: ";
    cin >> ws;
    getline(cin, nombreBuscado);

    ofstream temp("temp.txt");

    while (getline(file, linea)) {
        istringstream stream(linea);
        string nombre, precioStr, estadoStr;

        getline(stream, nombre, '|');
        getline(stream, precioStr, '|');
        getline(stream, estadoStr, '|');

        double precio = stod(precioStr);
        bool estado = (estadoStr == "1");

        if (nombre == nombreBuscado) {
            encontrado = true;

            cout << "Plato encontrado: " << endl;
            cout << "Nombre actual: " << nombre << ", Precio actual: " << precio << ", Estado: " << (estado ? "Activado" : "Desactivado") << endl;

            // Nombre
            cout << "Nuevo nombre (dejar en blanco para no cambiar): ";
            string nuevoNombre;
            getline(cin, nuevoNombre);
            if (!nuevoNombre.empty()) {
                nombre = nuevoNombre;
            }

            // Precio
            cout << "Nuevo precio (dejar en blanco para no cambiar): ";
            string entradaPrecio;
            getline(cin, entradaPrecio);
            if (!entradaPrecio.empty()) {
                double nuevoPrecio;
                istringstream precioStream(entradaPrecio);
                if (precioStream >> nuevoPrecio) {
                    precio = nuevoPrecio;
                } else {
                    cout << "Precio invalido. Se mantiene el precio actual." << endl;
                }
            }

            // Estado
            cout << "Nuevo estado (1=Activado, 0=Desactivado, dejar en blanco para no cambiar): ";
            string entradaEstado;
            getline(cin, entradaEstado);
            if (!entradaEstado.empty()) {
                if (entradaEstado == "1") estado = true;
                else if (entradaEstado == "0") estado = false;
                else cout << "Estado invalido. Se mantiene el estado actual." << endl;
            }

            temp << nombre << "|" << precio << "|" << estado << endl;
        } else {
            temp << nombre << "|" << precio << "|" << estado << endl;
        }
    }

    file.close();
    temp.close();

    if (encontrado) {
        remove(archivo.c_str());
        rename("temp.txt", archivo.c_str());
        cout << "Plato actualizado correctamente." << endl;
    } else {
        remove("temp.txt");
        cout << "El plato no se encontro en " << archivo << "." << endl;
    }
}


inline void menuGestionarMenu() {

    int opcion;
    string archivoSeleccionado;

    do {
        cout << "\n\tMENU\n";
        cout << "1. Agregar platos\n";
        cout << "2. Ver platos\n";
        cout << "3. Actualizar plato\n";
        cout << "0. Salir\n\n";
        cout << "Selecciona una opcion--> ";

        if (!(cin >> opcion)) {
            cout << "Opcion invalida. Intenta de nuevo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcion < 0 || opcion > 3) {
            cout << "Opcion invalida. Intenta de nuevo." << endl;
            continue;
        }

        if (opcion == 0) break;

        int tipo;
        cout << "\nSelecciona el tipo de plato:\n";
        cout << "1. Entradas\n";
        cout << "2. Segundos\n";
        cout << "3. Bebidas\n\n";
        cout << "Selecciona una opcion--> ";

        if (!(cin >> tipo) || tipo < 1 || tipo > 3) {
            cout << "Tipo de plato inválido." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (tipo == 1) archivoSeleccionado = "entradas.txt";
        else if (tipo == 2) archivoSeleccionado = "segundos.txt";
        else archivoSeleccionado = "bebidas.txt";

        if (opcion == 1) agregarPlatos(archivoSeleccionado);
        else if (opcion == 2) leerPlatos(archivoSeleccionado);
        else if (opcion == 3) actualizarPlato(archivoSeleccionado);

    } while (opcion != 0);

    cout << "Saliendo del programa." << endl;
}


#endif //GESTIONMENU_H