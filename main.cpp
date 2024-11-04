#include <iostream>
#include <conio.h>
#include "include/admin.h"
#include "include/utilidades.h"
using namespace std;

int main() {

    int opt;
    bool repite=true;
    string usuario;
    const char *titulo="Sistema de Gestion de pedidos";
    const char *opciones[]={"Mesero","cocina","administrador","SALIR"};
    int m=4;
    system("COLOR D6");
    cuadro(0,0,119,29);
    cuadro(8,1,110,3);
    do {
        opt=menus(titulo,opciones,m);
        switch(opt) {
            case 1://mesero();
                break;
            case 2://cocina();
                break;
            case 3:
                admin();
            break;
            case 4:
                repite=false;
            break;
        }
    }while(repite);


    return 0;
}