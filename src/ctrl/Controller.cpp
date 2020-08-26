#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>

#include "../db/BaseDatos.cpp"
#include "../lib/Grupo.cpp"
#include "../lib/Equipo.cpp"
#include "../lib/Entrenador.cpp"
#include "../lib/Seleccion.cpp"
#include "../lib/Estadio.cpp"
#include "../lib/Resultado.cpp"
#include "../lib/Goleadores.cpp"

#ifndef CONTROLLER
#define CONTROLLER

class Controller
{
    private:
        int cantidadRegistro;
	    BaseDatos *db;
	    Lista<Grupo> *grupos;
	    Lista<Entrenador> *entrenadores;
	    Lista<Partido> *partidos;
	    Lista<Estadio> *estadios;
	    Lista<Goleadores> *goleadores;

	    void crearGrupos();
	    void llamareEquipos(string **);
	    void llamarEntrenadores();
	    void llamarSeleccionEntrenador();
	    void llamarJugadores();
	    void llamarPartido();
	    void llamarEstadios();
	    void llamarResultados();
	    void llamarGoleadores();

	    Lista<Equipo> *listaTodosEquipo();
	    Lista<Jugador> *listaTodosJUgador();

    public:
	    Controller(BaseDatos *);
	    void cargardb(string **);
	    void programarPartido(Fecha);
	    void programarResultados(int);
	    void programarResultados(int,int,int,int,int,int,int);
	    void modificarSancionesJugador(int,int,int,int);
	    void agregargoleadores(int,int,int,int);

	    void guardarPartido();
	    void guardarResultado();
	    void guardarGoleadores();
	    string ** goleadoresconciertacantidad(int);

	    string **listaEquipos();
	    string **consultaEquiposTodos(string);
	    string **consultaEquiposGrupo(int);
	    string **consultaListaJug(string,int,int);
	    string **consultaListapartido();//enfocado en la seleccion
	    string **consultaJugadoresPartido(int,int);
	    string **consultaPartidosconFecha(Fecha);
	    string *consultaEntrenadordeEquipo(int,int);
	    string **consultaEstadiosTodos();//Retorna todos los estadios
	    string **consultaPartidosEstadio(int);//Retorna partidos en cierto estadio
	    string **consultaGoleadoresOrdenada();
	    string **consultaJugadoresSancionados();
	    string *consultaResultadosdePartidos(int);

	    int getCantidadRegistro();
	    int getCantPartidos();
	    string **getListaEquiposTodos();
};

// Los valores no inicializados nunca son nulos ya que estos se inicializan
// Cuando se necesitan
Controller::Controller(BaseDatos *base){this->db=base;}

Lista<Equipo> *Controller::listaTodosEquipo()
{
    Lista<Equipo> *listatodosequipos=new Lista<Equipo>();
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<4;j++)
        {
            listatodosequipos->insertarFin
                (grupos->seleccionar (i).getEquipo (j));
        }
    }
    return listatodosequipos;
}

Lista<Jugador> *Controller::listaTodosJUgador ()
{
    Lista<Jugador> *lista=new Lista<Jugador>();
    Lista<Equipo> *listaeq=listaTodosEquipo ();
    for (int i=0;i<listaeq->cantidadElementos ();i++)
    {
        for (int j=0;j<listaeq->seleccionar (i).getCantJugadores ();j++)
        {
            lista->insertarFin (listaeq->seleccionar (j).getJugador (j));
        }
    }
    return lista;
}

void Controller::crearGrupos ()
{
    char nom='A';
    grupos=new Lista<Grupo>();
    for (int i=0;i<8;i++)
    {
        Grupo nuevo=*new Grupo(nom);
        grupos->insertarFin(nuevo);
        nom++;
    }
}

void Controller::llamareEquipos (string **listadatos)
{
    int k=0,l=0;
    string **lista=new string *[28];
    Equipo equipo=*new Equipo();
    for (int i=0;i<8;i++)//Datos de cabeza de grupo
    {
        Grupo grupotemp=grupos->seleccionar (i);
        equipo.cadena(listadatos[i]);
        grupotemp.insertarEquipo (equipo);
        grupos->modificar (i, grupotemp);
        equipo=*new Equipo();
    }
    for (int i=0;i<32;i++)
    {
        if (k!=8)
        {
            if (listadatos[k][0] == getListaEquiposTodos ()[i][0]){k++;}
            else
            {
                lista[l]=getListaEquiposTodos ()[i];
                l++;
            }
        }
        else
        {
            lista[l]=getListaEquiposTodos ()[i];
            l++;
        }
    }
    k=0;
    for (int i=0;i<3;i++)
    {
        for (int j=0;j<8;j++)
        {
            Grupo grupotemp=grupos->seleccionar (j);
            equipo.cadena(lista[k]);
            grupotemp.insertarEquipo(equipo);
            grupos->modificar (j, grupotemp);
            equipo=*new Equipo();
            k++;
        }
    }
}

