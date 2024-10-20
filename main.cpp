#include <iostream>
#include <conio.h>
#include "include/admin.h"
using namespace std;

int main() {
    int opcion;

    do {
        system("cls");
        menu();
        cin >> opcion;

        switch (opcion) {
            case 1: {
                //mesero();
                break;
            }
            case 2: {
                //cocina();
                break;
            }
            case 3: {
                admin();
                break;
            }
            case 0: {
                cout << "Saliendo..." << endl;
                getch();
                break;
            }
            default: {
                cout<<"Opcion Invalida"<<endl;
                getch();
            }
        }
    }while(opcion !=0);

    return 0;
}

