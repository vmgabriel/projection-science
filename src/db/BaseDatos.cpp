#include <stdio.h>

#include <iostream>
#include <string.h>
#include <ctype.h>
#include <iomanip>

#include "../lib/Lista.cpp"

using namespace std;

#ifndef BASEDATOS
#define BASEDATOS

class BaseDatos
{
        private:
                string ruta;

        public:
                BaseDatos();
                ~BaseDatos();

                //Para Obtencion de Datos
                //Caracter ; como caracter especial
                string **obtenerTodo(string tabla);
                int cantidadRegistros(string tabla);
                int cantidadRegistrosConDato(string tabla,string dato, int posi);
                int cantidadDatos(string tabla);
                string *obtenerRegistroCod(string tabla, string cod,int posi);
                string **obtenerRegistrosDato(string tabla, string dato,int posi);
                string obtenerDatoEspecifico(string tabla,string codigo,int posc,int posd);
                int obtenerUlltimoCodigo(string tabla);

                //Para Insercion
                bool insertRegistroNuevo(string tabla, string datos);

                //Para Insercion de todas
                bool insertAll(string tabla, string **datos, int numreg, int numdato);
};

BaseDatos::BaseDatos(){ruta="../src/db/";}

 int BaseDatos::cantidadDatos(string tabla)
{
        int datos=0;
        FILE *archivo;
        string pos=ruta+tabla;
        archivo=fopen(pos.c_str(),"r");
        if (archivo == NULL)
        {
                cout<<"Error en la apertura del archivo"<<endl;
        }
        else
        {
                char caracter;
                bool bandera=true;
                while (bandera)
                {
                        caracter = fgetc(archivo);
                        if (caracter == ';')
                        {
                                datos++;
                        }
                        if (caracter == '\n')
                        {
                                bandera=false;
                        }
                }
        }
        fclose(archivo);
        return datos;
}

 int BaseDatos::cantidadRegistros(string tabla)
{
        int lineas=0;
        FILE *archivo;
        char caracter;
        string pos=ruta+tabla;
        archivo=fopen(pos.c_str(),"r");
        if (archivo == NULL)
        {
                printf("Error de apertura del archivo. \n");
        }
        else
        {
                while (feof(archivo) == 0)
                {
                        caracter = fgetc(archivo);
                        if (caracter == '\n')
                        {
                                lineas++;
                        }
                }
        }
        fclose(archivo);

        return lineas;
}

string **BaseDatos::obtenerTodo(string tabla)
{
        FILE *archivo;
        string **tabladatos=new string *[cantidadRegistros (tabla)];
        string *tablafilas;
        string pos=ruta+tabla;
        archivo=fopen(pos.c_str(),"r");
        if (archivo == NULL)
        {
                cout<<"Error en la apertura del archivo"<<endl;
        }
        else
        {
                char caracter;
                string palabra;
                tablafilas=new string[cantidadDatos(tabla)];
                int posx=0;
                int posy=0;
                while (feof(archivo) == 0)
                {
                        caracter=fgetc(archivo);
                        if (caracter == ';')
                        {
                                tablafilas[posx]=palabra;
                                posx++;
                                palabra="";
                        }
                        else if (caracter == '\n')
                        {
                                tabladatos[posy]=tablafilas;
                                tablafilas=new string[cantidadDatos(tabla)];
                                posx=0;
                                posy++;
                        }
                        else
                        {
                                palabra=palabra+caracter;
                        }
                }
        }
        fclose(archivo);
        return tabladatos;
}

/*
 * Obtener registro retorna solo una linea del registro con las condiciones que en la
 * posicion posi (posi es el numero del dato de la tabla), con el codigo cod en esa posicion
 * <NO CONFUNDIR CON UN RETORNADOR TIPO SELECT(EN SQL)>
 * <Codigo en sql> SELECT FROM TABLA WHERE POSI==COD; RETORNARA CON COD
 */

string *BaseDatos::obtenerRegistroCod (string tabla,string cod,int posi=0)
{
        string **info =obtenerTodo (tabla);
        string *datos;

        for(int i=0;i<cantidadRegistros (tabla);i++)
        {
                if (info[i][posi] == cod)
                {
                        datos=info[i];
                }
        }

        return datos;
}

/*
 * Returnara lista de datos donde dato estara en dicha posicion
 */
string **BaseDatos::obtenerRegistrosDato(string tabla, string dato,int posi)
{
        FILE *archivo;
        string **tabladatos=new string *[cantidadRegistrosConDato (tabla, dato, posi)];
        string *tablafilas;
        string pos=ruta+tabla;
        archivo=fopen(pos.c_str(),"r");
        if (archivo == NULL)
        {
                cout<<"Error en la apertura del archivo"<<endl;
        }
        else
        {
                char caracter;
                string palabra;
                tablafilas=new string[cantidadDatos(tabla)];
                int posx=0;
                int posy=0;
                while (feof(archivo) == 0)
                {
                        caracter=fgetc(archivo);
                        if (caracter == ';')
                        {
                                tablafilas[posx]=palabra;
                                posx++;
                                palabra="";
                        }
                        else if (caracter == '\n')
                        {
                                if (tablafilas[posi] == dato)
                                {
                                        tabladatos[posy]=tablafilas;
                                        posy++;
                                }
                                tablafilas=new string[cantidadDatos(tabla)];
                                posx=0;
                        }
                        else
                        {
                                palabra=palabra+caracter;
                        }
                }
        }
        fclose(archivo);
        return tabladatos;
}