void Controller::llamarEntrenadores()
{
    entrenadores=new Lista<Entrenador>();
    Entrenador entrenador=*new Entrenador();
    string **listadatos=db->obtenerTodo (entrenador.getTabla ());
    for (int i=0;i<32;i++)
    {
        entrenador.cadena(listadatos[i]);
        entrenadores->insertarFin (entrenador);
        entrenador=*new Entrenador();
    }
}

void Controller::llamarSeleccionEntrenador()
{
    Seleccion seleccion = *new Seleccion();
    string **listadatos=db->obtenerTodo (seleccion.getTabla ());
    int j=0;
    for (int i=0;i<db->cantidadRegistros (seleccion.getTabla());i++)
    {
        seleccion.cadena (listadatos[i]);
        if (j+1 != seleccion.getfk ())j++;
        Entrenador entrenador=entrenadores->seleccionar (j);
        entrenador.agregarSeleccion (seleccion);
        entrenadores->modificar(j,entrenador);
        seleccion=*new Seleccion();
    }
}


//Es aqui donde ingresa los datos de los jugadores de los equipos que a su
//vez estan en grupos

void Controller::llamarJugadores ()
{
    for (int i=0;i<8;i++)
    {
        Grupo grupotemp=grupos->seleccionar (i);
        for (int j=0;j<4;j++)
        {
            Equipo equipotemp=grupotemp.getEquipo (j);
            stringstream  fk;
            fk<<equipotemp.getFk ();

            string **listadatos=db->obtenerRegistrosDato
                    ((*new Jugador()).getTabla (), fk.str(), 14);
            for (
                int k=0;
                k<db->cantidadRegistrosConDato((*new Jugador()).getTabla (), fk.str(), 14);
                k++)
            {
                Jugador nuevoJugador=*new Jugador();
                nuevoJugador.cadena (listadatos[k]);
                equipotemp.darJugador (nuevoJugador);
            }
            grupotemp.modificarEquipo (equipotemp,j);
        }
        grupos->modificar(i,grupotemp);
    }
}

//Saca de archivos los partidos y los modifica

void Controller::llamarPartido ()
{
    partidos=new Lista<Partido>();
    if (db->cantidadRegistros ((new Partido())->getTabla())!=0)
    {
        string **lista=db->obtenerTodo (((new Partido())->getTabla()));
        for (int i=0;i<db->cantidadRegistros ((new Partido())->getTabla());i++)
        {
            Partido Nuevo =*new Partido();
            Nuevo.cadena(lista[i]);
            partidos->insertarFin (Nuevo);
        }
    }
    else{cout<<"Partidos Vacios"<<endl;}
}

//LLamada basica de Estadios
void Controller::llamarEstadios ()
{
    estadios=new Lista<Estadio>();
    string **listadatos=db->obtenerTodo ((new Estadio())->getTabla ());
    for (int i=0;i<db->cantidadRegistros ((new Estadio())->getTabla());i++)
    {
        Estadio Nuevo=*new Estadio();
        Nuevo.cadena (listadatos[i]);
        estadios->insertarFin (Nuevo);
    }
}

//Llamada basica a Resultados de cada Partido, Si Hay
void Controller::llamarResultados ()
{
    if(partidos->cantidadElementos ()!=0)
    {
        string **listaResultados=db->obtenerTodo ((new Resultado)->getTabla());
        for (int i=0;i<partidos->cantidadElementos ();i++)
        {
            Partido partidotemp=partidos->seleccionar (i);
            int j=0;
            while(j<db->cantidadRegistros ((new Resultado)->getTabla()))
            {
                int fk=atoi(listaResultados[j][7].c_str ());
                if (fk == partidotemp.getId())
                {
                    Resultado nuevo=*new Resultado();
                    nuevo.cadena(listaResultados[j]);
                    partidotemp.darResultado (nuevo);
                    partidos->modificar (i, partidotemp);
                    j++;
                }
            }
        }
    }
    else{cout<<"Omitidos Resultados por Partidos no asignados"<<endl;}
}

void Controller::llamarGoleadores ()
{
    goleadores=new Lista<Goleadores>();
}

void Controller::cargardb (string **listaEquipos)
{
    cout<<"Creando Grupos"<<endl;
    crearGrupos ();
    cout<<"Cargando Equipos"<<endl;
    llamareEquipos (listaEquipos);
    cout<<"Cargando Entrenadores"<<endl;
    llamarEntrenadores ();
    cout<<"Cargando Seleccion de Entrenadores"<<endl;
    llamarSeleccionEntrenador ();
    cout<<"Cargando Jugadores de Seleccion"<<endl;
    llamarJugadores ();
    cout<<"Cargando Estadios"<<endl;
    llamarEstadios ();
    cout<<"Cargando Partidos Guardados"<<endl;
    llamarPartido ();
    cout<<"Cargando Resultados de Partidos Guardados"<<endl;
    llamarResultados ();
    cout<<"Cargando Goleadores"<<endl;
    llamarGoleadores ();
}

