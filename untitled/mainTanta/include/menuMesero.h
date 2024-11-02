#ifndef MENUMESERO_H
#define MENUMESERO_H

#include "utils.h"
#include "misOrdenes.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <cstring>


using namespace std;


inline void cancelarOrden() {
    cout<<"> ELIMINAR ORDEN"<<endl<<endl;
    bool ordenEncontrada=false;
    //Apertura de archivos y definicion de variables
    FILE *archivo = fopen("Ordenes.dat", "r+b");
    FILE *temp = fopen("temp.dat", "w+b");
    int  numeroMesaBorrar;
    Orden o;
    size_t numPlatos;
    //Solicitud del numero de mesa
    do{
        cin.clear();
        fflush(stdin);
        cout<<"Numero de mesa que canceló la orden :  ";cin>>numeroMesaBorrar;

        if(numeroMesaBorrar<0 || cin.fail() ){
            cout<<"\n\n"; cout<<"mesa no existente"<<"\n\n";
        }

    }while(numeroMesaBorrar<0  || cin.fail() );

    // Copia de órdenes del archivo original al temporal, excepto la orden a cancelar
    while (fread(&o.numeroMesa, sizeof(int), 1, archivo) &&
           fread(&o.hora, sizeof(Fecha), 1, archivo) &&
           fread(o.estado, sizeof(o.estado), 1, archivo) &&
           fread(&numPlatos, sizeof(size_t), 1, archivo)) {
           o.platos.clear();
           for (size_t i = 0; i < numPlatos; ++i) {
            Plato p;
            fread(&p, sizeof(Plato), 1, archivo);
            o.platos.push_back(p);
        }
        if (o.numeroMesa != numeroMesaBorrar) {
            fwrite(&o.numeroMesa, sizeof(o.numeroMesa), 1, temp);
            fwrite(&o.hora, sizeof(o.hora), 1, temp);
            fwrite(&o.estado, sizeof(o.estado), 1, temp);
            //fwrite(&o, sizeof(Orden), 1, temp);
            numPlatos = o.platos.size();
            fwrite(&numPlatos, sizeof(numPlatos), 1, temp);

            // Guardar cada plato individualmente
            for (const auto& plato : o.platos) {
                fwrite(&plato, sizeof(Plato), 1, temp);
            }
        } else {
            ordenEncontrada = true; // Indicar que la orden a cancelar fue encontrada
        }
    }

    fclose(archivo);
    fclose(temp);

    if (ordenEncontrada) {
        // Sobreescribir el archivo original con el contenido del archivo temporal
        archivo = fopen("Ordenes.dat", "wb");
        temp = fopen("temp.dat", "rb");

        while (fread(&o.numeroMesa, sizeof(int), 1, temp) &&
           fread(&o.hora, sizeof(Fecha), 1, temp) &&
           fread(o.estado, sizeof(o.estado), 1, temp) &&
           fread(&numPlatos, sizeof(size_t), 1, temp)) {


            fwrite(&o.numeroMesa, sizeof(o.numeroMesa), 1, archivo);
            fwrite(&o.hora, sizeof(o.hora), 1, archivo);
            fwrite(&o.estado, sizeof(o.estado), 1, archivo);
            fwrite(&numPlatos, sizeof(numPlatos), 1, archivo);

            // Guardar cada plato individualmente
            for (const auto& plato : o.platos) {
                Plato p;
                fread(&p, sizeof(Plato), 1, temp);
                fwrite(&p, sizeof(Plato), 1, archivo);
            }
        }

        fclose(archivo);
        fclose(temp);
        remove("temp.dat"); // Eliminar el archivo temporal

        cout << "\nOrden de la mesa " << numeroMesaBorrar << " cancelada con éxito.\n";
    } else {
        cout << "\nNo se encontró ninguna orden para la mesa " << numeroMesaBorrar << ".\n";
    }


    system("CLS");

    system("pause");
}


