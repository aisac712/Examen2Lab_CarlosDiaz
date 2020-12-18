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
    Relacion(){
    }
    Relacion(string nombre, vector<string> headers){
        this->nombre = nombre;
        this->headers = headers;
    }
    
//    Relacion(const Relacion& orig){
//        
//    }
//    ~Relacion(){
//        
//    }
    void setNombre(string nombre){
        this->nombre = nombre;
    }
    
    string getNombre(){
        return this->nombre;
    }
    
    vector<string> getHeaders(){
        return this->headers;
    }
    
    void anadirHeader(string encabezado){
        this->headers.push_back(encabezado);
    }
    
    void anadirTupla(Tupla* tuplaNueva){
        this->tuplas.push_back(tuplaNueva);
    }
    
    vector<Tupla*> getTuplas(){
        return this->tuplas;
    }
    
private:
    string nombre;
    vector<string> headers;
    vector<Tupla*> tuplas;
};
#endif /* RELACION_HPP */