string **Controller::listaEquipos ()
{
    string ** lista=new string *[32];
    Lista<Equipo> *listatodosequipos=listaTodosEquipo ();
    for (int i=0;i<32;i++)
    {
        stringstream  id,puesto,fk;
        string *datos=new string [5];

        id<<listatodosequipos->seleccionar(i).getId();
        puesto<<listatodosequipos->seleccionar(i).getPuesto();
        fk<<listatodosequipos->seleccionar(i).getFk();

        datos[0]=id.str();
        datos[1]=listatodosequipos->seleccionar(i).getNombre ();
        datos[2]=listatodosequipos->seleccionar(i).getConfederacion ();
        datos[3]=puesto.str();
        datos[4]=fk.str();

        lista[i]=datos;
    }
    return lista;
}

//Consultas-----
string **Controller::consultaEquiposTodos(string conf)
{
    this->cantidadRegistro=0;
    string ** lista=new string *[32];
    Lista<Equipo> *listatodosequipos=listaTodosEquipo ();
    for (int i=0;i<32;i++)
    {
        stringstream  id,puesto;
        string *datos=new string [6];

        id<<listatodosequipos->seleccionar(i).getId();
        puesto<<listatodosequipos->seleccionar(i).getPuesto();

        datos[0]=id.str();
        datos[1]=listatodosequipos->seleccionar(i).getNombre();
        datos[2]=listatodosequipos->seleccionar(i).getConfederacion ();
        datos[3]=puesto.str();
        Entrenador temp=*new Entrenador();
        int k=0;
        while(temp.getCed() != listatodosequipos->seleccionar (i).getFk ())
        {
            temp=entrenadores->seleccionar (k);
            k++;
        }
        datos[4]=temp.getNombre ()+" "
            +temp.getapellido ();
        datos[5]=temp.getNacionalidad ();
        if (conf=="")lista[i]=datos;//Tome todos los datos de los equipos sin discriminar
        else if (conf==datos[2]){lista[cantidadRegistro]=datos;cantidadRegistro++;}
    }
    return lista;
}

string **Controller::consultaEquiposGrupo(int val)
{
    Grupo tempgrupo=grupos->seleccionar (val);
    string **lista=new string *[tempgrupo.getcantequipos ()];
    for (int i=0;i<tempgrupo.getcantequipos ();i++)
    {
        stringstream  id,puesto;
        string *datos=new string[6];

        id<<tempgrupo.getEquipo (i).getId ();
        puesto<<tempgrupo.getEquipo (i).getPuesto ();

        datos[0]=id.str();
        datos[1]=tempgrupo.getEquipo (i).getNombre ();
        datos[2]=tempgrupo.getEquipo (i).getConfederacion ();
        datos[3]=puesto.str();

        Entrenador temp=*new Entrenador();
        int k=0;
        while(temp.getCed () != tempgrupo.getEquipo (i).getFk ())
        {
            temp=entrenadores->seleccionar (k);
            k++;
        }
        datos[4]=temp.getNombre ()+" "
            +temp.getapellido ();
        datos[5]=temp.getNacionalidad ();
        lista[i]=datos;
    }
    cantidadRegistro=tempgrupo.getcantequipos ();
    return lista;
}

string **Controller::consultaListaJug(string consulta,int grupo, int equipo)
{
    Grupo grupotemp=grupos->seleccionar (grupo);
    Equipo equipotemp=grupotemp.getEquipo (equipo%4);
    string **lista=new string *[equipotemp.getCantJugadores ()];
    for (int i=0;i<equipotemp.getCantJugadores ();i++)
    {
        lista[i]=equipotemp.getJugador (i).obtenerregistro ();
    }
    cout<<cantidadRegistro<<endl;
    this->cantidadRegistro=equipotemp.getCantJugadores ();
    return lista;
}

