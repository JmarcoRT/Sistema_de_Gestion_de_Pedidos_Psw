#ifndef MENUADMIN_H
#define MENUADMIN_H

#include "utils.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <cstdio>

using namespace std;


inline void agregarPlato(vector<string>& categorias) {
    int i=1, continuar,opc;

	FILE *archivo = fopen("Platos.dat", "a+b");
	Plato p;
	
	do{
		
		system("CLS");
		cout<<"\n> Crear Platos";
		cout<<"\n\n Plato "<<i<<endl<<endl;
		
		fflush(stdin);
		cout<<"\tCategoria de plato:"; cin.getline(p.categoria ,30); cin.clear(); cout<<endl;
		agregarCategoria(p.categoria,categorias );
		do {
			fflush(stdin);
			cout<<"\tNombre de plato: "; cin.getline(p.nombre ,30); cin.clear(); cout<<endl;

			do{
				cin.clear();
				fflush(stdin);
				cout<<"\n\tIngrese el precio del plato "; cin>>p.precio;

				if(cin.fail() || p.precio < 0) {
					cout<<"\n\t"; cout<<"Cantidad Invalida"; cout<<"\n";

				}
			}while( cin.fail() || p.precio < 0);


			i++;
			cout << "\n\tPlato creado con exito" << endl;

			fwrite(&p,sizeof(Plato),1,archivo);

			cout<<"\n\n\tContinuar creando platos en la misma categoria  ? ( 1: Si | 0: No ): "; cin>>opc;


		}while(opc == 1);




		do{
			cin.clear();
			fflush(stdin);
			cout<<"\n\n\tContinuar creando platos ( 1: Si | 0: No ): "; cin>>continuar;
			
			if( (continuar != 1 && continuar !=0) || cin.fail() ) {		
				cout<<"\n\tOpcion invalida\n\t";
				
			}
		}while( (continuar != 1 && continuar !=0) || cin.fail() ) ;
		
	}while( continuar == 1 );
	
	fclose(archivo);
}

inline void menuAdmin() {
		vector<string> categoria;
		cargarCategorias(categoria);
        int opcion;

    do {
        system("cls");
        std::cout << "MENU ADMIN" << std::endl;
        std::cout << "1. Agregar plato" << std::endl;
        std::cout << "2. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                agregarPlato(categoria);
                break;

            case 2:
                std::cout << "Saliendo del menú del mesero..." << std::endl;
                break;
            default:
                std::cout << "¡Seleccione una opción valida!" << std::endl;
                getch();
                break;
        }
    } while (opcion != 2);
}

#endif //MENUADMIN_H
