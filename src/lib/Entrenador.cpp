#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "Lista.cpp"
#include "Seleccion.cpp"

using namespace std;

#ifndef ENTRENADOR
#define ENTRENADOR

class Entrenador
{
    private:
        int ced;
        string nombre;
        string apellido;
        string nacionalidad;
        string tabla;
        Lista<Seleccion> *trayectoria;

    public:
        Entrenador();
        void asignarDatos(int,string,string,string);
        void cadena(string *);
        void agregarSeleccion(Seleccion);

        string *getdatos();
        int getCed();
        int getFk();
        string getNombre();
        string getapellido();
        string getNacionalidad();
        string getTabla();

};

Entrenador::Entrenador()
{
	trayectoria=new Lista<Seleccion>();
	tabla="Entrenador";
}

void Entrenador::asignarDatos(int id,string nom,string ape,string naci)
{
    this->ced=id;
    this->nombre=nom;
    this->apellido=ape;
    this->nacionalidad=naci;
}

void Entrenador::cadena(string * cadena)
{
    int ced=atoi(cadena[0].c_str());
    this->asignarDatos(ced,cadena[1],cadena[2],cadena[3]);
}

string *Entrenador::getdatos ()
{
    stringstream ced;
    ced<<this->ced;
    string *datos=new string[4];
    datos[0]=ced.str();
    datos[1]=this->nombre;
    datos[2]=this->apellido;
    datos[3]=this->nacionalidad;
    return datos;
}

void Entrenador::agregarSeleccion(Seleccion temp){trayectoria->insertarFin(temp);}

int Entrenador::getCed(){return ced;}
string Entrenador::getNombre(){return nombre;}
string Entrenador::getapellido(){return apellido;}
string Entrenador::getNacionalidad(){return nacionalidad;}
string Entrenador::getTabla(){return tabla;}

#endif
