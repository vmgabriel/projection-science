#include <stdio.h>
#include <iostream>
#include <string>

//Habria que intentar evitar esto, pero como es una libreria de primer orden
//no pienso que rompa el esquema de Orientada a Objetos
#include "../lib/Fecha.cpp"

using namespace std;

#ifndef DATOS
#define DATOS

class Datos
{
    private:
        void pause();
        void separador();

    public:
        Datos();
        void mostrarDatosEquipo(string **,int);
        void mostrarDatosJugador(string **,int);
        void mostrarDatosPartido(string **,int);
        void mostrarDatosGoleadores(string **,int);
        void mostrarDatosResultados(string *);

        Fecha nuevaFecha();
};

Datos::Datos(){}

void Datos::separador()
{
    cout<<"-------------------------------"<<endl;
}

//#FIXME "Modifcar para que sea practica la impresion con printf"
void Datos::mostrarDatosEquipo(string **datos,int cant)
{
    separador ();
    cout<<"-Lista de Equipos-"<<endl;
    cout<<"Cod | Nombre | Confederacion | PuestoFiFa |Entrenador | NacionalidadEntrenador |"<<endl;
    separador ();
    for(int i=0;i<cant;i++)
    {
        cout<<datos[i][0]<<" | ";
        cout<<datos[i][1]<<" | ";
        cout<<datos[i][2]<<" | ";
        cout<<datos[i][3]<<" | ";
        cout<<datos[i][4]<<" | ";
        cout<<datos[i][5]<<" | "<<endl;
    }
    separador ();
}

void Datos::mostrarDatosJugador(string ** lista,int cant)
{
    separador ();
    cout<<"-Lista de Jugadores-"<<endl;
    cout<<"Cod | Nombre | Apellido | Nacionalidad | Numero | posicion | FechaNacimiento | Estatura | Titular? |"<<endl;
    for (int i=0;i<cant;i++)
    {
        cout<<lista[i][0]<<" | ";
        cout<<lista[i][1]<<" | ";
        cout<<lista[i][2]<<" | ";
        cout<<lista[i][3]<<" | ";
        cout<<lista[i][4]<<" | ";
        cout<<lista[i][5]<<" | ";
        cout<<lista[i][6]<<"/";
        cout<<lista[i][7]<<"/";
        cout<<lista[i][8]<<" | ";
        cout<<lista[i][9]<<" | ";
        if (lista[i][13]=="1")cout<<"Si |"<<endl;
        else cout<<"No |"<<endl;
    }
    separador ();
}

void Datos::mostrarDatosPartido(string ** lista,int cant)
{
    separador ();
    cout<<"------lista de partidos----"<<endl;
    cout<<"Cod | Equipo1 | Equipo2 | Estadio | Fecha y Hora |"<<endl;
    separador ();
    for (int i=0;i<cant;i++)
    {
        cout<<lista[i][0]<<" | ";
        cout<<lista[i][1]<<" | ";
        cout<<lista[i][2]<<" | ";
        cout<<lista[i][3]<<" | ";
        cout<<lista[i][4]<<"/";
        cout<<lista[i][5]<<"/";
        cout<<lista[i][6]<<" ";
        cout<<lista[i][7]<<":00"<<endl;
    }
    separador ();
}

void Datos::mostrarDatosGoleadores (string ** lista, int cant)
{
    separador ();
    cout<<"------lista de Goleadores----"<<endl;
    cout<<"Nombre | Apellido | Goles | Seleccion |"<<endl;
    separador ();
    for (int i=0;i<cant;i++)
    {
        cout<<lista[i][0]<<" | ";
        cout<<lista[i][1]<<" | ";
        cout<<lista[i][2]<<" | ";
        cout<<lista[i][3]<<" | "<<endl;
    }
    separador ();
}

void Datos::mostrarDatosResultados(string * resultado)
{
    separador ();
    cout<<"------Resultado----"<<endl;
    cout<<"Goles de EQ 1 | Goles de EQ 2 | Goles de Sup 1 | Goles de Sup 2 | Goles de Penales 1 | Goles de Penales 2 |"<<endl;
    separador ();
    cout<<resultado[1]<<" | "<<resultado[2]<<" | "<<resultado[3]<<" | ";
    cout<<resultado[4]<<" | "<<resultado[5]<<" | "<<resultado[6]<<endl;
    separador ();
}

Fecha Datos::nuevaFecha ()
{
    int dia,mes,ano;
    separador ();
    bool correcto=true;
    Fecha NFecha=*new Fecha();
    while (correcto)
    {
        cout<<"Ingrese dia: ";
        cin>>dia;
        cout<<"Ingrese mes: ";
        cin>>mes;
        cout<<"Ingrese año: ";
        cin>>ano;
        correcto=!(NFecha.poner (dia, mes, ano, 0, 0));
    }
    return NFecha;
}

#endif
