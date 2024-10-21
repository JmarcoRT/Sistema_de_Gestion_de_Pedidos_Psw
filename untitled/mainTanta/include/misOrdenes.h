
#ifndef MISORDENES_H
#define MISORDENES_H

#include <iostream>
#include <conio.h>
using namespace std;

inline void verDetalles() {
    system("cls");
    cout << "Cargando detalles..." << endl;
    getch();
}

inline void actualizarOrden() {
    system("cls");
    cout << "Actualizando ordenes..." << endl;
    getch();
}

inline void finalizarOrden() {
    system("cls");
    cout << "Finalizando orden (generando boleta)..." << endl;
    getch();
}

inline void cancelarOrden() {
    system("cls");
    cout << "Cancelando orden..." << endl;
    getch();
}

inline void menuOrdenes() {
    int opcion;

    do {
        system("cls");
        cout << "MIS ORDENES" << endl;
        cout << "1. Ver detalles." << endl;
        cout << "2. Actualizar orden." << endl;
        cout << "3. Finalizar orden." << endl;
        cout << "4. Cancelar orden." << endl;
        cout << "5. Salir." << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                verDetalles();
            break;
            case 2:
                actualizarOrden();
            break;
            case 3:
                finalizarOrden();
            break;
            case 4:
                cancelarOrden();
            break;
            case 5:
                cout << "Saliendo del menú..." << endl;
            break;
            default:
                cout << "¡Seleccione una opción valida!" << endl;
            getch();
            break;
        }
    } while (opcion != 5);
}
#endif //MISORDENES_H
