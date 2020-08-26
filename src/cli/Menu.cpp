#include <stdio.h>
#include <iostream>

using namespace std;

#ifndef MENU
#define MENU

class Menu
{
    private:
        void separador();

    public:
        Menu();
        int menuprincipal();
        int menulistas();
        int menugrupo();
        int menuConsultas();
        int menuSimulacion();
        int menuManualoAutomatico();
        bool Sino(string);
        int seleccionPrimeraCabeza(string **, char,int);
        int seleccionEquipo(string **,int);
        int seleccionPartido(string **,int);
        int seleccionEstadio(string **,int);
        int seleccionJugador(string **,int);
        string menuconferacion();
};

Menu::Menu(){}

void Menu::separador ()
{
    cout<<"--------------------------------"<<endl;
}

bool Menu::Sino(string mensaje)
{
    separador ();
    cout<<mensaje<<endl;
    separador ();
    cout<<"1. Si"<<endl;
    cout<<"2. No"<<endl;
    int x;
    cin>>x;
    bool valor=false;
    if (x==1)valor=true;
    return valor;
}

int Menu::menuprincipal()
{
    separador();
    cout<<"------------Menu Principal----------------------"<<endl;
    separador();
    cout<<"1. Listas"<<endl;
    cout<<"2. Consultas"<<endl;
    cout<<"3. Simulacion"<<endl;
    cout<<"4. Guardar Programacion de Partidos"<<endl;
    cout<<"5. Guardar Resultados de Partidos"<<endl;
    cout<<"6. Guardar Goleadores"<<endl;
    cout<<"7. Salir"<<endl;
    separador();
    cout<<"Ingrese el valor: ";
    int x;
    cin>>x;
    return x;
}

int Menu::menulistas()
{
    separador();
    cout<<"------------Menu Listas----------------------"<<endl;
    separador();
    cout<<"1. Lista de Jugadores Alineados en cada equipo"<<endl;
    cout<<"2. Lista de Selecciones de Cada Confederacion"<<endl;
    cout<<"3. Lista de Jugadores por equipo"<<endl;
    cout<<"4. Lista de partidos programados para fecha"<<endl;
    cout<<"5. Lista de Goleadores"<<endl;
    cout<<"6. Lista de Cada Grupo en Primera Fase"<<endl;
    cout<<"7. Arbol para segunda Fase"<<endl;
    cout<<"8. Atras"<<endl;
    separador();
    cout<<"Ingrese el valor: ";
    int x;
    cin>>x;
    return x;
}

int Menu::menuConsultas ()
{
    separador();
    cout<<"------------Menu Consultas----------------------"<<endl;
    separador();
    cout<<"1. Director Tecnico y Jugadores de cierto Pais"<<endl;
    cout<<"2. Lista de Juegos con su estadio y equipos en cierta fecha"<<endl;
    cout<<"3. Partidos jugados y resultados de cierto equipo"<<endl;
    cout<<"4. Lista de Partidos Programadas en cierto estadio"<<endl;
    cout<<"5. Jugadores Sancionados en cierta fecha"<<endl;
    cout<<"6. Tabla de Goleadores en Orden"<<endl;
    cout<<"7. Puntos obtenidos en orden de cierto grupo"<<endl;
    cout<<"8. Resumen de Resultados de la Segunda Fecha"<<endl;
    cout<<"9. Goleadores con mayor numero de goles que"<<endl;
    cout<<"10. Atras"<<endl;
    separador();
    cout<<"Ingrese el valor: ";
    int x;
    cin>>x;
    return x;
}


int Menu::menuSimulacion ()
{
    separador();
    cout<<"------------Menu Simulacion----------------------"<<endl;
    separador();
    cout<<"1. Modificar plantilla de titulares de equipo"<<endl;
    cout<<"2. Atras"<<endl;
    separador();
    cout<<"Ingrese el valor: ";
    int x;
    cin>>x;
    return x;
}



