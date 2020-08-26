#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "Lista.cpp"
#include "Jugador.cpp"
#include "Partido.cpp"

#ifndef EQUIPO
#define EQUIPO

class Equipo
{
    private:
        int id;
        string nombre;
        string confederacion;
        int puestoFifa;
        int FK_entrenador;
        string tabla;
        Lista<Jugador> *convocados;

    public:
        Equipo();
        void asignarDatos(int,string,string,int,int);
        void cadena(string *);
        void darJugador(Jugador);
        void modificarJugador(Jugador,int);

        //getter
        string **getListaJugadorTodos();
        string **getListaJugadorTitular();
        string *getdatos();

        Jugador getJugador(int);
        string getTabla();
        int getId();
        string getNombre();
        string getConfederacion();
        int getPuesto();
        int getFk();
        int getCantJugadores();
};


Equipo::Equipo()
{
    convocados=new Lista<Jugador>();
    tabla="Equipo";
}

void Equipo::asignarDatos (int id, string nom, string conf, int puest, int fk)
{
    this->id=id;
    this->nombre=nom;
    this->confederacion=conf;
    this->puestoFifa=puest;
    this->FK_entrenador=fk;
}

void Equipo::cadena (string * cadena)
{
    int id=atoi(cadena[0].c_str());
    int puesto=atoi(cadena[3].c_str ());
    int fkEntrenador=atoi (cadena[4].c_str ());
    this->asignarDatos(id,cadena[1],cadena[2],puesto,fkEntrenador);
}

string *Equipo::getdatos ()
{
    stringstream id,puesto,fk;
    id<<this->id;
    puesto<<this->puestoFifa;
    fk<<this->FK_entrenador;
    string *datos=new string [5];
    datos[0]=id.str();
    datos[1]=nombre;
    datos[2]=confederacion;
    datos[3]=puesto.str ();
    datos[4]=fk.str();
    return datos;
}

string **Equipo::getListaJugadorTodos()
{
    string **lista=new string *[convocados->cantidadElementos ()];
    for (int i=0;i<convocados->cantidadElementos ();i++)
    {
        lista[i]=convocados->seleccionar (i).obtenerregistro ();
    }
    return lista;
}

string **Equipo::getListaJugadorTitular()
{
    string **lista=new string *[11];
    int j=0;
    for (int i=0;i<convocados->cantidadElementos ();i++)
    {
        if (convocados->seleccionar (i).getTitular ())
        {
            lista[j]=convocados->seleccionar (i).obtenerregistro ();
            j++;
        }
    }
    return lista;
}

void Equipo::darJugador(Jugador jug){convocados->insertarFin (jug);}

void Equipo::modificarJugador (Jugador jug, int val)
{
    convocados->modificar (val, jug);
}

string Equipo::getTabla (){return tabla;}

int Equipo::getId(){return id;}
string Equipo::getNombre(){return nombre;}
string Equipo::getConfederacion(){return confederacion;}
int Equipo::getPuesto(){return puestoFifa;}
int Equipo::getFk(){return FK_entrenador;}

Jugador Equipo::getJugador(int pos){return convocados->seleccionar (pos);}

int Equipo::getCantJugadores(){return convocados->cantidadElementos();}

#endif
