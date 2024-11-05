#ifndef COCINA_H
#define COCINA_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Estructura para almacenar los platillos
struct Platillo {
    string nombre;
    int cantidad;
    double precio;
};

// Estructura para registrar los cambios realizados en una orden
struct Cambio {
    string nombrePlatillo;
    int cantidadAntes;
    int cantidadDespues;
    string motivo;
};

// Estructura para almacenar los pedidos
struct Pedido {
    int numeroOrden;
    int numeroMesa;
    string mesero;
    string prioridad;
    vector<Platillo> platillos;
    vector<string> comentarios;
    bool atendido = false;  // Estado del pedido
    vector<Cambio> cambios; // Vector para registrar los cambios
};

// Vector global para almacenar los pedidos
vector<Pedido> pedidos;

// Declaracion de funciones
void iniciarCocina();
void verPedidos();
void atenderPedidos();
void generarPedido();
void aceptarPedido(int);
void cancelarPlato(int);
void completarPedido(int);
void verCambiosOrden(int);

// Implementacion de funciones
void iniciarCocina() {
    int opcion;
    do {
        system("CLS");
        cout << "===== Menu Cocina =====" << endl;
        cout << "1. Ver pedidos" << endl;
        cout << "2. Atender pedidos" << endl;
        cout << "3. Salir" << endl;
        cout << "4. Generar pedido" << endl;
        cout << "5. Ver cambios en una orden" << endl;
        cout << "Ingresa una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                verPedidos();
                break;
            case 2:
                atenderPedidos();
                break;
            case 3:
                break;
            case 4: {
                generarPedido();
                break;
            }
            case 5: 
                int numeroOrden;
                cout << "Ingrese el numero de orden: ";
                cin >> numeroOrden;
                verCambiosOrden(numeroOrden);
                break;
            default:
                cout << "Opcion fuera de rango." << endl;
                break;
        }
    } while (opcion < 1 || opcion > 5);
}

void verPedidos() {
    system("CLS");
    cout << "===== Pedidos Actuales =====" << endl;
    for (const auto& pedido : pedidos) {
        cout << "Orden #" << pedido.numeroOrden << " - Mesa #" << pedido.numeroMesa
             << " - Prioridad: " << pedido.prioridad << endl;
    }
    cout << "\nPresione cualquier tecla para volver al menu principal...";
    cin.ignore();
    cin.get();
}

void generarPedido() {
    system("CLS");
    Pedido nuevoPedido;

    cout << "Numero de orden: ";
    cin >> nuevoPedido.numeroOrden;
    cout << "Numero de mesa: ";
    cin >> nuevoPedido.numeroMesa;
    cout << "Nombre del mesero: ";
    cin.ignore();  
    getline(cin, nuevoPedido.mesero);
    cout << "Prioridad (Alta/Normal/Baja): ";
    getline(cin, nuevoPedido.prioridad);

    int cantidadPlatillos;
    cout << "Cuantos platillos desea agregar? ";
    cin >> cantidadPlatillos;

    for (int i = 0; i < cantidadPlatillos; ++i) {
        Platillo platillo;
        cout << "\nPlatillo #" << i + 1 << ":\n";
        cout << "Nombre: ";
        cin.ignore();
        getline(cin, platillo.nombre);
        cout << "Cantidad: ";
        cin >> platillo.cantidad;
        cout << "Precio: ";
        cin >> platillo.precio;
        nuevoPedido.platillos.push_back(platillo);
    }

    int cantidadComentarios;
    cout << "\nCuantos comentarios desea agregar? ";
    cin >> cantidadComentarios;
    cin.ignore();

    for (int i = 0; i < cantidadComentarios; ++i) {
        string comentario;
        cout << "Comentario #" << i + 1 << ": ";
        getline(cin, comentario);
        nuevoPedido.comentarios.push_back(comentario);
    }

    pedidos.push_back(nuevoPedido);
    cout << "\nPedido #" << nuevoPedido.numeroOrden << " generado con exito!" << endl;
    cout << "Presione cualquier tecla para volver al menu principal...";
    cin.ignore();
    cin.get();
}

