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

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <bits/stdc++.h>    //lib de tokenizer tipo java

#include <iomanip>
using std::setw;
using std::setfill;
using std::left;

using namespace std;

#include "Relacion.hpp"
#include "Tupla.hpp"

//prototipo de funciones
int generarID(vector<Relacion*>&);
void anadirRelacion(string, Relacion*);
void cargarRelaciones(string, vector<Relacion*>&, bool);
void anadirTupla(string, Tupla*);
void cargarTuplas(string);

int main(int argc, char** argv) {
    vector<Relacion*> relaciones;
    int op=0;
    
    while(op!=4){
        cout << "   MENU" << endl;
        cout << "1. Crear Relación" << endl;
        cout << "2. Ver Relaciones" << endl;
        cout << "3. Insertar tupla" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingresa opción: ";
        cin >> op;
        
        cout << "" << endl;
        switch(op){
            case 1: {
                string nombre, encabezadoTemp;
                int numHeaders;
                vector <string> headers;
                cout << "   CREAR RELACI0N" << endl;
                cout << "Nombre: ";
                cin >> nombre;
                cout << "Cantidad de encabezados: ";
                cin  >> numHeaders;
                
                for(int i=0; i<numHeaders+1; i++){
                    if(i==0){
                        encabezadoTemp = "ID";
                        headers.push_back(encabezadoTemp);
                    } else {
                        cout << "Encabezado " << i << ": ";
                        cin  >> encabezadoTemp;
                        headers.push_back(encabezadoTemp);
                    }
                }
                
                Relacion* relacionNueva = new Relacion(nombre, headers);
                //relaciones.push_back(relacionNueva);                              //no messirve si luego hago clear en cargarRelaciones
                anadirRelacion("txtFiles/HeadersRelaciones.txt", relacionNueva);
                
                //TODO: AGARRAR ARCHIVO QUE GUARDA LOS HEADERS DE LAS RELACIONES
            } break;
            case 2: {
                cout << "   VISUALIZAR RELACI0N" << endl;
                int numRelacion=-1;
                cargarRelaciones("txtFiles/HeadersRelaciones.txt", relaciones, false);
                
                if(relaciones.size()>0){
                    cout << "Número de relación a visualizar estado de tuplas: ";
                    cin  >> numRelacion;

                    while(numRelacion<0 || numRelacion>=relaciones.size()){
                        cout << "Número de relación a visualizar estado de tuplas: ";
                        cin  >> numRelacion;
                    }
                    for(int i=0; i<relaciones[numRelacion]->getHeaders().size(); i++){
                        //int MAXWIDTH = relaciones[numRelacion]->getHeaders().at(i).length()+5;
                        int MAXWIDTH = 8;
                        //contenidoHeaders += relaciones[numRelacion]->getHeaders().at(i) + "\t";
                        cout << left << setw(MAXWIDTH) << setfill(' ') << relaciones[numRelacion]->getHeaders().at(i);
                    }
                    cout << "" << endl;

                    cargarTuplas("txtFiles/"+relaciones[numRelacion]->getNombre()+".txt");
                } else
                    cout << "No hay relaciones por ver" << endl;
            } break;
            case 3: {
                cout << "   INSERTAR TUPLA" << endl;
                int numRelacion=-1;
                string atributoNuevo="";
                cargarRelaciones("txtFiles/HeadersRelaciones.txt", relaciones, true);
                
                if(relaciones.size()>0){
                    cout << "Número de relación a añadir tupla: ";
                    cin  >> numRelacion;

                    while(numRelacion<0 || numRelacion>=relaciones.size()){
                        cout << "Número de relación a añadir tupla: ";
                        cin  >> numRelacion;
                    }

                    int ID = generarID(relaciones); 
                    //cout << ID;
                    Tupla* tuplaTemp = new Tupla(ID);

                    //cout << relaciones[numRelacion]->getHeaders().at(1);
                    for(int i=1; i<relaciones[numRelacion]->getHeaders().size(); i++){
                        cout << relaciones[numRelacion]->getHeaders().at(i) << ": ";
                        cin  >> atributoNuevo;
                        tuplaTemp->anadirAtributo(atributoNuevo);
                    }

                    relaciones[numRelacion]->anadirTupla(tuplaTemp);

                    anadirTupla("txtFiles/"+relaciones[numRelacion]->getNombre()+".txt", tuplaTemp);

                    //delete tuplaTemp;
                } else
                    cout << "No hay relaciones para añadir tuplas" << endl;
            } break;
            case 4: {
                for(int i=0; i<relaciones.size(); i++){                         //LIBERAR MEMORIA
                    for(int j=0; j<relaciones[i]->getTuplas().size(); j++){
                        delete relaciones[i]->getTuplas().at(j);
                    }
                    delete relaciones[i];
                }
                cout << "Nos vemos labs de programación ;)" << endl;
            } break;
            default: cout << "Opción no válida. Intentá de nuevo" << endl;
        }
        cout << "" << endl;
    }
    return 0;
}