//Simulaciones
void Controller::programarPartido (Fecha fechaInicio)
{
    int eq1,eq2,eq3,eq4,codgrupo=0, codestadio=0;
    this->partidos=new Lista<Partido>();
    for (int i=0;i<48;i++)
    {
        Partido partidoNuevo=*new Partido();
        Grupo grupotemp=grupos->seleccionar(codgrupo);
        if (i==15)
        {
            eq2=2;
            eq3=1;
            eq4=3;
            codgrupo=0;
        }
        if (i==32)
        {
            eq2=3;
            eq3=1;
            eq4=2;
            codgrupo=0;
        }
        if (i==0)
        {
            eq1=0;
            eq2=1;
            eq3=2;
            eq4=3;
            fechaInicio.modficarHora (13);
            partidoNuevo.asignarDatos (i+1,fechaInicio,
                grupotemp.getEquipo (eq1).getId (),
                grupotemp.getEquipo (eq2).getId (), estadios->seleccionar(codestadio).getId (),
                 (*new Resultado()));
            fechaInicio.agregar (0, 0, 0, 3, 0);
        }
        else if (i>=1 && i<25)
        {
            if (i%2==0)
            {
                partidoNuevo.asignarDatos (i+1,fechaInicio,
                grupotemp.getEquipo (eq1).getId (),
                grupotemp.getEquipo (eq2).getId (), estadios->seleccionar(codestadio).getId(),
                 (*new Resultado()));
                 fechaInicio.agregar (0, 0, 0, 3, 0);
            }
            else
            {
                partidoNuevo.asignarDatos (i+1,fechaInicio,
                grupotemp.getEquipo (eq3).getId (),
                grupotemp.getEquipo (eq4).getId (), estadios->seleccionar(codestadio).getId(),
                 (*new Resultado()));
                 fechaInicio.agregar (0, 0, 0, 3, 0);
                codgrupo++;
            }

            if ((i+1)%3==0)
            {
                fechaInicio.agregar (1, 0, 0, 0, 0);
                fechaInicio.modficarHora (13);
            }
        }
        else
        {
            if (i%2==0)
            {
                partidoNuevo.asignarDatos (i+1,fechaInicio,
                grupotemp.getEquipo (eq1).getId (),
                grupotemp.getEquipo (eq2).getId (), estadios->seleccionar(codestadio).getId(),
                 (*new Resultado()));
            }
            else
            {
                partidoNuevo.asignarDatos (i+1,fechaInicio,
                grupotemp.getEquipo (eq3).getId (),
                grupotemp.getEquipo (eq4).getId (), estadios->seleccionar(codestadio).getId(),
                 (*new Resultado()));
                codgrupo++;
            }
            if ((i+1)%4==2)fechaInicio.agregar (0, 0, 0, 3, 0);
            if ((i+1)%4==0)
            {
                fechaInicio.agregar (1, 0, 0, 0, 0);
                fechaInicio.modficarHora (13);
            }
        }
        codestadio++;
        if (codestadio==12)codestadio=0;
        partidos->insertarFin(partidoNuevo);
    }
}

