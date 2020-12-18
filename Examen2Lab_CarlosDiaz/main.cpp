#include <cstdlib>

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <vector>           //librería estándar de los vectores
using std::vector;

#include <string>           //librería estándar de las cadenas          
using std::string;
using std::to_string;
using namespace std;

#include "Relacion.hpp"
#include "Tupla.hpp"

int main(int argc, char** argv) {
    int op=0;
    while(op!=4){
        cout << "   MENU" << endl;
        cout << "1. Crear Relación" << endl;
        cout << "2. Ver Relaciones" << endl;
        cout << "3. Insertar tupla" << endl;
        cout << "Ingresa opción: ";
        cin >> op;
        
        cout << "" << endl;
        switch(op){
            case 1: {
                
            } break;
            case 2: {
                
            } break;
            case 3: {
                
            } break;
            case 4: {
                cout << "Nos vemos labs de programación ;)" << endl;
            } break;
            default: cout << "Opción no válida. Intentá de nuevo" << endl;
        }
        cout << "" << endl;
    }
    return 0;
}

