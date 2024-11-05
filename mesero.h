#ifndef MESERO_H
#define MESERO_H

#include <iostream>
#include <vector>
#include "cocinero.h"  // Importamos el header de cocin
using namespace std;

void iniciarMesero();
void crearPedido();
Platillo ingresarPlatillo();
Pedido generarPedidoMesero();

// Implementación del menú del mesero
void iniciarMesero() {
    int opcion;
    do {
        system("CLS");
        cout << "===== Menu Mesero =====" << endl;
        cout << "1. Crear pedido" << endl;
        cout << "2. Volver" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                crearPedido();
                break;
            case 2:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
                break;
        }
    } while (opcion != 2);
}

// Función para crear un pedido
void crearPedido() {
    system("CLS");
    cout << "===== Crear Pedido =====" << endl;

    Pedido nuevoPedido = generarPedidoMesero();  // Generamos un nuevo pedido
    pedidos.push_back(nuevoPedido);  // Lo agregamos al vector de pedidos

    cout << "Pedido #" << nuevoPedido.numeroOrden << " creado con exito." << endl;
    cout << "\nPresione cualquier tecla para volver al menu...";
    cin.ignore();
    cin.get();
}

// Función para ingresar un platillo al pedido
Platillo ingresarPlatillo() {
    Platillo platillo;
    cout << "Ingrese el nombre del platillo: ";
    cin.ignore();  // Limpiar el buffer
    getline(cin, platillo.nombre);
    cout << "Ingrese la cantidad: ";
    cin >> platillo.cantidad;
    cout << "Ingrese el precio: ";
    cin >> platillo.precio;
    return platillo;
}

// Función para generar un nuevo pedido
Pedido generarPedidoMesero() {
    Pedido pedido;
    cout << "Numero de orden: ";
    cin >> pedido.numeroOrden;
    cout << "Numero de mesa: ";
    cin >> pedido.numeroMesa;
    cout << "Nombre del mesero: ";
    cin.ignore();
    getline(cin, pedido.mesero);
    cout << "Prioridad (Alta/Normal/Baja): ";
    getline(cin, pedido.prioridad);

    // Agregamos platillos al pedido
    int cantidadPlatillos;
    cout << "Cuantos platillos desea agregar? ";
    cin >> cantidadPlatillos;
    for (int i = 0; i < cantidadPlatillos; ++i) {
        cout << "\nPlatillo #" << i + 1 << ":\n";
        pedido.platillos.push_back(ingresarPlatillo());
    }

    // Agregamos comentarios al pedido
    int cantidadComentarios;
    cout << "\nCuantos comentarios desea agregar? ";
    cin >> cantidadComentarios;
    cin.ignore();  // Limpiar el buffer
    for (int i = 0; i < cantidadComentarios; ++i) {
        string comentario;
        cout << "Comentario #" << i + 1 << ": ";
        getline(cin, comentario);
        pedido.comentarios.push_back(comentario);
    }

    return pedido;
}

#endif
