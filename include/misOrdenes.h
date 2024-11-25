
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
    cout << "Mesas con órdenes atendidas:\n";

    FILE* archivo = fopen("Ordenes.dat", "rb+");
    if (archivo == nullptr) {
        cout << "No se pudo acceder a las órdenes.\n";
        system("pause");
        return;
    }

    //Se mostrarán las mesas con órdenes atendidas, verificando primero el estado de la orden
    Orden o;
    size_t numPlatos;
    bool hayOrdenesAtendidas = false;
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
        if (strcmp(o.estado, "atendido") == 0) {
            cout << "Mesa " << o.numeroMesa << endl;
            hayOrdenesAtendidas = true;
        }
           }
    if (!hayOrdenesAtendidas) {
        cout << "No hay órdenes atendidas.\n";
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
            if (strcmp(o.estado, "pendiente") == 0) {
                cout << "La orden de la mesa " << numeroMesa << " no puede ser finalizada, ya que sigue pendiente.\n";
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

    cout << "                 BOLETA\n\n";
    cout << "        RAZON SOCIAL: TANTA KENNEDY\n";
    cout << "              RUT: 76.064.319-K\n";
    cout << "           GIRO: RESTAURANTES\n";
    cout << "   LOCAL: AV. KENNEDY 5413 LOC 371\n";
    cout << "        LAS CONDES - SANTIAGO\n\n";

    for (const auto& plato : o.platos) {
        cout << std::setw(2) << plato.cantidad << "X ";
        cout << std::left << std::setw(15) << plato.nombre;
        cout << "$" << std::right << std::setw(10) << plato.precio * plato.cantidad << "\n";
        total += plato.precio * plato.cantidad;
    }

    cout << "----------------------------------------\n";
    cout << "TOTAL                             $" << total << "\n\n";

    cout << "Tienda:           TANTA PARQUE ARAUCO\n";
    cout << "Fecha:            " << formato_hora(o.hora) << "\n";
    cout << "Atendido por:     Liliana Jimenez\n";
    cout << "Mesa:             M" << o.numeroMesa << "\n";
    cout << "----------------------------------------\n";

    //Se guarda la boleta como un archivo txt
    string nombreArchivo = "boleta_mesa_" + to_string(o.numeroMesa) + ".txt";
    ofstream boletaArchivo(nombreArchivo);

    if (boletaArchivo.is_open()) {
        boletaArchivo << "                 BOLETA\n\n";
        boletaArchivo << "        RAZON SOCIAL: TANTA KENNEDY\n";
        boletaArchivo << "              RUT: 76.064.319-K\n";
        boletaArchivo << "           GIRO: RESTAURANTES\n";
        boletaArchivo << "   LOCAL: AV. KENNEDY 5413 LOC 371\n";
        boletaArchivo << "        LAS CONDES - SANTIAGO\n\n";
        for (const auto& plato : o.platos) {
            boletaArchivo << setw(2) << plato.cantidad << "X ";
            boletaArchivo << left << setw(15) << plato.nombre;
            boletaArchivo << "$" << right << setw(10) << plato.precio * plato.cantidad << "\n";
        }
        boletaArchivo << "----------------------------------------\n";
        boletaArchivo << "TOTAL                             $" << total << "\n\n";

        boletaArchivo << "Tienda:           TANTA PARQUE ARAUCO\n";
        boletaArchivo << "Fecha:            " << formato_hora(o.hora) << "\n";
        boletaArchivo << "Atendido por:     Liliana Jimenez\n";
        boletaArchivo << "Mesa:             M" << o.numeroMesa << "\n";
        boletaArchivo << "----------------------------------------\n";
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