string Menu::menuconferacion()
{
    separador();
    cout<<"------------Seleccion Confederacion----------------"<<endl;
    separador();
    cout<<"1. CONMEBOL (Sudamerica)"<<endl;
    cout<<"2. CONCACAF (America Norte y Centro America)"<<endl;
    cout<<"3. CAF (Africa)"<<endl;
    cout<<"4. AFC (Asia)"<<endl;
    cout<<"5. UEFA (Europa)"<<endl;
    separador();
    cout<<"Ingrese el valor: ";
    int x;
    cin>>x;
    switch(x)
    {
        case(1):return "CONMEBOL";
        break;
        case(2):return "CONCACAF";
        break;
        case(3):return "CAF";
        break;
        case(4):return "AFC";
        break;
        default:return "UEFA";
        break;
    }
}

int Menu::menugrupo()
{
    separador();
    cout<<"------------Seleccion Grupo----------------"<<endl;
    separador();
    cout<<"1. A"<<endl;
    cout<<"2. B"<<endl;
    cout<<"3. C"<<endl;
    cout<<"4. D"<<endl;
    cout<<"5. E"<<endl;
    cout<<"6. F"<<endl;
    cout<<"7. G"<<endl;
    cout<<"8. H"<<endl;
    separador();
    cout<<"Ingrese el valor: ";
    int x;
    cin>>x;
    return x;
}

int Menu::menuManualoAutomatico ()
{
    separador();
    cout<<"-----¿Manual o Automatico?-----------"<<endl;
    separador();
    cout<<"1. Manual"<<endl;
    cout<<"2. Automatico"<<endl;
    separador();
    cout<<"Ingrese el valor: ";
    int x;
    cin>>x;
    return x;
}

int Menu::seleccionPrimeraCabeza(string **lista , char grupo, int cantequipos)
{
    separador();
    cout<<"------------Seleccion Cabeza Grupo "<<grupo<<"--------------"<<endl;
    cout<<"------------"<<endl;
    for (int i=0;i<cantequipos;i++)
    {
        cout<<i<<". ";
        cout<<lista[i][1]<<" | ";
        cout<<lista[i][2]<<endl;
    }
    separador();
    cout<<"Seleccione cabeza de Grupo: ";
    int x;
    cin>>x;
    return x;
}

int Menu::seleccionEquipo(string ** lista,int cantequipos)
{
    separador();
    cout<<"----------------Seleccion Equipo----------------------"<<endl;
    separador();
    for (int i=0;i<cantequipos;i++)
    {
        cout<<i<<". ";
        cout<<lista[i][1]<<" | ";
        cout<<lista[i][2]<<endl;
    }
    separador();
    cout<<"Seleccione Equipo: ";
    int x;
    cin>>x;
    return x;
}

int Menu::seleccionPartido(string **lista,int cant)
{
    separador();
    cout<<"-----------------Seleccion Partido-----------------------"<<endl;
    separador();
    for(int i=0;i<cant;i++)
    {
        cout<<i<<". ";
        cout<<lista[i][0]<<" vs ";
        cout<<lista[i][1]<<" en ";
        cout<<lista[i][2]<<endl;
    }
    separador();
    cout<<"Seleccione Partido: ";
    int x;
    cin>>x;
    return x;
}

int Menu::seleccionEstadio(string ** lista,int cantestadios)
{
    separador();
    cout<<"----------------Seleccion Estadio----------------------"<<endl;
    separador();
    for (int i=0;i<cantestadios;i++)
    {
        cout<<i<<". ";
        cout<<lista[i][1]<<" | ";
        cout<<lista[i][3]<<endl;
    }
    separador();
    cout<<"Seleccione Estadio: ";
    int x;
    cin>>x;
    return x;
}

int Menu::seleccionJugador (string ** lista, int cantjug)
{
    separador ();
    cout<<"-------------------Seleccion Jugador-------------------"<<endl;
    separador ();
    for (int i=0;i<cantjug;i++)
    {
        if (lista[i][13] == "1")
        {
            cout<<i<<". ";
            cout<<lista[i][1]<<" ";
            cout<<lista[i][2]<<" | ";
            cout<<lista[i][5]<<" | ";
            cout<<lista[i][6]<<endl;
        }
    }
    separador ();
    cout<<"Seleccione Jugador: ";
    int x;
    cin>>x;
    return x;
}
#endif
