#ifndef RELACION_HPP
#define RELACION_HPP

#include "Tupla.hpp"

#include <vector>           //librería estándar de los vectores
using std::vector;

#include <string>           //librería estándar de las cadenas          
using std::string;
using std::to_string;

class Relacion{
public:
    Relacion(string nombre){
        this->nombre = nombre;
    }
    
    Relacion(const Relacion& orig){
        
    }
    ~Relacion(){
        
    }
    
private:
    string nombre;
    vector<string> headers;
    vector<Tupla> tuplas;
};
#endif /* RELACION_HPP */