int BaseDatos::cantidadRegistrosConDato(string tabla,string dato, int posi)
{
        int datos=0;
        FILE *archivo;
        string *tablafilas;
        string pos=ruta+tabla;
        archivo=fopen(pos.c_str(),"r");
        if (archivo == NULL)
        {
                cout<<"Error en la apertura del archivo"<<endl;
        }
        else
        {
                char caracter;
                string palabra;
                tablafilas=new string[cantidadDatos(tabla)];
                int posx=0;
                int posy=0;
                while (feof(archivo) == 0)
                {
                        caracter=fgetc(archivo);
                        if (caracter == ';')
                        {
                                tablafilas[posx]=palabra;
                                posx++;
                                palabra="";
                        }
                        else if (caracter == '\n')
                        {
                                if (tablafilas[posi]==dato)
                                {
                                        datos++;
                                }
                                tablafilas=new string[cantidadDatos(tabla)];
                                posx=0;
                                posy++;
                        }
                        else
                        {
                                palabra=palabra+caracter;
                        }
                }
        }
        fclose(archivo);
        return datos;
}

string BaseDatos::obtenerDatoEspecifico(string tabla,string codigo,int posc,int posd)
{
        string sock;
        FILE *archivo;
        string pos=ruta+tabla;
        archivo=fopen(pos.c_str(),"r");
        if (archivo == NULL)
        {
                cout<<"Error en la apertura del archivo"<<endl;
        }
        else
        {
                char caracter;
                string palabra;
                string *tablafilas=new string[cantidadDatos(tabla)];
                int posx=0;
                while (feof(archivo) == 0)
                {
                        caracter=fgetc(archivo);
                        if (caracter == ';')
                        {
                                tablafilas[posx]=palabra;
                                posx++;
                                palabra="";
                        }
                        else if (caracter == '\n')
                        {
                                if (tablafilas[posc] == codigo)
                                {
                                        sock=tablafilas[posd];
                                }
                                tablafilas=new string[cantidadDatos(tabla)];
                                posx=0;
                        }
                        else
                        {
                                palabra=palabra+caracter;
                        }
                }
        }
        fclose(archivo);
        return sock;
}

int BaseDatos::obtenerUlltimoCodigo(string tabla)
{
        int valor;
        FILE *archivo;
        string pos=ruta+tabla;
        archivo=fopen(pos.c_str(),"r");
        if (archivo == NULL)
        {
                cout<<"Error en la apertura del archivo"<<endl;
        }
        else
        {
                char caracter;
                string palabra;
                int posy=0;
                int posx=0;
                string *tablafilas=new string[cantidadDatos(tabla)];
                while (feof(archivo) == 0)
                {
                        caracter=fgetc(archivo);
                        if (caracter == ';')
                        {
                                tablafilas[posx]=palabra;
                                posx++;
                                palabra="";
                        }
                        else if (caracter == '\n')
                        {
                                posy++;
                                if (cantidadRegistros (tabla) == posy)
                                {
                                        valor=atoi(tablafilas[0].c_str());//No hay tal error
                                }
                                posx=0;
                        }
                        else
                        {
                                palabra=palabra+caracter;
                        }
                }
        }
        valor++;
        fclose(archivo);
        return valor;
}

bool BaseDatos::insertRegistroNuevo(string tabla, string datos)
{
        bool val=false;
        FILE *archivo;
        string pos=ruta+tabla;
        archivo=fopen(pos.c_str(),"a+");
        if (archivo == NULL)
        {
                cout<<"Error en la apertura del archivo"<<endl;
        }
        else
        {
                fprintf(archivo,datos.c_str());
                val=true;
        }
        fclose(archivo);
        return val;
}

/*
 * Maximo cuidado con este metodo
 * */
bool BaseDatos::insertAll(string tabla, string **datos, int numreg, int numdato)
{
        bool val=false;
        FILE *archivo;
        string pos=ruta+tabla;

        archivo=fopen(pos.c_str(),"w"); //Se Vuelve a Crear el archivo

        string palabra="";
        for(int i=0;i<numreg;i++)
        {
                palabra="";
                for(int j=0;j<numdato;j++)
                {
                        palabra=datos[i][j]+";";
                        fputs(palabra.c_str(),archivo);
                }
                fputc('\n',archivo);
        }
        fclose(archivo);

        if (cantidadRegistros(tabla) > 0)
        {
                val=true;
        }
        return val;
}
#endif
