#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "Fecha.cpp"
#include "Resultado.cpp"

#ifndef PARTIDO
#define PARTIDO

class Partido
{
    private:
        int id;
        Fecha fecha;
        int FK_Equipo1;
        int FK_Equipo2;
        int FK_Estadio;
        Resultado Conclusion;
        string tabla;

    public:
        Partido();
        void asignarDatos(int,Fecha,int,int,int,Resultado);
        void cadena(string *);
        void darResultado(Resultado);

        string *getdatos();

        int getId();
        int getDia();
        int getMes();
        int getAno();
        int getHora();
        int getFkEq1();
        int getFkEq2();
        int getEstadio();
        Resultado getResultado();
        Fecha getFecha();
        string getTabla();
};

Partido::Partido(){tabla="Partido";}

void Partido::asignarDatos
    (int id,Fecha fecha,int fkEq1,int fkEq2,int fkEstadio, Resultado Res)
{
    this->id=id;
    this->fecha=fecha;
    this->FK_Equipo1=fkEq1;
    this->FK_Equipo2=fkEq2;
    this->FK_Estadio=fkEstadio;
    this->Conclusion=Res;
}

void Partido::cadena(string * datos)
{
    int id=atoi(datos[0].c_str ());
    int dia=atoi(datos[1].c_str ());
    int mes=atoi(datos[2].c_str ());
    int ano=atoi (datos[3].c_str ());
    int hora=atoi(datos[4].c_str());
    int fkeq1=atoi(datos[5].c_str ());
    int fkeq2=atoi(datos[6].c_str ());
    int fkestadio=atoi(datos[7].c_str ());
    Fecha fechanueva =*new Fecha();
    fechanueva.poner (dia, mes, ano, hora, 0);
    Resultado res =*new Resultado();
    this->asignarDatos (id, fechanueva, fkeq1, fkeq2, fkestadio, res);
}

void Partido::darResultado (Resultado res){this->Conclusion=res;}

string *Partido::getdatos ()
{
    stringstream id,dia,mes,ano,eq1,eq2,est;
    id<<this->id;
    dia<<this->fecha.getdia ();
    mes<<this->fecha.getmes ();
    ano<<this->fecha.getano ();
    eq1<<this->FK_Equipo1;
    eq2<<this->FK_Equipo2;
    est<<this->FK_Estadio;
    string *datos=new string [7];
    datos[0]=id.str();
    datos[1]=dia.str();
    datos[2]=mes.str();
    datos[3]=ano.str();
    datos[4]=eq1.str();
    datos[5]=eq2.str();
    datos[6]=est.str();
    return datos;
}

int Partido::getId(){return id;}
int Partido::getDia(){return fecha.getdia ();}
int Partido::getMes(){return fecha.getmes ();}
int Partido::getAno(){return fecha.getano ();}
int Partido::getFkEq1(){return FK_Equipo1;}
int Partido::getFkEq2(){return FK_Equipo2;}
int Partido::getEstadio(){return FK_Estadio;}
int Partido::getHora (){return fecha.gethora ();}
Resultado Partido::getResultado (){return Conclusion;}
Fecha Partido::getFecha(){return fecha;}

string Partido::getTabla (){return tabla;}

#endif
