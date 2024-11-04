#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <conio.h>
#include "gestionMenu.h"
#include "historialVentas.h"
#include "informeVentas.h"
#include "utilidades.h"
using namespace std;


void admin() {
    string usuario;
    do {
        system("cls");
        cuadro(0,0,119,29);

        gotoxy(2,4); cout << "Introduzca el  (0 para salir): ";
        gotoxy(2,5); cin >> usuario;

        if (usuario == "0") {
            return; // Salir si se ingresa "0"
        } else if (usuario != "jefe") {
            gotoxy(2,6); cout << "El usuario es invalido" << endl;
            getch();
        }
    } while (usuario != "jefe");

    // Usuario autenticado correctamente
    int opt;
    bool repite = true;
    const char *titulo = "Bienvenido al modulo ADMIN";
    const char *opciones[] = {"Gestionar menu", "Historial de pedidos", "Informe semanal de ventas", "SALIR"};
    int m = 4;

    do {
        system("cls");
        cuadro(0,0,119,29);
        cuadro(8,1,110,3);

        opt = menus(titulo, opciones, m);
        switch (opt) {
            case 1:
                menuGestionarMenu();
                break;
            case 2:
                menuHistorialVentas();
                break;
            case 3:
                menuInformeVentas();
                break;
            case 4:
                repite = false;
                break;
        }
    } while (repite);
}


#endif //ADMIN_H
