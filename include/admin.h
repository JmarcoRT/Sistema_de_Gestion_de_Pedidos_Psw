#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <conio.h>
#include "gestionMenu.h"
#include "historialVentas.h"
#include "informeVentas.h"

using namespace std;

inline void menuAdmin() {
    cout << "Bienvenido al modulo ADMIN" << endl;
    cout << "1. Gestionar menu" << endl;
    cout << "2. Historial de pedidos" << endl;
    cout << "3. Informe semanal de ventas" << endl;
    cout << "0. Salir" << endl << endl;
    cout << "Seleccione su opcion-->";
}

inline void admin() {

    int op;

    do {
        system("cls");
        menuAdmin();
        cin >> op;

        switch (op) {
            case 1: {
                menuGestionarMenu();
                break;
            }
            case 2: {
                menuHistorialVentas();
                break;
            }
            case 3: {
                menuInformeVentas();
                break;
            }
            case 0: {
                cout << "Hasta luego!" << endl;
                getch();
                break;
            }
            default: {
                cout << "Opcion invalida" << endl;
                getch();
            }
        }
    }while(op != 0);
}


#endif //ADMIN_H
