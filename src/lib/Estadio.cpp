#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

#ifndef ESTADIO
#define ESTADIO

class Estadio
{
    private:
        int id;
        string nombre;
        int capacidad;
        string ciudad;
        string tabla;

    public:
        Estadio();
        void asignarDatos(int,string,int,string);
        void cadena(string *);

        string *getdatos();

        int getId();
        string getNombre();
        int getcapacidad();
        string getciudad();
        string getTabla();
};

Estadio::Estadio(){tabla="Estadio";}

void Estadio::asignarDatos(int id,string nombre,int capacidad,string ciudad)
{
    this->id=id;
    this->nombre=nombre;
    this->capacidad=capacidad;
    this->ciudad=ciudad;
}

void Estadio::cadena(string *datos)
{
    int id=atoi(datos[0].c_str());
    int capacidad=atoi(datos[2].c_str());
    this->asignarDatos (id, datos[1], capacidad, datos[3]);
}

string *Estadio::getdatos ()
{
    stringstream id,capacidad;
    id<<this->id;
    capacidad<<this->capacidad;
    string *datos=new string[4];
    datos[0]=id.str();
    datos[1]=this->nombre;
    datos[2]=capacidad.str();
    datos[3]=this->ciudad;
    return datos;
}

int Estadio::getId(){return id;}
string Estadio::getNombre(){return nombre;}
int Estadio::getcapacidad(){return capacidad;}
string Estadio::getciudad(){return ciudad;}

string Estadio::getTabla(){return tabla;}

#endif
