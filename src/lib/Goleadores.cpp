#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>

using namespace std;

#ifndef GOLEADORES
#define GOLEADORES

class Goleadores
{
    private:
        int id;
        int fk_eq;
        int fk_jug;
        int fk_part;
        int tiempo; //2=Penales,0=Partido,1=Suplementario
        string tabla;

    public:
        Goleadores();
        void dardatos(int,int,int,int,int);

        string *getdatos();

        int getid();
        int getFKEq();
        int getFkJugador();
        int getFKPartido();
        int gettiempo();
        string getTabla();
};

Goleadores::Goleadores(){tabla="Goleadores";}

void Goleadores::dardatos (int id,int fkjug,int fkpar,int eq,int tiempo)
{
    this->id=id;
    this->fk_jug=fkjug;
    this->fk_part=fkpar;
    this->tiempo=tiempo;
    this->fk_eq=eq;
}

string *Goleadores::getdatos()
{
    stringstream id,fkjug,fkpart,tiempo,fkeq;
    id<<this->id;
    fkjug<<this->fk_jug;
    fkpart<<this->fk_part;
    tiempo<<this->tiempo;
    fkeq<<this->fk_eq;
    string *datos=new string [5];
    datos[0]=id.str();
    datos[1]=fkjug.str();
    datos[2]=fkpart.str();
    datos[3]=tiempo.str();
    datos[4]=fkeq.str();
    return datos;
}

int Goleadores::getid(){return this->id;}
int Goleadores::getFkJugador(){return this->fk_jug;}
int Goleadores::getFKPartido(){return this->fk_part;}
int Goleadores::gettiempo (){return this->tiempo;}
int Goleadores::getFKEq (){return this->fk_eq;}
string Goleadores::getTabla (){return this->tabla;}

#endif
