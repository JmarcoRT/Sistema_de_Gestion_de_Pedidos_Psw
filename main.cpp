#include <iostream>
#include "cocinero.h"
#include "mesero.h"
using namespace std;
int opcion;

int main(){

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

    return 0;
}