#ifndef TUPLA_HPP
#define TUPLA_HPP

#include <vector>           //librería estándar de los vectores
using std::vector;

#include <string>           //librería estándar de las cadenas          
using std::string;
using std::to_string;

class Tupla{
public:
    Tupla(int ID){
        this->ID = ID;
    }
    
    Tupla(const Tupla& orig){
        
    }
    ~Tupla(){
        
    }
    
private:
    int ID;
    vector<string> atributos;
};

#endif /* TUPLA_HPP */

