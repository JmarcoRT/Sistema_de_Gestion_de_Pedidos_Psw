
#ifndef MISORDENES_H
#define MISORDENES_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include "utils.h"
#include "menuMesero.h"

using namespace std;

inline void verDetalles() {
    system("cls");
    cout << "Cargando detalles..." << endl;
    getch();
}




inline void finalizarOrden() {
    system("cls");
    cout << R"(

    _____ _         _ _                          _
   |   __|_|___ ___| |_|___ ___ ___    ___ ___ _| |___ ___
   |   __| |   | .'| | |- _| .'|  _|  | . |  _| . | -_|   |
   |__|  |_|_|_|__,|_|_|___|__,|_|    |___|_| |___|___|_|_|

    )" << endl;
    cout << "Mesas con órdenes pendientes:\n";

    FILE* archivo = fopen("Ordenes.dat", "rb+");
    if (archivo == nullptr) {
        cout << "No se pudo acceder a las órdenes.\n";
        system("pause");
        return;
    }

    //Se mostrarán las mesas con órdenes pendientes, verificando primero el estado de la orden
    Orden o;
    size_t numPlatos;
    bool hayOrdenesPendientes = false;
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
        if (strcmp(o.estado, "pendiente") == 0) {
            cout << "Mesa " << o.numeroMesa << endl;
            hayOrdenesPendientes = true;
        }
    }
    if (!hayOrdenesPendientes) {
        cout << "No hay órdenes pendientes.\n";
        fclose(archivo);
        system("pause");
        return;
    }
    rewind(archivo);

    //Se pide ingresar el numero de la mesa para finalizar esa orden
    int numeroMesa;
    cout << "\nIngrese el número de la mesa para finalizar la orden: ";
    cin >> numeroMesa;
    if (cin.fail() || numeroMesa <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Número de mesa inválido. Intente nuevamente.\n";
        fclose(archivo);
        system("pause");
        return;
    }
    bool ordenEncontrada = false;
    long posicion = 0;

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
            ordenEncontrada = true;
            if (strcmp(o.estado, "finalizado") == 0) {
                cout << "La orden de la mesa " << numeroMesa << " ya ha sido finalizada.\n";
                fclose(archivo);
                system("pause");
                return;
            }
            posicion = ftell(archivo) - (sizeof(o.numeroMesa) + sizeof(o.hora) + sizeof(o.estado) + sizeof(size_t) + numPlatos * sizeof(Plato));
            break;
        }
    }

    if (!ordenEncontrada) {
        cout << "No se encontró una orden para la mesa " << numeroMesa << ".\n";
        fclose(archivo);
        system("pause");
        return;
    }

    cout << "\n¿Está seguro de que desea finalizar la orden? (Se generará la boleta de venta y el pedido se marcará como finalizado)\n";
    cout << "Presione 1 para confirmar o 0 para cancelar: ";
    int confirmacion;
    cin >> confirmacion;

    if (confirmacion != 1) {
        cout << "Operación cancelada.\n";
        fclose(archivo);
        system("pause");
        return;
    }

    //Se genera la boleta
    system("cls");
    cout << "Generando boleta...\n\n";

    double total = 0;
    for (const auto& plato : o.platos) {
        cout << plato.cantidad << "x " << plato.nombre << "   $" << plato.precio * plato.cantidad << "\n";
        total += plato.precio * plato.cantidad;
    }
    cout << "----------------------------------------\n";
    cout << "TOTAL: $" << total << "\n";

    //Se guarda la boleta como un archivo txt
    string nombreArchivo = "boleta_mesa_" + to_string(o.numeroMesa) + ".txt";
    ofstream boletaArchivo(nombreArchivo);

    if (boletaArchivo.is_open()) {
        boletaArchivo << "Boleta de Venta - Mesa M" << o.numeroMesa << "\n";
        for (const auto& plato : o.platos) {
            boletaArchivo << plato.cantidad << "x " << plato.nombre << "   $" << plato.precio * plato.cantidad << "\n";
        }
        boletaArchivo << "TOTAL: $" << total << "\n";
        boletaArchivo.close();
        cout << "La boleta se ha descargado y guardado como " << nombreArchivo << ".\n";
    } else {
        cout << "No se pudo generar la boleta.\n";
        fclose(archivo);
        system("pause");
        return;
    }

    //Se actualiza el estado de la orden de pendiente a finalizado
    strcpy(o.estado, "finalizado");
    fseek(archivo, posicion, SEEK_SET);
    fwrite(&o.numeroMesa, sizeof(o.numeroMesa), 1, archivo);
    fwrite(&o.hora, sizeof(o.hora), 1, archivo);
    fwrite(o.estado, sizeof(o.estado), 1, archivo);
    fwrite(&numPlatos, sizeof(size_t), 1, archivo);
    for (const auto& plato : o.platos) {
        fwrite(&plato, sizeof(Plato), 1, archivo);
    }

    fclose(archivo);
    cout << "\nOrden finalizada exitosamente.\n";
    system("pause");
}




#endif //MISORDENES_H