//Sobrecarga para entrada automatica
void Controller::programarResultados (int fk)
{
    int sup1=0,sup2=0,pen1=0,pen2=0;
    int gol1=rand () % 7;
    int gol2=rand () % 7;
    int sanciones1=rand() %3;
    int sanciones2=rand() %3;
    Partido partidotemp=partidos->seleccionar (fk);
    Lista<Equipo> *equipos=listaTodosEquipo ();
    Equipo equipo1,equipo2;
    for(int i=0;i<equipos->cantidadElementos ();i++)
    {
        equipo1=equipos->seleccionar (i);
        if (equipo1.getId ()==partidotemp.getFkEq1 ())
        {
            i=equipos->cantidadElementos ();
        }
    }
    for (int i=0;i<equipos->cantidadElementos ();i++)
    {
        equipo2=equipos->seleccionar (i);
        if (equipo2.getId ()==partidotemp.getFkEq2 ())
        {
            i=equipos->cantidadElementos ();
        }
    }
    cout<<"equipo2: "<<equipo2.getNombre ()<<endl;
    int idgoljug;
    for (int i=0;i<gol1;i++)
    {
        idgoljug=rand() % equipo1.getCantJugadores();
        Goleadores nuevo=*new Goleadores();
        nuevo.dardatos (goleadores->cantidadElementos ()+1,
            equipo1.getJugador (idgoljug).getCed (),
            partidotemp.getId (), equipo1.getId (), 0);
        goleadores->insertarFin (nuevo);
    }
    for (int i=0;i<gol2;i++)
    {
        idgoljug=rand() % equipo2.getCantJugadores();
        Goleadores nuevo=*new Goleadores();
        nuevo.dardatos (goleadores->cantidadElementos ()+1,
            equipo2.getJugador (idgoljug).getCed (),
            partidotemp.getId (), equipo2.getId (), 0);
        goleadores->insertarFin (nuevo);
    }
    if (gol1 == gol2)
    {
        sup1= rand() % 5;
        sup2= rand() % 5;
        for (int i=0;i<sup1;i++)
        {
            idgoljug=rand() % equipo1.getCantJugadores();
            Goleadores nuevo=*new Goleadores();
            nuevo.dardatos (goleadores->cantidadElementos ()+1,
                equipo1.getJugador (idgoljug).getCed (),
                partidotemp.getId (), equipo1.getId (), 1);
            goleadores->insertarFin (nuevo);
        }
        for (int i=0;i<sup2;i++)
        {
            idgoljug=rand() % equipo2.getCantJugadores();
            Goleadores nuevo=*new Goleadores();
            nuevo.dardatos (goleadores->cantidadElementos ()+1,
                equipo2.getJugador (idgoljug).getCed (),
                partidotemp.getId (), equipo2.getId (), 1);
            goleadores->insertarFin (nuevo);
        }
        if (sup1 == sup2)
        {
            pen1=rand() %5;
            pen2=rand() %5;
            for (int i=0;i<pen1;i++)
            {
                idgoljug=rand() % equipo1.getCantJugadores();
                Goleadores nuevo=*new Goleadores();
                nuevo.dardatos (goleadores->cantidadElementos ()+1,
                    equipo1.getJugador (idgoljug).getCed (),
                    partidotemp.getId (), equipo1.getId (), 1);
                goleadores->insertarFin (nuevo);
            }
            for (int i=0;i<pen2;i++)
            {
                idgoljug=rand() % equipo2.getCantJugadores();
                Goleadores nuevo=*new Goleadores();
                nuevo.dardatos (goleadores->cantidadElementos ()+1,
                    equipo2.getJugador (idgoljug).getCed (),
                    partidotemp.getId (), equipo2.getId (), 1);
                goleadores->insertarFin (nuevo);
            }
            int val1=5,val2=5;
            while (pen1==pen2)
            {
                pen1+=rand() %1;
                if (pen1>val1)
                {
                    idgoljug=rand() % equipo1.getCantJugadores();
                    Goleadores nuevo=*new Goleadores();
                    nuevo.dardatos (goleadores->cantidadElementos ()+1,
                        equipo1.getJugador (idgoljug).getCed (),
                        partidotemp.getId (), equipo1.getId (), 1);
                    val1++;
                    goleadores->insertarFin (nuevo);
                }
                pen2+=rand() %1;
                if (pen2>val2)
                {
                    idgoljug=rand() % equipo2.getCantJugadores();
                    Goleadores nuevo=*new Goleadores();
                    nuevo.dardatos (goleadores->cantidadElementos ()+1,
                        equipo2.getJugador (idgoljug).getCed (),
                        partidotemp.getId (), equipo2.getId (), 1);
                    val2++;
                    goleadores->insertarFin (nuevo);
                }
            }
        }
    }
    programarResultados (gol1,gol2,sup1,sup2,pen1,pen2,fk+1);
    cout<<"Resultados Programados"<<endl;
    int sancion1,sancion2,codjug;
    sancion1=rand() % 3;
    sancion2=rand() % 3;
    for (int i=0;i<sancion1;i++)
    {
        codjug=rand() %11;
        modificarSancionesJugador (sancion1,codjug,fk,1);
    }
    for (int i=0;i<sancion2;i++)
    {
        codjug=rand() %11;
        modificarSancionesJugador (sancion2,codjug,fk,2);
    }
}

//sobrecarga para entrada manual
void Controller::programarResultados (int gol1,int gol2,int sup1,int sup2,int pen1,int pen2,int fk)
{
    Resultado nuevo=*new Resultado();
    nuevo.asignarDatos (fk,gol1,gol2,sup1,sup2,pen1,pen2,fk);
    Partido partidotemp=partidos->seleccionar (fk-1);
    partidotemp.darResultado (nuevo);
    partidos->modificar (fk-1,partidotemp);
}

string **Controller::consultaListapartido()
{
    string **listadatos=new string *[partidos->cantidadElementos ()];
    Lista<Equipo> *todosequipo=listaTodosEquipo ();
    for (int i=0;i<partidos->cantidadElementos ();i++)
    {
        string *datos=new string[3];
        for (int j=0;j<todosequipo->cantidadElementos ();j++)
        {
            if (todosequipo->seleccionar (j).getId ()==partidos->seleccionar (i).getFkEq1 ())
                datos[0]=todosequipo->seleccionar (j).getNombre ();
            if (todosequipo->seleccionar (j).getId ()==partidos->seleccionar (i).getFkEq2 ())
                datos[1]=todosequipo->seleccionar (j).getNombre ();
        }
        for (int j=0;j<estadios->cantidadElementos ();j++)
        {
            if (estadios->seleccionar (j).getId ()==partidos->seleccionar (i).getEstadio ())
                datos[2]=estadios->seleccionar (j).getNombre ();
        }
        listadatos[i]=datos;
    }
    return listadatos;
}

