#ifndef MENUMESERO_H
#define MENUMESERO_H

#include "utils.h"
#include "misOrdenes.h"
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

inline void verOrdenes() {
    system("cls");
    std::cout << "MIS ORDENES" << std::endl;

    for (int i = 0; i < std::size(ordenes); i++) {
        std::cout << i + 1 << ". Orden #" << ordenes[i].id << " a las " << ordenes[i].hora << ". Estado: " << ordenes[i].estado << std::endl;
    }

    std::cout << "Seleccione una orden para ver detalles (presione 0 para regresar): ";
    int seleccion;
    std::cin >> seleccion;

    if (seleccion > 0 && seleccion <= std::size(ordenes)) {
        menuOrdenes();
    } else if (seleccion == 0) {
    } else {
        std::cout << "Selección inválida." << std::endl;
        getch();
    }
}

inline void menuMesero() {
    int opcion;

    do {
        system("cls");
        std::cout << "MENU DEL MESERO" << std::endl;
        std::cout << "1. Ver mis órdenes" << std::endl;
        std::cout << "2. Agregar nueva orden" << std::endl;
        std::cout << "3. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                verOrdenes();
                break;
            case 2:
                system("cls");
                std::cout << "Agregando nueva orden...";
                getch();
                break;
            case 3:
                std::cout << "Saliendo del menú del mesero..." << std::endl;
                break;
            default:
                std::cout << "¡Seleccione una opción valida!" << std::endl;
                getch();
                break;
        }
    } while (opcion != 3);
}

#endif //MENUMESERO_H
