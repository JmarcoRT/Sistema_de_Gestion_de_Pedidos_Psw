//Submodulo para Gestionar el Menu
#ifndef GESTIONMENU_H
#define GESTIONMENU_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <string>
#include <ctime>
#include <iomanip>
#include <cctype>
#include <cstring> // Para manejo de strings en binarios
#include "utilidades.h"
#include "menuMesero.h"
#include "utils.h"
using namespace std;

struct HistorialCambio {
    int id;
    char campo[20];
    char valorAntiguo[20];
    char valorNuevo[20];
    char fecha[20];
};

// Función para convertir una cadena a minúsculas
inline void convertirAMinusculas(string& str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

// Funcion para obtener la fecha actual en formato string
inline string obtenerFechaActual() {
    time_t ahora = time(nullptr);
    tm* tiempoLocal = localtime(&ahora);
    ostringstream oss;
    oss << (tiempoLocal->tm_year + 1900) << "-"
        << (tiempoLocal->tm_mon + 1) << "-"
        << tiempoLocal->tm_mday << " "
        << tiempoLocal->tm_hour << ":"
        << tiempoLocal->tm_min;
    return oss.str();
}

inline void limpiarPantalla() {
    system("cls"); // Para Windows
}

inline int obtenerUltimoID() {
    fstream archivoContador("contador_id.txt", ios::in | ios::out);
    int id = 0;

    if (!archivoContador.is_open()) {
        // Si el archivo no existe, comenzamos con el ID 0
        archivoContador.open("contador_id.txt", ios::out);
        archivoContador << id; // Escribimos el primer ID
        archivoContador.close();
        return id;
    }

    archivoContador >> id;
    archivoContador.close();

    return id; // Retorna el último ID asignado
}

// Función para verificar si una cadena es un número válido
inline bool esNumero(const string& str) {
    try {
        stod(str); // Intentamos convertir a double
        return true;
    } catch (...) {
        return false;
    }
}

inline void mostrarHistorialPlato(int id) {
    ifstream historial("historial.bin", ios::binary);
    if (!historial.is_open()) {
        cout << "Error al abrir el archivo de historial." << endl;
        return;
    }

    HistorialCambio cambio{};
    bool hayCambios = false; // Para verificar si hay registros para este ID
    cout << "\tHistorial de cambios para el plato con ID: " << id << endl;
    cout << "-------------------------------------------------------------------------------" << endl;

    while (historial.read(reinterpret_cast<char*>(&cambio), sizeof(HistorialCambio))) {
        if (cambio.id == id) { // Mostrar solo los registros con el ID correspondiente
            hayCambios = true;
            cout << "Campo: " << cambio.campo << endl;
            cout << "Valor antiguo: ";

            // Si el valor es numérico, lo formateamos
            if (esNumero(cambio.valorAntiguo)) {
                double oldPrecio = stod(cambio.valorAntiguo);
                cout << fixed << setprecision(2) << oldPrecio;
            } else {
                cout << cambio.valorAntiguo;
            }

            cout << ", Valor nuevo: ";

            // Si el valor es numérico, lo formateamos
            if (esNumero(cambio.valorNuevo)) {
                double newPrecio = stod(cambio.valorNuevo);
                cout << fixed << setprecision(2) << newPrecio;
            } else {
                cout << cambio.valorNuevo;
            }

            cout << ", Fecha: " << cambio.fecha << endl;
            cout << "-------------------------------------------------------------------------------" << endl;
        }
    }

    if (!hayCambios) {
        cout << "No hay historial de cambios para este plato." << endl;
    }

    historial.close();
}

// Función para registrar cambios en un archivo binario
inline void registrarCambio(int id, const string& campo, const string& valorAntiguo, const string& valorNuevo) {
    ofstream historial("historial.bin", ios::app | ios::binary);
    if (!historial.is_open()) {
        cout << "Error al abrir el archivo de historial." << endl;
        return;
    }

    HistorialCambio cambio{};
    cambio.id = id;
    strncpy(cambio.campo, campo.c_str(), sizeof(cambio.campo) - 1);
    cambio.campo[sizeof(cambio.campo) - 1] = '\0';
    strncpy(cambio.valorAntiguo, valorAntiguo.c_str(), sizeof(cambio.valorAntiguo) - 1);
    cambio.valorAntiguo[sizeof(cambio.valorAntiguo) - 1] = '\0';
    strncpy(cambio.valorNuevo, valorNuevo.c_str(), sizeof(cambio.valorNuevo) - 1);
    cambio.valorNuevo[sizeof(cambio.valorNuevo) - 1] = '\0';
    string fecha = obtenerFechaActual();
    strncpy(cambio.fecha, fecha.c_str(), sizeof(cambio.fecha) - 1);
    cambio.fecha[sizeof(cambio.fecha) - 1] = '\0';

    // Guardar el cambio en el archivo binario
    historial.write(reinterpret_cast<const char*>(&cambio), sizeof(HistorialCambio));
    historial.close();
}

inline void agregarPlatos(const string& archivo, vector<string>& categorias) {
    limpiarPantalla();
    ofstream file(archivo, ios::binary | ios::app);
    FILE *archivoSecundario = fopen("Platos.dat", "a+b");

    if (!file.is_open() || archivoSecundario == nullptr) {
        cout << "Error al abrir el archivo " << archivo << " o Platos.dat" << endl;
        return;
    }

    string nombre, categoria;
    double precio;
    char continuarCategoria, continuarPlato;

    // Obtener un ID único global para el nuevo plato
    int idNuevo = obtenerUltimoID() + 1;  // Incrementamos el ID global
    Plato plato{};
    plato.id = idNuevo;
    plato.estado = true;

    do {
        cout << "\n> CREAR PLATO\n" << endl;

        // Solicitar la categoría del plato y agregarla a la lista de categorías si es necesario
        cout << "\tCategoria de plato: ";
        cin >> ws;
        getline(cin, categoria);
        strncpy(plato.categoria, categoria.c_str(), sizeof(plato.categoria));
        agregarCategoria(plato.categoria, categorias);

        do {
            // Solicitar el nombre del plato
            cout << "\tNombre de plato: ";
            getline(cin, nombre);
            strncpy(plato.nombre, nombre.c_str(), sizeof(plato.nombre));

            // Solicitar el precio del plato con validación
            cout << "\tPrecio del plato: ";
            while (!(cin >> precio) || precio < 0) {
                cout << "\tCantidad invalida. Ingrese un numero valido: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            plato.precio = precio;

            // Guardar el plato en el archivo principal y el archivo secundario
            file.write(reinterpret_cast<char*>(&plato), sizeof(Plato));
            fwrite(&plato, sizeof(Plato), 1, archivoSecundario);

            cout << "\n\tPlato creado con exito\n" << endl;

            // Preguntar si desea continuar creando platos en la misma categoría
            cout << "\n\tSeguir creando platos de la misma categoria? (s/n): ";
            cin >> continuarPlato;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } while (continuarPlato == 's' || continuarPlato == 'S');

        // Preguntar si desea continuar creando platos en una nueva categoría
        cout << "\n\tSeguir creando platos en otra categoria? (s/n): ";
        cin >> continuarCategoria;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (continuarCategoria == 's' || continuarCategoria == 'S');

    // Actualizar el archivo del contador de IDs
    fstream archivoContador("contador_id.txt", ios::in | ios::out);
    archivoContador.seekp(0, ios::beg);
    archivoContador << idNuevo;  // Escribimos el último ID usado

    cout << endl << "Creacion de platos finalizada!" << endl;

    file.close();
    fclose(archivoSecundario);
    archivoContador.close();
    getch();
}


inline void leerPlatos(const string& archivo) {
    limpiarPantalla();
    ifstream file(archivo, ios::binary);
    if (!file.is_open()) {
        cout << "Error al abrir el archivo " << archivo << endl;
        return;
    }

    Plato plato;
    file.seekg(0, ios::end);
    size_t numPlatos = file.tellg() / sizeof(Plato);
    file.seekg(0, ios::beg);

    if (numPlatos == 0) {
        cout << "\nNo hay platos registrados en el archivo." << endl;
        getch();
        return;
    }

    cout << "\n> Lista de Platos\n" << endl;
    while (file.read(reinterpret_cast<char*>(&plato), sizeof(Plato))) {
        // Mostrar solo los campos relevantes (sin cantidad, id y comentario)
        cout << "\tCategoria: " << plato.categoria << endl;
        cout << "\tNombre: " << plato.nombre << endl;

        // Mostrar el precio con 2 decimales
        cout << fixed << setprecision(2); // Fijar formato de punto decimal
        cout << "\tPrecio: " << plato.precio << endl;

        cout << "-----------------------------------" << endl;
    }

    cout << "\nProceso de lectura finalizado." << endl;
    getch();
}


inline void actualizarPlato(const string& archivo) {
    limpiarPantalla();
    fstream file(archivo, ios::binary | ios::in | ios::out);
    FILE *archivoSecundario = fopen("Platos.dat", "r+b");

    if (!file.is_open() || archivoSecundario == nullptr) {
        cout << "Error al abrir el archivo " << archivo << " o Platos.dat" << endl;
        return;
    }

    string nombreBuscado;
    bool encontrado = false;
    cout << "Ingresa el nombre del plato a actualizar: ";
    cin >> ws;
    getline(cin, nombreBuscado);

    // Convertir la entrada del usuario a minúsculas
    convertirAMinusculas(nombreBuscado);

    Plato plato{};  // Para leer el plato del archivo
    Plato platoSecundario{};  // Para leer el plato desde el archivo secundario
    int posicionSecundaria = -1;

    // Buscar y actualizar el plato en el archivo principal
    while (file.read(reinterpret_cast<char*>(&plato), sizeof(Plato))) {
        // Convertir el nombre del plato a minúsculas para la comparación
        string nombrePlato = plato.nombre;
        convertirAMinusculas(nombrePlato);

        if (nombreBuscado == nombrePlato) {
            limpiarPantalla();
            encontrado = true;
            cout << fixed << setprecision(2);
            cout << "Plato encontrado:\nNombre: " << plato.nombre << ", Precio: " << plato.precio << ", Estado: " << (plato.estado ? "Activado" : "Desactivado") << endl << endl;

            mostrarHistorialPlato(plato.id);

            // Actualización de nombre
            cout << endl << "Nuevo nombre (dejar en blanco para no cambiar): ";
            string nuevoNombre;
            getline(cin, nuevoNombre);
            if (!nuevoNombre.empty()) {
                registrarCambio(plato.id, "Nombre", plato.nombre, nuevoNombre);
                strncpy(plato.nombre, nuevoNombre.c_str(), sizeof(plato.nombre) - 1);
                plato.nombre[sizeof(plato.nombre) - 1] = '\0';
            }

            // Actualización de precio
            cout << "Nuevo precio (dejar en blanco para no cambiar): ";
            string entradaPrecio;
            getline(cin, entradaPrecio);
            if (!entradaPrecio.empty()) {
                try {
                    double nuevoPrecio = stod(entradaPrecio);
                    registrarCambio(plato.id, "Precio", to_string(plato.precio), entradaPrecio);
                    plato.precio = nuevoPrecio;
                } catch (const invalid_argument&) {
                    cout << "Precio invalido, no se actualizo el precio." << endl;
                }
            }

            // Actualización de estado
            cout << "Nuevo estado (1=Activado, 0=Desactivado, dejar en blanco para no cambiar): ";
            string entradaEstado;
            getline(cin, entradaEstado);
            if (!entradaEstado.empty()) {
                bool nuevoEstado = (entradaEstado == "1");
                registrarCambio(plato.id, "Estado", plato.estado ? "1" : "0", nuevoEstado ? "1" : "0");
                plato.estado = nuevoEstado;
            }

            // Reposicionar el puntero para sobrescribir en el archivo principal
            file.seekp(-static_cast<int>(sizeof(Plato)), ios::cur);
            file.write(reinterpret_cast<char*>(&plato), sizeof(Plato));

            // Buscar y actualizar el plato en el archivo secundario
            while (fread(&platoSecundario, sizeof(Plato), 1, archivoSecundario)) {
                if (platoSecundario.id == plato.id) {
                    // Encontrado el plato en el archivo secundario, actualizamos la información
                    posicionSecundaria = ftell(archivoSecundario) - sizeof(Plato);
                    fseek(archivoSecundario, posicionSecundaria, SEEK_SET);
                    fwrite(&plato, sizeof(Plato), 1, archivoSecundario);
                    break;
                }
            }

            cout << "Plato actualizado correctamente." << endl;
            break;
        }
    }

    if (!encontrado) {
        cout << "El plato no se encontro en el archivo." << endl;
    }

    file.close();
    fclose(archivoSecundario);
    getch();
}

inline string tipoPlato() {
    const char* titulo = "SELECCIONAR TIPO DE PLATO";
    const char* opciones[] = { "Entradas", "Segundos", "Bebidas", "ATRAS" };
    int m = 4; // Número de opciones
    int opcion;

    // Bucle para manejar la selección del tipo de plato
    do {
        limpiarPantalla();
        cuadro(0, 0, 119, 29);
        cuadro(8, 1, 110, 3);
        opcion = menus(titulo, opciones, m);

        switch (opcion) {
            case 1: return "entradas.bin";
            case 2: return "segundos.bin";
            case 3: return "bebidas.bin";
            case 4: return ""; // "ATRAS" o salir del menú
            default:
                cout << "Opcion no valida. Intenta nuevamente.\n";
            getch();
            break;
        }
    } while (true); // Repetir hasta que se seleccione una opción válida
}


inline void menuGestionarMenu() {
    int opt;
    vector<string> categoria;
    cargarCategorias(categoria);
    bool repite = true;
    const char* titulo = "GESTION DEL MENU";
    const char* opciones[] = { "Agregar Platos", "Ver platos", "Actualizar Plato", "ATRAS" };
    int m = 4;
    string tipo;

    cuadro(0, 0, 119, 29);
    cuadro(8, 1, 110, 3);

    do {
        opt = menus(titulo, opciones, m);
        switch (opt) {
            case 1: {
                tipo = tipoPlato();
                if (tipo.empty()) break; // Regresar si se selecciona "ATRAS"
                agregarPlatos(tipo, categoria);
                break;
            }
            case 2: {
                tipo = tipoPlato();
                if (tipo.empty()) break; // Regresar si se selecciona "ATRAS"
                leerPlatos(tipo);
                break;
            }
            case 3: {
                tipo = tipoPlato();
                if (tipo.empty()) break; // Regresar si se selecciona "ATRAS"
                actualizarPlato(tipo);
                break;
            }
            case 4: {
                repite = false;
                break;
            }
        }
    } while (repite);
}

#endif //GESTIONMENU_H