string **Controller::consultaJugadoresPartido(int cod,int equipo)
{
    string **lista;
    Lista<Equipo> *todosequipo=listaTodosEquipo ();
    for (int j=0;j<todosequipo->cantidadElementos ();j++)
    {
        if (equipo==1)
        {
            if (todosequipo->seleccionar (j).getId ()==partidos->seleccionar (cod).getFkEq1 ())
                lista=todosequipo->seleccionar (j).getListaJugadorTitular ();
        }
        else
        {
            if (todosequipo->seleccionar (j).getId ()==partidos->seleccionar (cod).getFkEq2 ())
                lista=todosequipo->seleccionar (j).getListaJugadorTitular ();
        }
    }
    return lista;
}

string **Controller::consultaPartidosconFecha(Fecha fechaevaluar)
{
    string **lista=new string *[4];
    Lista<Equipo> *todosequipo=listaTodosEquipo ();
    int k=0;
    for (int i=0;i<partidos->cantidadElementos ();i++)
    {
        if (partidos->seleccionar (i).getFecha().igualQue(fechaevaluar))
        {
            stringstream id,dia,mes,ano,hora;
            id<<partidos->seleccionar (i).getId ();
            dia<<partidos->seleccionar (i).getDia ();
            mes<<partidos->seleccionar (i).getMes ();
            ano<<partidos->seleccionar(i).getAno();
            hora<<partidos->seleccionar (i).getHora ();
            string *datos=new string[8];
            datos[0]=id.str();
            datos[4]=dia.str();
            datos[5]=mes.str ();
            datos[6]=ano.str();
            datos[7]=hora.str ();
            for (int j=0;j<todosequipo->cantidadElementos ();j++)
            {
                if (todosequipo->seleccionar (j).getId ()==partidos->seleccionar (i).getFkEq1 ())
                    datos[1]=todosequipo->seleccionar (j).getNombre ();
                if (todosequipo->seleccionar (j).getId ()==partidos->seleccionar (i).getFkEq2 ())
                    datos[2]=todosequipo->seleccionar (j).getNombre ();
            }
            for (int j=0;j<estadios->cantidadElementos ();j++)
            {
                if (estadios->seleccionar (j).getId ()==partidos->seleccionar (i).getEstadio ())
                    datos[3]=estadios->seleccionar (j).getNombre ();
            }
            lista[k]=datos;
            k++;
        }
    }
    this->cantidadRegistro=k;
    return lista;
}

string *Controller::consultaEntrenadordeEquipo(int grupo,int equipo)
{
    Grupo grupotemp=grupos->seleccionar (grupo);
    Equipo equipotemp=grupotemp.getEquipo (equipo);
    Entrenador entrenadortemp=entrenadores->seleccionar (equipotemp.getFk ()-1);
    return entrenadortemp.getdatos ();
}

string **Controller::consultaEstadiosTodos ()
{
    string **lista=new string *[estadios->cantidadElementos ()];
    for (int i=0;i<estadios->cantidadElementos ();i++)
    {
        lista[i]=estadios->seleccionar (i).getdatos ();
    }
    cantidadRegistro=estadios->cantidadElementos ();
    return lista;
}

string **Controller::consultaPartidosEstadio (int valor)
{
    string **lista=new string *[4];
    Lista<Equipo> *todosequipo=listaTodosEquipo ();
    int k=0;
    for (int i=0;i<partidos->cantidadElementos ();i++)
    {
        if (partidos->seleccionar (i).getEstadio () == estadios->seleccionar (valor).getId ())
        {
            stringstream id,dia,mes,ano,hora;
            id<<partidos->seleccionar (i).getId ();
            dia<<partidos->seleccionar (i).getDia ();
            mes<<partidos->seleccionar (i).getMes ();
            ano<<partidos->seleccionar(i).getAno();
            hora<<partidos->seleccionar (i).getHora ();
            string *datos=new string[8];
            datos[0]=id.str();
            datos[4]=dia.str();
            datos[5]=mes.str ();
            datos[6]=ano.str();
            datos[7]=hora.str ();
            for (int j=0;j<todosequipo->cantidadElementos ();j++)
            {
                if (todosequipo->seleccionar (j).getId ()==partidos->seleccionar (i).getFkEq1 ())
                    datos[1]=todosequipo->seleccionar (j).getNombre ();
                if (todosequipo->seleccionar (j).getId ()==partidos->seleccionar (i).getFkEq2 ())
                    datos[2]=todosequipo->seleccionar (j).getNombre ();
            }
            for (int j=0;j<estadios->cantidadElementos ();j++)
            {
                if (estadios->seleccionar (j).getId ()==partidos->seleccionar (i).getEstadio ())
                    datos[3]=estadios->seleccionar (j).getNombre ();
            }
            lista[k]=datos;
            k++;
        }
    }
    this->cantidadRegistro=k;
    return lista;
}

