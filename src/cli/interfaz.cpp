#include <stdio.h>
#include <iostream>

using namespace std;

#include "Menu.cpp"
#include "Dialogos.cpp"
#include "../ctrl/Controller.cpp"

#ifndef INTERFAZ
#define INTERFAZ

class Interfaz
{
    private:
        Menu *menus;
        Controller *ctrl;
        Datos *dialogos;

        void bienvenida();
        void cargado();
        void fin();
        void guardado();
        void partidos();
        void simulacionPartido(int);
        void simulacionResultado();
        string **equiposcabeza(string **);

    public:
        Interfaz(Controller *);
        void run();
};

Interfaz::Interfaz(Controller *ctrl){this->ctrl=ctrl;}

void Interfaz::bienvenida()
{
	cout<<"--------------------------------------------------------"<<endl;
	cout<<"--Bienvenido a Mundial FIFA 2018--"<<endl;
	cout<<"---------------------------------------------------------"<<endl;
	cargado();
}

void Interfaz::cargado()
{
	cout<<"--------------------------------------------------------"<<endl;
	cout<<"--Cargando Datos de Base de Datos--"<<endl;
	cout<<"---------------------------------------------------------"<<endl;
    menus = new Menu();
	ctrl->cargardb (equiposcabeza (ctrl->getListaEquiposTodos ()));
	cout<<"Hecho Correctamente!"<<endl;
	cout<<"---------------------------------------------------------"<<endl;
}

void Interfaz::fin()
{
    guardado();
    cout<<"--------------------------------------------------------"<<endl;
	cout<<"--Gracias, Cerrando Programa------------"<<endl;
	cout<<"---------------------------------------------------------"<<endl;
}

void Interfaz::guardado()
{
    cout<<"--------------------------------------------------------"<<endl;
	cout<<"--Guardando Datos--------------------------"<<endl;
	cout<<"---------------------------------------------------------"<<endl;
}

string **Interfaz::equiposcabeza(string **equipos)
{
    string **seleccionados=new string *[8];
    char grupo='A';
    for (int i=0;i<8;i++)
    {
        seleccionados[i]=equipos[menus->seleccionPrimeraCabeza(equipos,grupo,32)];
        grupo++;
    }
    return seleccionados;
}

void Interfaz::partidos()
{
    int cantsim;
    cout<<"Cuantos Partidos desea programar?(max "<<(48-ctrl->getCantPartidos ())<<"): ";
    cin>>cantsim;
    if((48-ctrl->getCantPartidos ())<=cantsim)
    {
        simulacionPartido (cantsim);
    }
}

void Interfaz::simulacionPartido (int cantSimulacion)
{
    cout<<"-------"<<endl;
    cout<<"Ingrese la fecha para el comienzo del mundial"<<endl;
    Fecha NF=dialogos->nuevaFecha ();
    ctrl->programarPartido (NF);
}

