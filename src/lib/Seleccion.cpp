#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

#ifndef SELECCION
#define SELECCION

class Seleccion
{
    private:
        int id;
        int fk;
      	string nombre;
        string tabla;

    public:
        Seleccion();
        void asignarDatos(int,string,int);
        void cadena(string *);

        string getTabla();
        int getid();
        int getfk();
        string getNombre();
};

//La iniciacion nunca va a estar vacia
Seleccion::Seleccion(){tabla="Seleccion";}


void Seleccion::asignarDatos (int id,string nom,int fk)
{
    this->id=id;
    this->nombre=nom;
    this->fk=fk;
}

void Seleccion::cadena(string * cadena)
{
    int id=atoi(cadena[0].c_str());
    int fk=atoi(cadena[2].c_str());
    this->asignarDatos(id,cadena[1],fk);
}
string Seleccion::getTabla(){return tabla;}
int Seleccion::getid(){return id;}
int Seleccion::getfk(){return fk;}
string Seleccion::getNombre(){return nombre;}

#endif