void Controller::modificarSancionesJugador (int numsanciones,int jug,int part,int equipo)
{
    Lista<Equipo> *equipos=listaTodosEquipo ();
    Partido partidotemp=partidos->seleccionar (part);
    Equipo equipotemp;
    int codgrupo;
    for (int i=0;i<equipos->cantidadElementos ();i++)
    {
        if (equipo==1)
        {
            if (partidotemp.getFkEq1 ()==equipos->seleccionar (i).getId ())
            {
                equipotemp=equipos->seleccionar (i);
                codgrupo=i;
            }
        }
        else
        {
            if (partidotemp.getFkEq2 ()==equipos->seleccionar (i).getId ())
            {
                equipotemp=equipos->seleccionar (i);
                codgrupo=i;
            }
        }
    }
    int k=0;
    Jugador jugadortemp;
    for (int i=0;i<equipotemp.getCantJugadores();i++)
    {
        if (k==jug)
        {
            jugadortemp=equipotemp.getJugador (i);
            jugadortemp.modificarNumSanciones (numsanciones);
            equipotemp.modificarJugador (jugadortemp, i);
            i=equipotemp.getCantJugadores ();
        }
        else
        {
            if (equipotemp.getJugador (i).getTitular ())
            {
                k++;
            }
        }
    }
    Grupo grupotemp=grupos->seleccionar (codgrupo/8);
    grupotemp.modificarEquipo (equipotemp, (codgrupo/8));
    grupos->modificar ((codgrupo/8), grupotemp);
}

void Controller::agregargoleadores (int jug,int part,int equipo,int tiempo)
{
    Lista<Equipo> *equipos=listaTodosEquipo ();
    Partido partidotemp=partidos->seleccionar (part);
    int codequipo;
    int codgrupo;
    for (int i=0;i<equipos->cantidadElementos ();i++)
    {
        if (equipo==1)
        {
            if (partidotemp.getFkEq1 ()==equipos->seleccionar (i).getId ())
            {
                codequipo=equipos->seleccionar (i).getId ();
                codgrupo=i;
            }
        }
        else
        {
            if (partidotemp.getFkEq2 ()==equipos->seleccionar (i).getId ())
            {
                codequipo=equipos->seleccionar (i).getId ();
                codgrupo=i;
            }
        }
    }
    int k=0;
    int idjug;
    for (int i=0;i<equipos->seleccionar(codgrupo).getCantJugadores();i++)
    {
        if (k==jug)
        {
            idjug=equipos->seleccionar(codgrupo).getJugador (i).getCed ();
            i=equipos->seleccionar(codgrupo).getCantJugadores ();
        }
        else
        {
            if (equipos->seleccionar(codgrupo).getJugador (i).getTitular ())
            {
                k++;
            }
        }
    }
    Goleadores nuevoGoleador=*new Goleadores();
    nuevoGoleador.dardatos (goleadores->cantidadElementos (), idjug, part,codequipo,tiempo);
    goleadores->insertarFin (nuevoGoleador);
}

string **Controller::consultaGoleadoresOrdenada ()
{
    string **listafinal;
    Lista<Goleadores> *goleadorestemp=goleadores;
    string **listaOrdenada=new string *[goleadores->cantidadElementos ()];
    Lista<Jugador> *listajug=listaTodosJUgador ();
    Lista<Equipo> *equipos=listaTodosEquipo ();
    int k=-1;
    int golesjug;
    for (int i=0;i<goleadorestemp->cantidadElementos ();i++)
    {
        string *dato=new string [4];
        Goleadores jugadorgoleador=goleadorestemp->seleccionar (i);
        golesjug=1;
        for(int j=0;j<listajug->cantidadElementos ();j++)
        {
            if (listajug->seleccionar (j).getCed ()==goleadorestemp->seleccionar (i).getFkJugador ())
            {
                dato[0]=listajug->seleccionar (j).getNombre ();cout<<dato[0]<<"  ";
                dato[1]=listajug->seleccionar (j).getApellido ();cout<<dato[1]<<endl;
            }
        }
        for(int j=0;j<equipos->cantidadElementos ();j++)
        {
            if (equipos->seleccionar (i).getId () ==goleadorestemp->seleccionar (i).getFkJugador ())
            {
                dato[3]=equipos->seleccionar (j).getNombre ();
            }
        }
        for (int j=i+1;j<goleadores->cantidadElementos ();j++)
        {
            if (jugadorgoleador.getid ()==goleadorestemp->seleccionar (j).getFkJugador ())
            {
                goleadorestemp->borrar (j);
                golesjug++;
            }
        }
        stringstream goles;
        goles<<golesjug;
        dato[2]=goles.str();
        k++;
        listaOrdenada[k]=dato;
    }
    // listafinal=new string *[k];
    // string *aux;
    // for (int i=0;i<k;i++)
    // {
    //     aux=listaOrdenada[i];
    //     for (int j=i+1;j<k;j++)
    //     {
    //         if (aux[i][2]>listaOrdenada[j][2])
    //         {}
    //     }
    // }
    cantidadRegistro=k+1;
    return listaOrdenada;
}

