#ifndef MENUMESERO_H
#define MENUMESERO_H

#include "utils.h"
#include "misOrdenes.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <cstring>
#include "utilidades.h"


using namespace std;

inline void cancelarOrden() {
    cout << "> ELIMINAR ORDEN" << endl << endl;
    bool ordenEncontrada = false;

    // Apertura de archivos y definición de variables
    FILE *archivo = fopen("Ordenes.dat", "r+b");
    FILE *temp = fopen("temp.dat", "w+b");
    int numeroMesaBorrar;
    Orden o;
    size_t numPlatos;

    if (archivo == nullptr || temp == nullptr) {
        cout << "Error al abrir los archivos." << endl;
        return;
    }

    // Solicitud del número de mesa
    do {
        cin.clear();
        fflush(stdin);
        cout << "Numero de mesa que cancelo la orden: ";
        cin >> numeroMesaBorrar;

        if (numeroMesaBorrar < 0 || cin.fail()) {
            cout << "\nMesa no existente\n\n";
        }

    } while (numeroMesaBorrar < 0 || cin.fail());

    // Copia de órdenes del archivo original al temporal, excepto la orden a cancelar
    while (fread(&o.numeroMesa, sizeof(int), 1, archivo) &&
           fread(&o.hora, sizeof(Fecha), 1, archivo) &&
           fread(o.estado, sizeof(o.estado), 1, archivo) &&
           fread(&numPlatos, sizeof(size_t), 1, archivo)) {

        // Leer los platos asociados a la orden
        o.platos.clear();
        for (size_t i = 0; i < numPlatos; ++i) {
            Plato p;
            fread(&p, sizeof(Plato), 1, archivo);
            o.platos.push_back(p);
        }

        // Si la orden no corresponde a la mesa a eliminar, se copia al archivo temporal
        if (o.numeroMesa != numeroMesaBorrar) {
            fwrite(&o.numeroMesa, sizeof(o.numeroMesa), 1, temp);
            fwrite(&o.hora, sizeof(o.hora), 1, temp);
            fwrite(o.estado, sizeof(o.estado), 1, temp);

            // Guardar el número de platos y los platos asociados
            numPlatos = o.platos.size();
            fwrite(&numPlatos, sizeof(numPlatos), 1, temp);
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

            // Escribir en el archivo original
            fwrite(&o.numeroMesa, sizeof(o.numeroMesa), 1, archivo);
            fwrite(&o.hora, sizeof(o.hora), 1, archivo);
            fwrite(o.estado, sizeof(o.estado), 1, archivo);
            fwrite(&numPlatos, sizeof(numPlatos), 1, archivo);

            // Leer y escribir cada plato en el archivo original
            for (size_t i = 0; i < numPlatos; ++i) {
                Plato p;
                fread(&p, sizeof(Plato), 1, temp);
                fwrite(&p, sizeof(Plato), 1, archivo);
            }
        }

        fclose(archivo);
        fclose(temp);
        remove("temp.dat"); // Eliminar el archivo temporal

        cout << "\nOrden de la mesa " << numeroMesaBorrar << " cancelada con exito.\n";
    } else {
        cout << "\nNo se encontro ninguna orden para la mesa " << numeroMesaBorrar << ".\n";
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
        cout << "Desea agregar otro plato a la orden? (1: Si | 0: No): ";
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
    cout << "> ACTUALIZAR ORDEN" << endl << endl;

    bool ordenEncontrada = false;
    FILE *archivo = fopen("Ordenes.dat", "r+b");
    if (archivo == nullptr) {
        cout << "Error al abrir el archivo de órdenes." << endl;
        return;
    }

    int numeroMesa;
    Orden o;
    size_t numPlatos;

    // Solicitar número de mesa
    do {
        cin.clear();
        fflush(stdin);
        cout << "Numero de mesa a actualizar: ";
        cin >> numeroMesa;

        if (numeroMesa < 0 || cin.fail()) {
            cout << "\nMesa no existente\n\n";
        }
    } while (numeroMesa < 0 || cin.fail());

    // Leer todas las órdenes y buscar la que coincida
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

        if (o.numeroMesa == numeroMesa) {
            ordenEncontrada = true;
            break; // Encontró la orden, salir del bucle
        }
    }

    fclose(archivo);

    if (!ordenEncontrada) {
        cout << "\nNo se encontró ninguna orden para la mesa " << numeroMesa << ".\n";
        system("pause");
        return;
    }

    // Agregar o actualizar platos en la orden
    cout << "\n> Agregar nuevos platos o actualizar existentes:\n";
    bool flag = false;
    int opc;
    string categoriasbuscar;

    Orden nuevosPlatos = o; // Crear un objeto temporal para los nuevos platos

    do {
        mostrarCategorias(categorias);

        fflush(stdin);
        cout << "Ingrese la categoría: ";
        getline(cin, categoriasbuscar);
        fflush(stdin);

        mostrarPlatosPorCategoria(categoriasbuscar, nuevosPlatos, flag);

        cout << "Desea agregar otro plato a la orden? (1: Sí | 0: No): ";
        cin >> opc;
    } while (opc == 1);

    // Combinar platos: actualizar cantidades si el plato ya existe
    for (const auto &nuevoPlato : nuevosPlatos.platos) {
        bool encontrado = false;
        for (auto &platoExistente : o.platos) {
            if (strcmp(platoExistente.nombre, nuevoPlato.nombre) == 0) {
                platoExistente.cantidad += nuevoPlato.cantidad; // Actualizar cantidad
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            o.platos.push_back(nuevoPlato); // Agregar el nuevo plato si no existía
        }
    }

    // Guardar la orden actualizada en el archivo
    archivo = fopen("Ordenes.dat", "r+b");
    if (archivo == nullptr) {
        cout << "Error al abrir el archivo para guardar la actualización." << endl;
        return;
    }

    FILE *temp = fopen("temp.dat", "w+b");

    fseek(archivo, 0, SEEK_SET);

    while (fread(&o.numeroMesa, sizeof(int), 1, archivo) &&
           fread(&o.hora, sizeof(Fecha), 1, archivo) &&
           fread(o.estado, sizeof(o.estado), 1, archivo) &&
           fread(&numPlatos, sizeof(size_t), 1, archivo)) {

        Orden tempOrden;
        tempOrden.numeroMesa = o.numeroMesa;
        tempOrden.hora = o.hora;
        strcpy(tempOrden.estado, o.estado);

        tempOrden.platos.clear();
        for (size_t i = 0; i < numPlatos; ++i) {
            Plato p;
            fread(&p, sizeof(Plato), 1, archivo);
            tempOrden.platos.push_back(p);
        }

        if (tempOrden.numeroMesa == numeroMesa) {
            tempOrden = o; // Reemplazar la orden con la actualizada
        }

        // Guardar la orden actualizada en el archivo temporal
        fwrite(&tempOrden.numeroMesa, sizeof(tempOrden.numeroMesa), 1, temp);
        fwrite(&tempOrden.hora, sizeof(tempOrden.hora), 1, temp);
        fwrite(tempOrden.estado, sizeof(tempOrden.estado), 1, temp);

        size_t platosSize = tempOrden.platos.size();
        fwrite(&platosSize, sizeof(platosSize), 1, temp);

        for (const auto &plato : tempOrden.platos) {
            fwrite(&plato, sizeof(Plato), 1, temp);
        }
    }

    fclose(archivo);
    fclose(temp);

    // Reemplazar archivo original por el temporal
    remove("Ordenes.dat");
    rename("temp.dat", "Ordenes.dat");

    cout << "\nOrden de la mesa " << numeroMesa << " actualizada con éxito.\n";
    system("pause");
}
inline void menuOrdenes() {
    int opt;
    bool repite = true;
    const char *titulo="MIS ORDENES";
    const char *opciones[]={"Ver detalles","Actualizar Orden","Finalizar orden","Cancelar Orden","SALIR"};
    int m=5;
    do {
        system("cls");
        cuadro(0,0,119,29);
        cuadro(8,1,110,3);
        opt = menus(titulo, opciones, m);
        /*
        cout << "MIS ORDENES" << endl;
        cout << "1. Ver detalles." << endl;
        cout << "2. Actualizar orden." << endl;
        cout << "3. Finalizar orden." << endl;
        cout << "4. Cancelar orden." << endl;
        cout << "5. Salir." << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;*/

        switch (opt) {
            case 1:
                system("cls");
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
                repite=false;
            break;
        }
    } while (repite);
}
inline void menuMesero() {
    string usuario;

    do {
        system("cls");
        cuadro(0,0,119,29);

        gotoxy(2,4); cout << "Introduzca el usuario (0 para salir): ";
        gotoxy(2,5); cin >> usuario;

        if (usuario == "0") {
            return; // Salir si se ingresa "0"
        } else if (usuario != "mesero") {
            gotoxy(2,6); cout << "El usuario es invalido" << endl;
            getch();
        }
    } while (usuario != "mesero");


    int opt;
    bool repite = true;
    const char *titulo="MENU DEL MESERO";
    const char *opciones[]={"Ver mis ordenes","Agregar nueva orden","SALIR"};
    int m=3;
    do {
        system("cls");
        cuadro(0,0,119,29);
        cuadro(8,1,110,3);
        opt = menus(titulo, opciones, m);
        /*std::cout << "MENU DEL MESERO" << std::endl;
        std::cout << "1. Ver mis ordenes" << std::endl;
        std::cout << "2. Agregar nueva orden" << std::endl;
        std::cout << "3. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;*/

        switch (opt) {
            case 1:
                menuOrdenes();
            break;
            case 2:
                system("cls");
                agregarOrden();
                getch();
            break;
            case 3:
                repite=false;
            break;

        }
    } while (repite);
}

#endif //MENUMESERO_H
