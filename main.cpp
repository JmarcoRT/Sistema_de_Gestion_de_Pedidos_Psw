#include <iostream>
#include "cocinero.h"
#include "mesero.h"
using namespace std;
int opcion;

void menu(){
    cout<<"Ingresa una opcion: "<<endl;
    cout<<"\n1. MESERO"<<endl;
    cout<<"2. COCINERO"<<endl;
    cout<<"3. ADMINISTRADOR"<<endl;
    cin>> opcion;

    switch(opcion){
        case 1: iniciarMesero(); break; //MESERO
        case 2: iniciarCocina(); break;
        case 3: break; //ADMINISTRADOR
        default: cout<<"Fuera de rango";
    } 
}

int main() {
    do {
        system("CLS");
        menu();
    } while (opcion != 3);  // Continua en el menú hasta que se elija la opción 3 (Salir)
    return 0;
}