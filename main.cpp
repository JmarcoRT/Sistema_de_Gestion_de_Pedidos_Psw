#include <iostream>
#include <conio.h>
#include "include/admin.h"
#include "include/utilidades.h"
#include "include/utils.h"
#include "include/menuMesero.h"
#include "include/cocinero.h"
#include "include/misOrdenes.h"
using namespace std;

int main() {

    int opt;
    bool repite=true;
    string usuario;
    const char *titulo="SISTEMA DE GESTION DE PEDIDOS TANTA";
    const char *opciones[]={"Mesero","Cocina","Administrador","SALIR"};
    int m=4;
    system("COLOR F0");  // Fondo blanco y texto negro
    cuadro(0,0,119,29);
    cuadro(8,1,110,3);
    do {
        opt=menus(titulo,opciones,m);
        switch(opt) {
            case 1:
                menuMesero();
                break;
            case 2:
                iniciarCocina();
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