inline void verOrdenes() {

    FILE *archivo = fopen("Ordenes.dat", "rb");
    Orden o;
    size_t numPlatos;

    // impresion de los datos de cada orden activa
    while (fread(&o.numeroMesa, sizeof(int), 1, archivo) &&
           fread(&o.hora, sizeof(Fecha), 1, archivo) &&
           fread(o.estado, sizeof(o.estado), 1, archivo) &&
           fread(&numPlatos, sizeof(size_t), 1, archivo)) {


        o.platos.clear();

        // Leer cada plato individualmente
        for (size_t i = 0; i < numPlatos; ++i) {
            Plato p;
            fread(&p, sizeof(Plato), 1, archivo);
            o.platos.push_back(p);
        }

        // Mostrar los datos de la orden
        cout << "Numero de mesa: " << o.numeroMesa << endl;
        cout << "Fecha: " << formato_hora(o.hora) << endl;
        cout << "Estado: " << o.estado << endl;

        cout << "Platos en la orden:" << endl;
        for (const auto& plato : o.platos) {
            cout << "- " << plato.nombre << " ($" << plato.precio << "), Cantidad: " << plato.cantidad
                 << ", Comentario: " << plato.comentario << endl;
        }
        cout << "\n";
           }


    fclose(archivo);

    cout<<"\n\n\n";
    system("pause");
}

