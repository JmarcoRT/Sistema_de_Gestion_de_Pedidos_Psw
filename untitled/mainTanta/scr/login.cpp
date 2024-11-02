#include "login.h"
#include "menuMesero.h"
#include "menuAdmin.h"
string logoPrincipal =
    R"(  _____           _
 |_   _|_ _ _ __ | |_ __ _
   | |/ _` | '_ \| __/ _` |
   | | (_| | | | | || (_| |
   |_|\__,_|_| |_|\__\__,_|
                            )";

bool validarLogin(const string& usuarioIngresado, const string& contrasenaIngresada, string& rol) {
    ifstream archivo(pathUsuarios);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo de usuarios." << endl;
        return false;
    }

    string linea;
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Usuario u;
        getline(ss, u.usuario, ',');
        getline(ss, u.contrasena, ',');
        getline(ss, u.rol, ',');

        if (u.usuario == usuarioIngresado && u.contrasena == contrasenaIngresada) {
            rol = u.rol;
            return true;
        }
    }

    return false;
}

string leerContrasena() {
    string contrasena;
    while (true) {
        char caracter = getch();
        if (caracter == 13) {
            cout << endl;
            break;
        } else if (caracter == 8) {
            if (!contrasena.empty()) {
                contrasena.pop_back();
                cout << "\b \b";
            }
        } else {
            contrasena += caracter;
            cout << "*";
        }
    }
    return contrasena;
}


void manejarLogin() {
    string usuarioIngresado;
    bool loginExitoso = false;
    string rol;

    while (!loginExitoso) {
        system("cls");
        cout << logoPrincipal << endl;

        cout << "Ingrese su usuario: ";
        cin >> usuarioIngresado;
        cout << "Ingrese su contraseña: ";
        string contrasenaIngresada = leerContrasena();

        loginExitoso = validarLogin(usuarioIngresado, contrasenaIngresada, rol);

        if (!loginExitoso) {
            cout << "Las credenciales son incorrectas, vuelva a intentarlo." << endl;
            cin.ignore();
            cin.get();
            system("cls");
        }
    }

    if (rol == "Administrador") {
        menuAdmin();
    } else if (rol == "Mesero") {
        menuMesero();
    } else if (rol == "Cocina") {
        menuCocina();
    } else {
        cout << "El rol no está definido." << endl;
    }
}