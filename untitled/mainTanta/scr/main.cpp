#include "login.h"
#include "menuMesero.h"
#include "menuAdmin.h"
void iniciarPrograma() {
    cout << "Bienvenido al sistema de gestión de pedidos." << endl;
}

int main() {

    iniciarPrograma();
    manejarLogin();
    return 0;
}
