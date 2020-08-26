#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>

#include "Fecha.cpp"

using namespace std;

#ifndef RESULTADO
#define RESULTADO

class Resultado
{
    private:
        int id;//0
        int golesequipo1;//1
        int golesequipo2;//2
        int golesuplementario1;//3
        int golesuplementario2;//4
        int golespenales1;//5
        int golespenales2;//6
        int fkPartido;//7
        string tabla;

    public:
        Resultado();
        void asignarDatos(int,int,int,int,int,int,int,int);
        void cadena(string *);

        string *getdatos();

        string getTabla();
};

Resultado::Resultado(){tabla="Resultado";}

void Resultado::asignarDatos(int id,int gol1,int gol2,int gols1,
    int gols2,int golp1,int golp2,int fk)
{
    this->id=id;
    this->golesequipo1=gol1;
    this->golesequipo2=gol2;
    this->golesuplementario1=gols1;
    this->golesuplementario2=gols2;
    this->golespenales1=golp1;
    this->golespenales2=golp2;
    this->fkPartido=fk;
}

void Resultado::cadena(string *datos)
{
    int id=atoi(datos[0].c_str ());
    int goleq1=atoi(datos[1].c_str ());
    int goleq2=atoi(datos[2].c_str ());
    int golsup1=atoi(datos[3].c_str ());
    int golsup2=atoi(datos[4].c_str ());
    int golpe1=atoi(datos[5].c_str ());
    int golpe2=atoi(datos[6].c_str ());
    int fk=atoi(datos[7].c_str ());
    this->asignarDatos
        (id,goleq1,goleq2 ,golsup1,golsup2,golpe1,golpe2,fk);
}

string *Resultado::getdatos()
{
    stringstream id,goleq1,goleq2,sup1,sup2,pe1,pe2,fk;
    id<<this->id;
    goleq1<<this->golesequipo1;
    goleq2<<this->golesequipo2;
    sup1<<this->golesuplementario1;
    sup2<<this->golesuplementario2;
    pe1<<this->golespenales1;
    pe2<<this->golespenales2;
    fk<<this->fkPartido;
    string *dato=new string [8];
    dato[0]=id.str();
    dato[1]=goleq1.str();
    dato[2]=goleq2.str();
    dato[3]=sup1.str();
    dato[4]=sup2.str();
    dato[5]=pe1.str();
    dato[6]=pe2.str();
    dato[7]=fk.str();
    return dato;
}

string Resultado::getTabla(){return tabla;}

#endif