int generarID(vector<Relacion*>& relaciones){
    int ID = (1000) + rand()%((9999+1) - (1000));
    
    for(int i=0; i<relaciones.size(); i++){
        for(int j=0; j<relaciones[i]->getTuplas().size(); j++){
            if( relaciones[i]->getTuplas().at(j)->getID() == ID )
                int ID = (1000) + rand()%((9999+1) - (1000));
        }
    }
    
    return ID;
}

void anadirRelacion(string file_name, Relacion* relacionAnadir){
    ofstream escritura;
    string contenidoGuardar="";
    
    contenidoGuardar += relacionAnadir->getNombre() + ";";
    
    //se recolectan los encabezados
    for(int i=0; i<relacionAnadir->getHeaders().size(); i++){
        contenidoGuardar += relacionAnadir->getHeaders().at(i) + ";";
    }
    
    contenidoGuardar += "\n";
    
    //se procede a guardar el string ya concatenado. lo prefiero con espacios ya que se ve más agradable  la vista
    escritura.open(file_name, ofstream::out | ofstream::app);
    escritura << contenidoGuardar;
    escritura.close();
}

void cargarRelaciones(string file_name, vector<Relacion*>& relaciones, bool cargarTuplas) {
    relaciones.clear();

    ifstream lectura;
    lectura.open(file_name);
    
    while (!lectura.eof()) {
        
        string linea;
        getline(lectura, linea);
        
        Relacion* relacionTemp = new Relacion();
        
        int bandera=0;
        for (auto i = strtok(&linea[0], ";"); i != NULL; i = strtok(NULL, ";")) {
            
            if(bandera==0){
                relacionTemp->setNombre(i);
                //cout << "nombre relacion " << relacionTemp->getNombre() << i;
            } else{
                //relacionTemp->getHeaders().push_back(i);
                relacionTemp->anadirHeader(i);
                
            }
            bandera++;
        }
        
        if(linea!=""){
            relaciones.push_back(relacionTemp);
        }
        //delete relacionTemp;
    }
    lectura.close();
    
    for(int i=0; i<relaciones.size(); i++){
        cout << "Relación " << i << ": " << relaciones[i]->getNombre() << "\n";
        
    }
}

void anadirTupla(string file_name, Tupla* tuplaGuardar){
    string contenidoGuardar="";
    
    contenidoGuardar += to_string( tuplaGuardar->getID() ) + ";";
    
    cout << tuplaGuardar->getID();
    
    for(int i=0; i<tuplaGuardar->getAtributos().size(); i++){
        contenidoGuardar += tuplaGuardar->getAtributos().at(i)+";";
    }
    
    contenidoGuardar += "\n";
    
    
    ifstream lectura (file_name);
    if(lectura){                                                                //si ya existe
        ofstream escritura;
        escritura.open(file_name, ofstream::out | ofstream::app);
        escritura << contenidoGuardar;
        escritura.close();
    } else{                                                                     //si no existe, crearlo
        ofstream escritura(file_name);
        
        //escritura.open(file_name, ofstream::out | ofstream::app);
        escritura << contenidoGuardar;
        escritura.close();
    }
    
}

void cargarTuplas(string file_name){
    ifstream lectura;
    lectura.open(file_name);
    
    
    while (!lectura.eof()) {
        if(!lectura){
            cout << "Esa relación aún no posee tuplas" << endl;
            break;
        }
        string linea;
        getline(lectura, linea);
        
        string contenidoTupla="";
        int bandera=0;
        for (auto i = strtok(&linea[0], ";"); i != NULL; i = strtok(NULL, ";")) {
            int MAXWIDTH = 8;
            if(bandera==0){
                //contenidoTupla += to_string(i) + "\t";
                cout << left << setw(MAXWIDTH) << setfill(' ') << i;
            } else{
                //contenidoTupla += to_string(i) + "\t";
                cout << left << setw(MAXWIDTH) << setfill(' ') << i;
            }
            bandera++;
        }
        
        if(linea!=""){
            cout << contenidoTupla;
            cout << "" << endl;
        }
        //delete relacionTemp;
    }
    lectura.close();
}