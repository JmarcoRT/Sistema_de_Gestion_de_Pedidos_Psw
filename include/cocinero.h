#ifndef COCINA_H
#define COCINA_H
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdio> // Para manejo de archivos
#include <cstring> // Para funciones de manejo de cadenas
#include "utils.h" // Incluir utils.h para la estructura Orden y utilidades
using namespace std;

// Vector global para almacenar los pedidos
vector<Orden> pedidos;

// Declaración de funciones
void iniciarCocina();
void cargarPedidosDesdeArchivo();
void verPedidos();
void atenderPedidos();
void aceptarPedido(int);
void cancelarPlato(int);
void completarPedido(int);
void verCambiosOrden(int);

// Implementación de funciones
void cargarPedidosDesdeArchivo() {
    pedidos.clear();
    FILE *archivo = fopen("Ordenes.dat", "rb");
    if (archivo == nullptr) {
        cout << "No se encontraron pedidos almacenados." << endl;
        return;
    }

    Orden o;
    size_t numPlatos;
    while (fread(&o.numeroMesa, sizeof(int), 1, archivo) &&
           fread(&o.hora, sizeof(Fecha), 1, archivo) &&
           fread(o.estado, sizeof(o.estado), 1, archivo) &&
           fread(&numPlatos, sizeof(size_t), 1, archivo)) {

        o.platos.clear();
        for (size_t i = 0; i < numPlatos; ++i) {
            Plato p;
            fread(&p, sizeof(Plato), 1, archivo);
            o.platos.push_back(p);
        }

        pedidos.push_back(o);
    }

    fclose(archivo);
}

void iniciarCocina() {
    cargarPedidosDesdeArchivo();
    int opt;
    bool repite = true;
    const char *titulo = "MENU COCINA";
    const char *opciones[] = {"Ver pedidos", "Atender pedidos", "Ver cambios en una orden", "SALIR"};
    int m = 4;
    do {
        system("cls");
        cuadro(0, 0, 119, 29);
        cuadro(8, 1, 110, 3);
        opt = menus(titulo, opciones, m);

        switch (opt) {
            case 1:
                verPedidos();
                break;
            case 2:
                atenderPedidos();
                break;
            case 3:
                system("cls");
                int numeroOrden;
                cout << "Ingrese el numero de orden: ";
                cin >> numeroOrden;
                verCambiosOrden(numeroOrden);
                break;
            case 4:
                repite = false;
                break;
        }
    } while (repite);
}

void verPedidos() {
    system("CLS");
    FILE *archivo = fopen("Ordenes.dat", "rb");
    if (archivo == nullptr) {
        cout << "Error al abrir el archivo de pedidos." << endl;
        return;
    }

    Orden o;
    size_t numPlatos;

    cout << "===== Pedidos Actuales =====" << endl;

    while (fread(&o.numeroMesa, sizeof(int), 1, archivo) &&
           fread(&o.hora, sizeof(Fecha), 1, archivo) &&
           fread(o.estado, sizeof(o.estado), 1, archivo) &&
           fread(&numPlatos, sizeof(size_t), 1, archivo)) {

        o.platos.clear();
        for (size_t i = 0; i < numPlatos; ++i) {
            Plato p;
            fread(&p, sizeof(Plato), 1, archivo);
            o.platos.push_back(p);
        }

        // Mostrar los detalles de la orden
        cout << "Numero de mesa: " << o.numeroMesa << endl;
        cout << "Fecha: " << formato_hora(o.hora) << endl;
        cout << "Estado: " << o.estado << endl;

        cout << "Platos en la orden:" << endl;
        for (const auto& plato : o.platos) {
            cout << "- " << plato.nombre << " ($" << plato.precio << "), Cantidad: " << plato.cantidad
                 << ", Comentario: " << plato.comentario << endl;
        }
        cout << "\n";
    }

    fclose(archivo);
    cout << "\nPresione cualquier tecla para volver al menu principal...";
    cin.ignore();
    cin.get();
}

void atenderPedidos() {
    system("CLS");
    int numeroMesa;
    cout << "===== Atender Pedido =====" << endl;
    cout << "Ingrese el numero de mesa a atender: ";
    cin >> numeroMesa;

    bool encontrado = false;
    FILE *archivo = fopen("Ordenes.dat", "r+b");
    if (archivo == nullptr) {
        cout << "Error al abrir el archivo de órdenes." << endl;
        return;
    }

    Orden o;
    size_t numPlatos;
    while (fread(&o.numeroMesa, sizeof(int), 1, archivo) &&
           fread(&o.hora, sizeof(Fecha), 1, archivo) &&
           fread(o.estado, sizeof(o.estado), 1, archivo) &&
           fread(&numPlatos, sizeof(size_t), 1, archivo)) {

        o.platos.clear();
        for (size_t i = 0; i < numPlatos; ++i) {
            Plato p;
            fread(&p, sizeof(Plato), 1, archivo);
            o.platos.push_back(p);
        }

        if (o.numeroMesa == numeroMesa) {
            encontrado = true;
            // Cambiar el estado a "atendido"
            strcpy(o.estado, "atendido");

            // Reposicionar el puntero de archivo para sobrescribir la orden
            fseek(archivo, -static_cast<int>(sizeof(int) + sizeof(Fecha) + sizeof(o.estado) + sizeof(size_t) + numPlatos * sizeof(Plato)), SEEK_CUR);

            fwrite(&o.numeroMesa, sizeof(int), 1, archivo);
            fwrite(&o.hora, sizeof(Fecha), 1, archivo);
            fwrite(o.estado, sizeof(o.estado), 1, archivo);
            fwrite(&numPlatos, sizeof(size_t), 1, archivo);
            for (const auto& plato : o.platos) {
                fwrite(&plato, sizeof(Plato), 1, archivo);
            }

            cout << "Pedido de la mesa #" << numeroMesa << " atendido." << endl;
            break;
        }
    }

    fclose(archivo);

    if (!encontrado) {
        cout << "Orden no encontrada." << endl;
    }

    cout << "\nPresione cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

void verCambiosOrden(int numeroOrden) {
    system("CLS");
    bool encontrado = false;

    for (const auto& pedido : pedidos) {
        if (pedido.numeroMesa == numeroOrden) {
            encontrado = true;
            cout << "===== Detalles de la Orden #" << pedido.numeroMesa << " =====" << endl;
            cout << "Estado: " << pedido.estado << endl;

            for (const auto& plato : pedido.platos) {
                cout << "- " << plato.nombre << " ($" << plato.precio << "), Cantidad: " << plato.cantidad
                     << ", Comentario: " << plato.comentario << endl;
            }

            break;
        }
    }

    if (!encontrado) {
        cout << "Orden no encontrada." << endl;
    }

    cout << "\nPresione cualquier tecla para volver al menu principal...";
    cin.ignore();
    cin.get();
}

#endif // COCINA_H