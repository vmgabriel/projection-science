#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "Lista.cpp"
#include "Equipo.cpp"

#ifndef GRUPO
#define GRUPO

class Grupo
{
    private:
        char cod;
        Lista<Equipo> *equipos;

    public:
        Grupo(){equipos=new Lista<Equipo>();}
        Grupo(char);
        void insertarEquipo(Equipo);
        void modificarEquipo(Equipo,int);

        Equipo getEquipo(int);
        char getCod();
        int getcantequipos();
};

Grupo::Grupo(char nom)
{
    equipos=new Lista<Equipo>();
    this->cod=nom;
}

void Grupo::modificarEquipo(Equipo Eq,int pos){equipos->modificar (pos, Eq);}

void Grupo::insertarEquipo(Equipo eq){equipos->insertarFin(eq);}

char Grupo::getCod(){return cod;}

int Grupo::getcantequipos(){return equipos->cantidadElementos ();}

Equipo Grupo::getEquipo(int pos){return equipos->seleccionar(pos);}

#endif
