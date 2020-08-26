#include <stdio.h>
#include <iostream>

#ifndef LISTA
#define LISTA

template<typename T>
struct Nodo
{
    T info;
    Nodo<T> *sig, *ant;
};

template<typename T>
class Lista
{
    private:
        Nodo<T> *cab;

    public:
        //Constructor y Destructor
        Lista();

        //~Lista();

        //Metodos
        //Se usa cuando se genera la sobrecarga de constructores
        void primerElemento(T dato);
        void insertarFin(T dato);
        void insertarPos(T dato, int pos);
        bool modificar(int pos, T dato);
        int cantidadElementos();
        bool borrar(int pos);
        T seleccionar(int pos);
};

template<typename T>
Lista<T>::Lista()
{
    cab=new Nodo<T>;
    cab->ant=NULL;
	cab->sig=cab;
}

template<typename T>
void Lista<T>::primerElemento(T dato)
{
    Nodo<T> *temp;
	temp=new Nodo<T>;

	temp->info=dato;
	temp->ant=cab;
	temp->sig=cab;

	cab->ant=temp;
	cab->sig=temp;
}

template<typename T>
void Lista<T>::insertarFin(T dato)
{
    if (this->cantidadElementos() == 0){this->primerElemento(dato);}
    else
    {
		Nodo<T> *temp, *aux, *caja;
		temp=new Nodo<T>;
		temp->info=dato;
		aux=cab->sig;
		caja=cab;
		while(aux != cab)
		{
		    aux=aux->sig;
		    caja=caja->sig;
		}
		temp->ant=caja;
		temp->sig=cab;
		cab->ant=temp;
		caja->sig=temp;
    }
}

template<typename T>
void Lista<T>::insertarPos(T dato, int pos)
{
	Nodo<T> *aux, *temp;
	aux=cab;
	for (int i=0;i<pos;i++){aux=aux->sig;}
	temp=new Nodo<T>;
	temp->info=dato;
	temp->ant=aux->ant;
	temp->sig=aux;
	(aux->ant)->sig=temp;
	aux->ant=temp;
}

template<typename T>
bool Lista<T>::modificar(int pos, T dato)
{
	bool elem=false;
	if ((pos>=0) && (pos < this->cantidadElementos()))
	{
		T temp;
		Nodo<T> *aux, *cont;
		aux=cab->sig;
		for (int i=0;i<pos;i++){aux=aux->sig;}
		cont=new Nodo<T>;
		cont->info=dato;
		cont->ant=aux->ant;
		cont->sig=aux->sig;
		(aux->ant)->sig=cont;
		(aux->sig)->ant=cont;
		elem=true;
	}
	return elem;
}

template<typename T>
int Lista<T>::cantidadElementos()
{
    int cant=0;
    Nodo<T> *aux;
	aux=cab->sig;
	while(aux != cab)
	{
	    aux=aux->sig;
		cant++;
	}
	return cant;
}

template<typename T>
bool Lista<T>::borrar(int pos)
{
	bool elem=false;
	if ((pos >= 0) && (pos < cantidadElementos()))
	{
		int n = cantidadElementos();
		Nodo<T> *aux;
		aux=cab;
		for (int i=0;i<pos;i++)
		{aux=aux->sig;}
		(aux->ant)->sig=aux->sig;
		(aux->sig)->ant=aux->ant;
		if (cantidadElementos() != n){elem=true;}
	}
	return elem;
}

template<typename T>
T Lista<T>::seleccionar(int pos)
{
	T dato;
	if ((pos >= 0) && (pos < cantidadElementos()))
	{
	    int i=0;
	    Nodo<T> *aux=cab->sig;
	    while ((i<pos) && (aux != cab))
	    {
	        aux=aux->sig;
	        i++;
	    }
	    dato=aux->info;
	}
	return dato;
}
#endif