inline void agregarOrden() {
    vector<string> categorias;
    cargarCategorias(categorias);
    int opc;
    bool flag =false;
    FILE *archivo = fopen("Ordenes.dat", "a+b");
    Orden o;
    system("cls");

    //funcion para ver las mesas
    mostrarMesas(5,3);cout<<endl;

    fflush(stdin);

    cout<<"ingrese el numero de mesa : ";cin>>o.numeroMesa;
    fflush(stdin);
    o.hora = definir_fecha(0,0,0,0);
    fflush(stdin);
    strcpy(o.estado, "pendiente");
    //funcion para ver las categorias
    mostrarCategorias(categorias);

    cout<<endl;
    string categoriasbuscar;
    do {
        fflush(stdin);
        cout<<"Ingrese la categoria :";getline(cin,categoriasbuscar);
        fflush(stdin);
        mostrarPlatosPorCategoria(categoriasbuscar, o,flag);
        if(flag) {
            fclose(archivo);
            return;
        }
        cout << "¿Desea agregar otro plato a la orden? (1: Sí | 0: No): ";
        cin >> opc;
    }while(opc == 1);
    //guardar cada cosa independiente
    fwrite(&o.numeroMesa, sizeof(o.numeroMesa), 1, archivo);
    fwrite(&o.hora, sizeof(o.hora), 1, archivo);
    fwrite(&o.estado, sizeof(o.estado), 1, archivo);


    // Guardar la cantidad de platos en el vector
    size_t numPlatos = o.platos.size();
    fwrite(&numPlatos, sizeof(numPlatos), 1, archivo);

    // Guardar cada plato individualmente
    for (const auto& plato : o.platos) {
        fwrite(&plato, sizeof(Plato), 1, archivo);
    }

    cout<<"\n\tOrden creada con exito"<<endl;


    fclose(archivo);

}
inline void actualizarOrden() {
    system("cls");
    vector<string> categorias;
    cargarCategorias(categorias);
    cout<<"> ACTUALIZAR ORDEN"<<endl<<endl;
    bool ordenEncontrada=false;
    //Apertura de archivos y definicion de variables
    FILE *archivo = fopen("Ordenes.dat", "r+b");
    FILE *temp = fopen("temp.dat", "w+b");
    int  numeroMesa;
    Orden o;
    size_t numPlatos;
    //Solicitud del numero de mesa
    do{
        cin.clear();
        fflush(stdin);
        cout<<"Numero de mesa que cancelo la orden :  ";cin>>numeroMesa;

        if(numeroMesa<0 || cin.fail() ){
            cout<<"\n\n"; cout<<"mesa no existente"<<"\n\n";
        }

    }while(numeroMesa<0  || cin.fail() );

    // Copia de ordenes del archivo original al temporal, excepto la orden a cancelar
    while (fread(&o.numeroMesa, sizeof(int), 1, archivo) &&
           fread(&o.hora, sizeof(Fecha), 1, archivo) &&
           fread(o.estado, sizeof(o.estado), 1, archivo) &&
           fread(&numPlatos, sizeof(size_t), 1, archivo)) {
           o.platos.clear();
           for (size_t i = 0; i < numPlatos; ++i) {
            Plato p;
            fread(&p, sizeof(Plato), 1, archivo);
            o.platos.push_back(p);
        }
        if (o.numeroMesa != numeroMesa) {
            fwrite(&o.numeroMesa, sizeof(o.numeroMesa), 1, temp);
            fwrite(&o.hora, sizeof(o.hora), 1, temp);
            fwrite(&o.estado, sizeof(o.estado), 1, temp);

            numPlatos = o.platos.size();
            fwrite(&numPlatos, sizeof(numPlatos), 1, temp);

            // Guardar cada plato individualmente
            for (const auto& plato : o.platos) {
                fwrite(&plato, sizeof(Plato), 1, temp);
            }
        } else {
            ordenEncontrada = true; // Indicar que la orden a cancelar fue encontrada
        }
    }

    fclose(archivo);
    fclose(temp);

    if (ordenEncontrada) {
        // Eliminar el archivo original
        remove("Ordenes.dat");
        rename("temp.dat", "Ordenes.dat");
        //----------------------------------------------------------FUNCION AGREGAR ORDEN---------------------------------------
        vector<string> categorias;
        cargarCategorias(categorias);
        int opc;
        bool flag =false;
        FILE *archivo = fopen("Ordenes.dat", "a+b");
        Orden o;
        system("cls");

        fflush(stdin);
        //ya no pide numero de mesa
        o.numeroMesa= numeroMesa;
        fflush(stdin);
        o.hora = definir_fecha(0,0,0,0);
        fflush(stdin);
        strcpy(o.estado, "pendiente");
        //funcion para ver las categorias
        mostrarCategorias(categorias);

        cout<<endl;
        string categoriasbuscar;
        do {
            fflush(stdin);
            cout<<"Ingrese la categoria :";getline(cin,categoriasbuscar);
            fflush(stdin);
            mostrarPlatosPorCategoria(categoriasbuscar, o,flag);
            if(flag) {
                fclose(archivo);
                return;
            }
            cout << "¿Desea agregar otro plato a la orden? (1: Sí | 0: No): ";
            cin >> opc;
        }while(opc == 1);
        //guardar cada cosa independiente
        fwrite(&o.numeroMesa, sizeof(o.numeroMesa), 1, archivo);
        fwrite(&o.hora, sizeof(o.hora), 1, archivo);
        fwrite(&o.estado, sizeof(o.estado), 1, archivo);


        // Guardar la cantidad de platos en el vector
        size_t numPlatos = o.platos.size();
        fwrite(&numPlatos, sizeof(numPlatos), 1, archivo);

        // Guardar cada plato individualmente
        for (const auto& plato : o.platos) {
            fwrite(&plato, sizeof(Plato), 1, archivo);
        }

        fclose(archivo);
        //----------------------------------------------------fin de funcion agregar orden-----------------------------------------
        cout << "\nOrden de la mesa " << numeroMesa << " actualizada con exito.\n";
    } else {
        cout << "\nNo se encontro ninguna orden para la mesa " << numeroMesa << ".\n";
    }

    system("pause");
    getch();
}
inline void menuOrdenes() {
    int opcion;

    do {
        system("cls");
        cout << "MIS ORDENES" << endl;
        cout << "1. Ver detalles." << endl;
        cout << "2. Actualizar orden." << endl;
        cout << "3. Finalizar orden." << endl;
        cout << "4. Cancelar orden." << endl;
        cout << "5. Salir." << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                verOrdenes();
            break;
            case 2:
                actualizarOrden();
            break;
            case 3:
                finalizarOrden();
            break;
            case 4:
                cancelarOrden();
            break;
            case 5:
                cout << "Saliendo del menú..." << endl;
            break;
            default:
                cout << "¡Seleccione una opción valida!" << endl;
            getch();
            break;
        }
    } while (opcion != 5);
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
                menuOrdenes();
            break;
            case 2:
                system("cls");
                agregarOrden();
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
