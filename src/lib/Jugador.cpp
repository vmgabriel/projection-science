#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>

#include "Fecha.cpp"

#ifndef JUGADOR
#define JUGADOR

class Jugador
{
    private:
        int ced;
        string nombre;
        string apellido;
        string nacionalidad;
        int numero;
        string posicion;
        Fecha fechaNacimiento;
        double estatura;
        string club;
        int numeroGoles;
        int fechaSancion;
        bool titular;
        int fkEquipo;
        string tabla;

    public:
        Jugador();
        void asignarDatos(int,string,string,string,int,string,Fecha,double,
            string,int,int,bool,int);
        void cadena(string*);
        void modificarNumSanciones(int);

        string getApellido();
        int getCed();
        string getClub();
        double getEstatura();
        Fecha getFechaNacimiento();
        int getFechaSancion();
        string getNacionalidad();
        string getNombre();
        int getNumero();
        int getNumeroGoles();
        string getPosicion();
        string getTabla();
        bool getTitular();

        string *obtenerregistro();
};

Jugador::Jugador(){tabla="Jugador";}

void Jugador::asignarDatos(int ced,string nombre,string apellido,
    string nacionalidad,int numero,string posicion,Fecha fechan,double estatura,
    string club,int numerogoles,int numerosanciones,bool titular,int fk)
{
    this->ced=ced;
    this->nombre=nombre;
    this->apellido=apellido;
    this->nacionalidad=nacionalidad;
    this->numero=numero;
    this->posicion=posicion;
    this->fechaNacimiento=fechan;
    this->estatura=estatura;
    this->club=club;
    this->numeroGoles=numerogoles;
    this->fechaSancion=numerosanciones;
    this->titular=titular;
    this->fkEquipo=fk;
}

void Jugador::cadena (string * datos)
{
    int ced=atoi(datos[0].c_str ());
    int numero=atoi(datos[4].c_str ());
    int dia=atoi (datos[6].c_str());
    int mes=atoi (datos[7].c_str());
    int ano=atoi (datos[8].c_str());
    double estatura=atof (datos[9].c_str());
    int numgoles=atoi(datos[11].c_str());
    int numsancion=atoi(datos[12].c_str());
    bool titular=false;
    if (datos[13] == "1")titular=true;
    int fk=atoi(datos[14].c_str ());
    Fecha fechanueva=*new Fecha();
    fechanueva.poner (dia, mes, ano, 0, 0);
    this->asignarDatos (ced,datos[1],datos[2],datos[3],numero,datos[5],
        fechanueva,estatura,datos[10],numgoles,numsancion,titular,fk);
}

string *Jugador::obtenerregistro ()
{
    ostringstream estatura;
    stringstream  id,numero,dia,mes,ano,numgoles,numsanciones,fk;
    string *datos=new string [15];
    estatura<<this->estatura;
    id<<this->ced;
    numero<<this->numero;
    dia<<this->fechaNacimiento.getdia ();
    mes<<this->fechaNacimiento.getmes ();
    ano<<this->fechaNacimiento.getano ();
    numgoles<<this->numeroGoles;
    numsanciones<<this->fechaSancion;
    fk<<this->fkEquipo;
    datos[0]=id.str();
    datos[1]=this->nombre;
    datos[2]=this->apellido;
    datos[3]=this->nacionalidad;
    datos[4]=numero.str();
    datos[5]=this->posicion;
    datos[6]=dia.str();
    datos[7]=mes.str();
    datos[8]=ano.str();
    datos[9]=estatura.str();
    datos[10]=this->club;
    datos[11]=numgoles.str();
    datos[12]=numsanciones.str();
    if (this->titular==0)datos[13]="0";
    else datos[13]="1";
    datos[14]=fk.str ();
    return datos;
}

void Jugador::modificarNumSanciones(int fechassacion){this->fechaSancion=fechassacion;}

string Jugador::getApellido(){return apellido;}

int Jugador::getCed(){return ced;}

string Jugador::getClub(){return club;}

double Jugador::getEstatura(){return estatura;}

Fecha Jugador::getFechaNacimiento(){return fechaNacimiento;}

int Jugador::getFechaSancion(){return fechaSancion;}

string Jugador::getNacionalidad(){return nacionalidad;}

string Jugador::getNombre(){return nombre;}

int Jugador::getNumero(){return numero;}

int Jugador::getNumeroGoles(){return numeroGoles;}

string Jugador::getPosicion(){return posicion;}

string Jugador::getTabla(){return tabla;}

bool Jugador::getTitular(){return titular;}

#endif