void atenderPedidos() {
    system("CLS");
    int numeroOrden;
    cout << "===== Atender Pedido =====" << endl;
    cout << "Ingrese el numero de orden a atender: ";
    cin >> numeroOrden;

    bool encontrado = false;
    for (size_t i = 0; i < pedidos.size(); ++i) {
        if (pedidos[i].numeroOrden == numeroOrden) {
            encontrado = true;
            int opcion;
            do {
                system("CLS");
                cout << "===== Detalles de la Orden #" << numeroOrden << " =====" << endl;
                cout << "Mesa: " << pedidos[i].numeroMesa << endl;
                cout << "Mesero: " << pedidos[i].mesero << endl;
                cout << "Prioridad: " << pedidos[i].prioridad << endl;

                for (const auto& platillo : pedidos[i].platillos) {
                    cout << "- " << platillo.nombre << " x" << platillo.cantidad 
                         << " - Precio: S/." << fixed << setprecision(2) << platillo.precio << endl;
                }

                cout << "\n1. Aceptar pedido" << endl;
                cout << "2. Cancelar plato" << endl;
                cout << "3. Completar pedido" << endl;
                cout << "4. Volver" << endl;
                cout << "Seleccione una opcion: ";
                cin >> opcion;

                switch (opcion) {
                    case 1:
                        aceptarPedido(i);
                        break;
                    case 2:
                        cancelarPlato(i);
                        break;
                    case 3:
                        completarPedido(i);
                        return;
                    case 4:
                        break;
                    default:
                        cout << "Opcion fuera de rango." << endl;
                        break;
                }
            } while (opcion != 4);
        }
    }

    if (!encontrado) {
        cout << "Orden no encontrada." << endl;
        cin.ignore();
        cin.get();
    }
}

void aceptarPedido(int index) {
    system("CLS");
    cout << "Pedido #" << pedidos[index].numeroOrden << " aceptado con exito." << endl;
    pedidos[index].atendido = true;  // Marcar el pedido como atendido
    cin.ignore();
    cin.get();
}

void cancelarPlato(int index) {
    system("CLS");
    cout << "Seleccione el numero del plato a cancelar:\n";

    for (size_t j = 0; j < pedidos[index].platillos.size(); ++j) {
        cout << j + 1 << ". " << pedidos[index].platillos[j].nombre 
             << " x" << pedidos[index].platillos[j].cantidad << endl;
    }

    size_t opcion;
    cin >> opcion;

    if (opcion > 0 && opcion <= pedidos[index].platillos.size()) {
        Platillo& platillo = pedidos[index].platillos[opcion - 1];
        int cantidadAntes = platillo.cantidad;
        platillo.cantidad--;

        string motivo;
        cout << "Ingrese el motivo de la eliminacion: ";
        cin.ignore();
        getline(cin, motivo);

        Cambio nuevoCambio = {
            platillo.nombre,
            cantidadAntes,
            platillo.cantidad,
            motivo
        };
        pedidos[index].cambios.push_back(nuevoCambio);

        if (platillo.cantidad == 0) {
            pedidos[index].platillos.erase(pedidos[index].platillos.begin() + opcion - 1);
        }
    }
}

void completarPedido(int index) {
    system("CLS");
    cout << "Pedido #" << pedidos[index].numeroOrden << " completado." << endl;

    string motivo;
    cout << "Ingrese el motivo de finalizacion del pedido: ";
    cin.ignore();
    getline(cin, motivo);

    Cambio nuevoCambio = {
        "Pedido completo", 0, 0, motivo
    };
    pedidos[index].cambios.push_back(nuevoCambio);

    pedidos.erase(pedidos.begin() + index);
    cout << "Pedido eliminado con exito." << endl;

    cin.ignore();
    cin.get();
}

void verCambiosOrden(int numeroOrden) {
    system("CLS");
    bool encontrado = false;

    for (const auto& pedido : pedidos) {
        if (pedido.numeroOrden == numeroOrden) {
            encontrado = true;
            cout << "===== Cambios en la Orden #" << pedido.numeroOrden << " =====" << endl;

            if (pedido.cambios.empty()) {
                cout << "No se han realizado cambios en esta orden." << endl;
            } else {
                for (const auto& cambio : pedido.cambios) {
                    cout << "- Platillo: " << cambio.nombrePlatillo << endl;
                    cout << "  Cantidad Antes: " << cambio.cantidadAntes 
                         << " | Cantidad Despues: " << cambio.cantidadDespues << endl;
                    cout << "  Motivo: " << cambio.motivo << endl;
                }
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
    iniciarCocina();
}

#endif