void Interfaz::simulacionResultado ()
{
    if (!(ctrl->getCantPartidos () > 0))
    {
        cout<<"Es necesario tener al menos un solo partido"<<endl;
        if(menus->Sino ("¿Desea Simular los encuentros(Los resultados estarian vacios)?"))
        {
            cout<<"Es Necesario tener al menos un Resultado"<<endl;
            partidos();
            string **lista=ctrl->consultaListapartido ();
            for (int i=0;i<48;i++)
            {
                cout<<"Partido:"<<endl;
                cout<<lista[i][0]<<" VS "<<lista[i][1]<<" en "<<lista[i][2]<<endl;
                if (menus->menuManualoAutomatico () == 2)
                {
                    ctrl->programarResultados (i);
                    cout<<"Hecho Correctamente"<<endl;
                }
                else
                {
                    string **listajugadores=ctrl->consultaJugadoresPartido (i,1);
                    int seleccionjug;
                    int gol1,gol2,sup1=0,sup2=0,pen1=0,pen2=0;
                    cout<<"Ingrese Goles de "<<lista[i][0]<<": ";
                    cin>>gol1;
                    for (int i=0;i<gol1;i++)
                    {
                        cout<<"Seleccione el jugador que marco"<<endl;
                        seleccionjug=menus->seleccionJugador (listajugadores, 11);
                        ctrl->agregargoleadores (seleccionjug,i,1,0);
                    }
                    cout<<"Ingrese Goles de "<<lista[i][1]<<": ";
                    cin>>gol2;
                    listajugadores=ctrl->consultaJugadoresPartido (i,2);
                    for (int i=0;i<gol2;i++)
                    {
                        cout<<"Seleccione el jugador que marco"<<endl;
                        seleccionjug=menus->seleccionJugador (listajugadores, 11);
                        ctrl->agregargoleadores (seleccionjug,i,2,0);
                    }
                    if (gol1 == gol2)
                    {
                        cout<<"Ingrese Goles Suplementarios de "<<lista[i][0]<<": ";
                        cin>>sup1;
                        listajugadores=ctrl->consultaJugadoresPartido (i,1);
                        for (int i=0;i<sup1;i++)
                        {
                            cout<<"Seleccione el jugador que marco"<<endl;
                            seleccionjug=menus->seleccionJugador (listajugadores, 11);
                            ctrl->agregargoleadores (seleccionjug,i,1,1);
                        }
                        cout<<"Ingrese Goles Suplementarios de "<<lista[i][1]<<": ";
                        cin>>sup2;
                        listajugadores=ctrl->consultaJugadoresPartido (i,2);
                        for (int i=0;i<sup2;i++)
                        {
                            cout<<"Seleccione el jugador que marco"<<endl;
                            seleccionjug=menus->seleccionJugador (listajugadores, 11);
                            ctrl->agregargoleadores (seleccionjug,i,2,1);
                        }
                        if (sup1 == sup2)
                        {
                            cout<<"Ingrese Goles de penales de "<<lista[i][0]<<": ";
                            cin>>pen1;
                            listajugadores=ctrl->consultaJugadoresPartido (i,1);
                            for (int i=0;i<pen1;i++)
                            {
                                cout<<"Seleccione el jugador que marco"<<endl;
                                seleccionjug=menus->seleccionJugador (listajugadores, 11);
                                ctrl->agregargoleadores (seleccionjug,i,1,2);
                            }
                            listajugadores=ctrl->consultaJugadoresPartido (i,1);
                            cout<<"Ingrese Goles de penales de "<<lista[i][1]<<": ";
                            cin>>pen2;
                            for (int i=0;i<pen2;i++)
                            {
                                cout<<"Seleccione el jugador que marco"<<endl;
                                seleccionjug=menus->seleccionJugador (listajugadores, 11);
                                ctrl->agregargoleadores (seleccionjug,i,2,2);
                            }
                        }
                    }
                    int numsancionados1,numsancionados2;
                    ctrl->programarResultados(gol1,gol2,sup1,sup2,pen1,pen2,i+1);
                    cout<<"ingrese el numero de sancionados de "<<lista[i][0]<<": ";
                    cin>>numsancionados1;
                    cout<<"ingrese el numero de sancionados de "<<lista[i][1]<<": ";
                    cin>>numsancionados2;
                    int numsancion;
                    listajugadores=ctrl->consultaJugadoresPartido (i,1);
                    for (int i=0;i<numsancionados1;i++)
                    {
                        seleccionjug=menus->seleccionJugador (listajugadores, 11);
                        cout<<"Ingrese las fechas de sancion (Por numeros): ";
                        cin>>numsancion;
                        ctrl->modificarSancionesJugador (numsancion, seleccionjug, i, 1);
                    }
                    listajugadores=ctrl->consultaJugadoresPartido (i,2);
                    for (int i=0;i<numsancionados2;i++)
                    {
                        seleccionjug=menus->seleccionJugador (listajugadores, 11);
                        cout<<"Ingrese las fechas de sancion (Por numeros): ";
                        cin>>numsancion;
                        ctrl->modificarSancionesJugador (numsancion, seleccionjug, i, 2);
                    }
                    cout<<"Modificado Correctamente"<<endl;
                }
            }
        }
    }
    else
    {
        string **lista=ctrl->consultaListapartido ();
        for (int i=0;i<48;i++)
        {
            cout<<"Partido:"<<endl;
            cout<<lista[i][0]<<" VS "<<lista[i][1]<<" en "<<lista[i][2]<<endl;
            if (menus->menuManualoAutomatico () == 2)
            {
                ctrl->programarResultados (i);
                cout<<"hecho Correctamente"<<endl;
            }
            else
            {
                int gol1,gol2,sup1=0,sup2=0,pen1=0,pen2=0;
                cout<<"Ingrese Goles de "<<lista[i][0]<<": ";
                cin>>gol1;
                cout<<"Ingrese Goles de "<<lista[i][1]<<": ";
                cin>>gol2;
                if (gol1 == gol2)
                {
                    cout<<"Ingrese Goles Suplementarios de "<<lista[i][0]<<": ";
                    cin>>sup1;
                    cout<<"Ingrese Goles Suplementarios de "<<lista[i][1]<<": ";
                    cin>>sup2;
                    if (sup1 == sup2)
                    {
                        cout<<"Ingrese Goles de penales de "<<lista[i][0]<<": ";
                        cin>>pen1;
                        cout<<"Ingrese Goles de penales de "<<lista[i][1]<<": ";
                        cin>>pen2;
                    }
                }
                ctrl->programarResultados(gol1,gol2,sup1,sup2,pen1,pen2,i+1);
            }
        }
    }
}