string **Controller::consultaJugadoresSancionados()
{
    string **lista=new string *[704];
    Lista<Equipo> *todosequipo=listaTodosEquipo ();
    int k=0;
    for (int i=0;i<partidos->cantidadElementos ();i++)
    {
        Equipo eqtemp;
        for (int j=0;j<todosequipo->cantidadElementos ();j++)
        {
            if (todosequipo->seleccionar (j).getId ()==partidos->seleccionar (i).getFkEq1 ())
            {
                eqtemp=todosequipo->seleccionar (j);
            }
        }
        for(int j=0;j<eqtemp.getCantJugadores ();j++)
        {
            if (eqtemp.getJugador (j).getFechaSancion ()>0)
            {
                lista[k]=eqtemp.getJugador (j).obtenerregistro ();
                k++;
            }
        }
        //eq2
        for (int j=0;j<todosequipo->cantidadElementos ();j++)
        {
            if (todosequipo->seleccionar (j).getId ()==partidos->seleccionar (i).getFkEq2 ())
            {
                eqtemp=todosequipo->seleccionar (j);
            }
        }
        for(int j=0;j<eqtemp.getCantJugadores ();j++)
        {
            if (eqtemp.getJugador (j).getFechaSancion ()>0)
            {
                lista[k]=eqtemp.getJugador (j).obtenerregistro ();
                k++;
            }
        }
    }
    cantidadRegistro=k;
    return lista;
}

string *Controller::consultaResultadosdePartidos (int partido)
{
    Partido partidotemp=partidos->seleccionar (partido);
    Resultado res=partidotemp.getResultado ();
    return res.getdatos ();
}

void Controller::guardarPartido ()
{
    string **listadatos=new string *[partidos->cantidadElementos ()];
    for (int i=0;i<partidos->cantidadElementos ();i++)
    {
        listadatos[i]=partidos->seleccionar (i).getdatos ();
    }
    db->insertAll (partidos->seleccionar (0).getTabla(), listadatos,partidos->cantidadElementos () , 7);
}

void Controller::guardarResultado ()
{
    string **listadatos=new string *[partidos->cantidadElementos ()];
    for (int i=0;i<partidos->cantidadElementos ();i++)
    {
        listadatos[i]=partidos->seleccionar (i).getResultado ().getdatos ();
    }
    db->insertAll (partidos->seleccionar(0).getResultado ().getTabla(), listadatos, partidos->cantidadElementos (), 8);
}

void Controller::guardarGoleadores ()
{
    string **listadatos=new string *[goleadores->cantidadElementos ()];
    for (int i=0;i<goleadores->cantidadElementos ();i++)
    {
        listadatos[i]=goleadores->seleccionar (i).getdatos ();
    }
    db->insertAll (goleadores->seleccionar (0).getTabla (), listadatos, goleadores->cantidadElementos (), 5);
}

string **Controller::goleadoresconciertacantidad (int goles){}
// {
//     string **listadatos=new string *[goleadores->cantidadElementos ()];
//     int **listagoleadoresgol=new int *[goleadores->cantidadElementos ()];
//     int posguardada=0;//la ultima posicion que guardo en el arreglo
//     for (int i=0;i<goleadores->cantidadElementos ();i++)
//     {
//         int *datos=new int[2];
//         datos[1]=0;
//         listagoleadoresgol[i]=datos;
//     }
//     for (int i=0;i<goleadores->cantidadElementos ();i++)
//     {
//         if (listagoleadoresgol[i][0]==goleadores->seleccionar (i).getFkJugador ())
//         {
//         for (int j=0;j<posguardada;j++)//guardo los goles
//         {
//             cout<<listagoleadoresgol[i][0]<<"=="<<goleadores->seleccionar (i).getFkJugador ()<<endl;
//             {
//                 listagoleadoresgol[i][1]++;
//             }
//             else
//             {
//                 listagoleadoresgol[posguardada][0]=goleadores->seleccionar (i).getFkJugador ();
//                 listagoleadoresgol[posguardada][1]++;
//                 posguardada++;
//             }
//         }
//     }
//     for (int i=0;i<posguardada;i++)
//     {
//         cout<<"FK: "<<listagoleadoresgol[i][0];
//         cout<<" "<<" Goles: "<<listagoleadoresgol[i][1]<<endl;
//     }
// }

int Controller::getCantidadRegistro (){return this->cantidadRegistro;}
int Controller::getCantPartidos (){return this->partidos->cantidadElementos ();}

string **Controller::getListaEquiposTodos()
{
    Equipo tempEquipo;
    return db->obtenerTodo (tempEquipo.getTabla ());
}
#endif
