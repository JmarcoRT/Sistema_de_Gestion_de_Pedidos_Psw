#ifndef UTILIDADES_H
#define UTILIDADES_H

#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define ENTER 13
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>

using namespace std;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void cuadro(int x1, int y1, int x2, int y2) {
    for (int i = x1; i < x2; i++) {
        gotoxy(i, y1); printf("%c", 196);
        gotoxy(i, y2); printf("%c", 196);
    }

    for (int i = y1; i < y2; i++) {
        gotoxy(x1, i); printf("%c", 179);
        gotoxy(x2, i); printf("%c", 179);
    }

    gotoxy(x1, y1); printf("%c", 218);
    gotoxy(x1, y2); printf("%c", 192);
    gotoxy(x2, y1); printf("%c", 191);
    gotoxy(x2, y2); printf("%c", 217);
}

void imprimirMenu(const char *titulo, const char *opciones[], int m, int opcionSeleccionada) {
    cuadro(0, 0, 119, 29);
    cuadro(8, 1, 110, 3);
    gotoxy(5, 3 + opcionSeleccionada); cout << "==>";
    // Imprime el título
    gotoxy(50, 2); cout << titulo;
    for (int i = 0; i < m; i++) {
        gotoxy(10, 4 + i); cout << i + 1 << ") " << opciones[i];
    }
}

int menus(const char *titulo, const char *opciones[], int m) {
    int opcionSeleccionada = 1;
    int tecla;
    bool repite = true;
    system("cls");
    imprimirMenu(titulo, opciones, m, opcionSeleccionada);
    do {
        gotoxy(5, 3 + opcionSeleccionada); cout << "==>";
        do {
            tecla = getch();
        } while (tecla != TECLA_ARRIBA && tecla != TECLA_ABAJO && tecla != ENTER);
        gotoxy(5, 3 + opcionSeleccionada); cout << "   ";  // Borra el indicador anterior
        switch (tecla) {
            case TECLA_ARRIBA:
                opcionSeleccionada--;
                if (opcionSeleccionada == 0) {
                    opcionSeleccionada = m;
                }
                break;
            case TECLA_ABAJO:
                opcionSeleccionada++;
                if (opcionSeleccionada > m) {
                    opcionSeleccionada = 1;
                }
                break;
            case ENTER:
                repite = false;
                break;
        }
    } while (repite);
    return opcionSeleccionada;
}

#endif //UTILIDADES_H