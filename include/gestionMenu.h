//Submodulo para Gestionar el Menu
#ifndef GESTIONMENU_H
#define GESTIONMENU_H

#include <iostream>
#include <conio.h>
using namespace std;

void menuGestionarMenu() {

    int ops;

    do {
        system("cls");
        cout << "GESTION DEL MENU" << endl;
        cout << "1. Agregar Plato" << endl;
        cout << "2. Modificar Plato" << endl;
        cout << "3. Archivar Plato" << endl;
        cout << "0. ATRAS" << endl;

        cout << "Seleccione una opcion-->";
        cin >> ops;

        switch (ops) {
            case 1: {
                system("cls");
                cout <<"Agregando platos.." << endl;
                getch();
                break;
            }
            case 2: {
                system("cls");
                cout <<"Modificando platos..." << endl;
                getch();
                break;
            }
            case 3: {
                system("cls");
                cout <<"Archivando platos..." << endl;
                getch();
                break;
            }
            case 0: {
                break;      //saliendo...
            }
            default: {
                cout<<"Opcion invalida!"<<endl;
                getch();
            }
        }
    }while(ops!=0);

}


#endif //GESTIONMENU_H
