
#ifndef LOGIN_H
#define LOGIN_H
#include <string>
#include <fstream>     // Para std::ifstream
#include <sstream>     // Para std::stringstream
using namespace std;


struct Usuario {
    string usuario;
    string contrasena;
    string rol;
};


bool validarLogin(const string& usuario, const string& contrasena, string& rol);
string leerContrasena();
void mostrarLogo();
void manejarLogin();
void menuAdmin();
#endif //LOGIN_H