void Interfaz::run()
{
    bienvenida ();
    dialogos=new Datos();
    int opcionmenuprinci=menus->menuprincipal ();
    while (opcionmenuprinci != 7)
    {
        switch (opcionmenuprinci)
        {
            case (1):
            {
                int opcionmenusecu=menus->menulistas();
                while (opcionmenusecu != 8)
                {
                    switch (opcionmenusecu)
                    {
                        case (1):
                        {
                            //Mostrara los jugadores alineados por cada partidos
                            //para ello hay que tener partidos listos.
                            if (!(ctrl->getCantPartidos () > 0))
                            {
                                cout<<"Es necesario tener al menos un solo partido"<<endl;
                                if(menus->Sino ("¿Desea Simular los encuentros(Los resultados estarian vacios)?"))
                                {
                                    int cantsim;
                                    cout<<"Cuantos Partidos desea programar?(max "<<(48-ctrl->getCantPartidos ())<<"): ";
                                    cin>>cantsim;
                                    if((48-ctrl->getCantPartidos ())<=cantsim)
                                    {
                                        simulacionPartido (cantsim);
                                        int valor=menus->seleccionPartido
                                            (ctrl->consultaListapartido (),ctrl->getCantPartidos ());

                                        cout<<"----------------------"<<endl;
                                        cout<<"Alienacion de equipo "<<ctrl->consultaListapartido ()[valor][0]<<endl;
                                        cout<<"----------------------"<<endl;
                                        dialogos->mostrarDatosJugador (ctrl->consultaJugadoresPartido (valor, 1), 11);

                                        cout<<"----------------------"<<endl;
                                        cout<<"Alienacion de equipo "<<ctrl->consultaListapartido ()[valor][1]<<endl;
                                        cout<<"----------------------"<<endl;
                                        dialogos->mostrarDatosJugador (ctrl->consultaJugadoresPartido (valor, 2), 11);
                                    }
                                }
                            }
                            else
                            {
                                int valor=menus->seleccionPartido
                                    (ctrl->consultaListapartido (),ctrl->getCantPartidos ());

                                cout<<"----------------------"<<endl;
                                cout<<"Alienacion de equipo "<<ctrl->consultaListapartido ()[valor][0]<<endl;
                                cout<<"----------------------"<<endl;
                                dialogos->mostrarDatosJugador (ctrl->consultaJugadoresPartido (valor, 1), 11);

                                cout<<"----------------------"<<endl;
                                cout<<"Alienacion de equipo "<<ctrl->consultaListapartido ()[valor][1]<<endl;
                                cout<<"----------------------"<<endl;
                                dialogos->mostrarDatosJugador (ctrl->consultaJugadoresPartido (valor, 2), 11);
                            }
                        }
                        break;
                        case (2):
                        {
                            string **lista=ctrl->consultaEquiposTodos
                                (menus->menuconferacion ());
                            dialogos->mostrarDatosEquipo
                                (lista, ctrl->getCantidadRegistro ());
                        }
                        break;
                        case (3):
                        {
                            int equiposel=menus->seleccionEquipo
                                (ctrl->consultaEquiposTodos (""), 32);
                            int grupo=(equiposel/4);
                            string **lista=ctrl->consultaListaJug
                                ("", grupo, equiposel);
                            dialogos->mostrarDatosJugador
                                (lista, ctrl->getCantidadRegistro ());
                        }
                        break;
                        case (4):
                        {
                            if (!(ctrl->getCantPartidos () > 0))
                            {
                                cout<<"Es necesario tener al menos un solo partido"<<endl;
                                if(menus->Sino ("¿Desea Simular los encuentros(Los resultados estarian vacios)?"))
                                {
                                    int cantsim;
                                    cout<<"Cuantos Partidos desea programar?(max "<<(48-ctrl->getCantPartidos ())<<"): ";
                                    cin>>cantsim;
                                    if((48-ctrl->getCantPartidos ())<=cantsim)
                                    {
                                        simulacionPartido (cantsim);
                                        cout<<"-------"<<endl;
                                        cout<<"Ingrese la fecha para evaluar partidos"<<endl;
                                        Fecha NF=dialogos->nuevaFecha ();
                                        dialogos->mostrarDatosPartido (ctrl->consultaPartidosconFecha (NF),
                                            ctrl->getCantidadRegistro ());
                                    }
                                }
                            }
                            else
                            {
                                cout<<"-------"<<endl;
                                cout<<"Ingrese la fecha para evaluar partidos"<<endl;
                                Fecha NF=dialogos->nuevaFecha ();
                                dialogos->mostrarDatosPartido (ctrl->consultaPartidosconFecha (NF),
                                ctrl->getCantidadRegistro ());
                            }
                        }
                        break;
                        case (5):
                        {
                            //Lista de Goleadores
                            simulacionResultado ();
                            cout<<"Lista de Jugadores Ordenada"<<endl;
                            string **lista=ctrl->consultaGoleadoresOrdenada ();
                            cout<<ctrl->getCantidadRegistro ()<<endl;
                            dialogos->mostrarDatosGoleadores (lista,ctrl->getCantidadRegistro ());
                        }
                        break;
                        case (6):
                        {
                            string **lista=ctrl->consultaEquiposGrupo
                                (menus->menugrupo ()-1);
                            dialogos->mostrarDatosEquipo (lista,ctrl->getCantidadRegistro ());
                        }
                        break;
                        case (7):
                        {
                            simulacionResultado ();
                        }
                        break;
                    }
                    opcionmenusecu=menus->menulistas();
                }
            }
            break;
            case(2):
            {
                int opcionmenusecu=menus->menuConsultas ();
                while (opcionmenusecu!=10)
                {
                    switch(opcionmenusecu)
                    {
                        case (1):
                        {
                            int equiposel=menus->seleccionEquipo
                                (ctrl->consultaEquiposTodos (""), 32);
                            int grupo=(equiposel/4);
                            string **lista=ctrl->consultaListaJug
                                ("", grupo, equiposel);
                            dialogos->mostrarDatosJugador
                                (lista, ctrl->getCantidadRegistro ());
                            string *datos=ctrl->consultaEntrenadordeEquipo (grupo, equiposel%4);
                            cout<<"Entrenador de equipo:"<<datos[1]<<" "<<datos[2]<<" - "<<datos[3]<<endl;
                        }
                        break;
                        case (2):
                        {
                            if (!(ctrl->getCantPartidos () > 0))
                            {
                                cout<<"Es necesario tener al menos un solo partido"<<endl;
                                if(menus->Sino ("¿Desea Simular los encuentros(Los resultados estarian vacios)?"))
                                {
                                    int cantsim;
                                    cout<<"Cuantos Partidos desea programar?(max "<<(48-ctrl->getCantPartidos ())<<"): ";
                                    cin>>cantsim;
                                    if((48-ctrl->getCantPartidos ())<=cantsim)
                                    {
                                        simulacionPartido (cantsim);
                                        cout<<"-------"<<endl;
                                        cout<<"Ingrese la fecha para evaluar partidos"<<endl;
                                        Fecha NF=dialogos->nuevaFecha ();
                                        string **lista=ctrl->consultaPartidosconFecha (NF);
                                        dialogos->mostrarDatosPartido (lista,
                                            ctrl->getCantidadRegistro ());
                                    }
                                }
                            }
                            else
                            {
                                cout<<"-------"<<endl;
                                cout<<"Ingrese la fecha para evaluar partidos"<<endl;
                                Fecha NF=dialogos->nuevaFecha ();
                                string **lista=ctrl->consultaPartidosconFecha (NF);
                                dialogos->mostrarDatosPartido (lista,
                                ctrl->getCantidadRegistro ());
                            }
                        }
                        break;
                        case (3):
                        {
                            //Partidos Jugados y resultados en cierta fecha
                            simulacionResultado ();
                            if (!(ctrl->getCantPartidos () > 0))
                            {
                                cout<<"-------"<<endl;
                                cout<<"Ingrese la fecha para evaluar partidos"<<endl;
                                Fecha NF=dialogos->nuevaFecha ();
                                string **lista=ctrl->consultaPartidosconFecha (NF);
                                dialogos->mostrarDatosPartido (lista,
                                    ctrl->getCantidadRegistro ());

                            }
                        }
                        break;
                        case (4):
                        {
                            //Partidos Programados en cierto Estadio
                            if (!(ctrl->getCantPartidos () > 0))
                            {
                                cout<<"Es necesario tener al menos un solo partido"<<endl;
                                if(menus->Sino ("¿Desea Simular los encuentros(Los resultados estarian vacios)?"))
                                {
                                    int cantsim;
                                    cout<<"Cuantos Partidos desea programar?(max "<<(48-ctrl->getCantPartidos ())<<"): ";
                                    cin>>cantsim;
                                    if((48-ctrl->getCantPartidos ())<=cantsim)
                                    {
                                        simulacionPartido (cantsim);
                                        cout<<"-------"<<endl;
                                        string **lista=ctrl->consultaEstadiosTodos ();
                                        string **listaeq=ctrl->consultaPartidosEstadio
                                            (menus->seleccionEstadio(lista, ctrl->getCantidadRegistro ()));
                                        dialogos->mostrarDatosPartido
                                            (listaeq, ctrl->getCantidadRegistro ());
                                    }
                                }
                            }
                            else
                            {
                                string **lista=ctrl->consultaEstadiosTodos ();
                                string **listaeq=ctrl->consultaPartidosEstadio
                                    (menus->seleccionEstadio(lista, ctrl->getCantidadRegistro ()));
                                dialogos->mostrarDatosPartido
                                    (listaeq, ctrl->getCantidadRegistro ());
                            }
                        }
                        break;
                        case (5):
                        {
                            //Jugadores sancionados
                            simulacionResultado ();
                            cout<<"Jugadores Sancionados"<<endl;
                            string **lista=ctrl->consultaJugadoresSancionados ();
                            cout<<"Cantidad reg: "<<ctrl->getCantidadRegistro ()<<endl;
                            dialogos->mostrarDatosJugador (lista, ctrl->getCantidadRegistro ());
                        }
                        break;
                        case (6):
                        {
                            //Goleadores en orden
                            simulacionResultado ();
                            cout<<"Lista de Jugadores Ordenada"<<endl;
                            string **lista=ctrl->consultaGoleadoresOrdenada ();
                            dialogos->mostrarDatosGoleadores (lista,ctrl->getCantidadRegistro ());
                        }
                        break;
                        case (7):
                        {
                            //puntos obtenidos en orden en cierta fecha
                            simulacionResultado ();
                        }
                        break;
                        case (8):
                        {
                            //Resumen de Resultados de la Segunda Fecha
                            simulacionResultado ();
                        }
                        break;
                        case (9):
                        {
                            simulacionResultado ();
                            //Valor a insertAll
                            int x;
                            cout<<"ingrese elnumero de goles: ";
                            cin>>x;
                            string **lista=ctrl->goleadoresconciertacantidad (x);
                        }
                        break;
                    }
                    opcionmenusecu=menus->menuConsultas ();
                }
            }
            break;
            case(3):
            {
                int opcionmenusecu=menus->menuConsultas ();
                while (opcionmenusecu!=2)
                {
                    switch (opcionmenusecu)
                    {
                        case (1):
                        {
                            //Modificar Plantilla
                        }
                        break;
                    }
                    opcionmenusecu=menus->menuConsultas ();
                }
            }
            break;
            case (4):
            {
                //Guardar Partido
                cout<<"guardar partido"<<endl;
                ctrl->guardarPartido ();
                cout<<"guardado correctamente"<<endl;
            }
            break;
            case (5):
            {
                //Guardar Resultados
                cout<<"guardar partido"<<endl;
                ctrl->guardarResultado ();
                cout<<"guardado correctamente"<<endl;
            }
            break;
            case (6):
            {
                //Guardar goleadores
                cout<<"guardar goleadores"<<endl;
                ctrl->guardarGoleadores ();
                cout<<"guardado correctamente"<<endl;
            }
            break;
        }
        opcionmenuprinci=menus->menuprincipal ();
    }
    fin ();
}

#endif
