// Hecho Por: Gabriel Vargas Monroy
#include <iostream>
#include<queue>

using namespace std;

#ifndef ARBOL
#define ARBOL

struct Nodo
{
	int elemento;
	int id;
	Nodo *izq;
	Nodo *der;
};

class ArbolBinario
{
    private:
        Nodo *agregariter(Nodo*, int,int);
        int eliminarder(Nodo *);
        Nodo *buscar(Nodo *,int);
	protected:
		Nodo *raiz;
		bool eshoja(Nodo *);

	public:
		ArbolBinario();
		Nodo *getRaiz();
		void setRaiz(Nodo *);
		bool eliminar(int);
		int profundidad(Nodo *);
		Nodo *agregar(int,int);
		Nodo *mostrarPreorden(Nodo *);
		Nodo *mostrarInorden(Nodo *);
		Nodo *mostrarPosorden(Nodo *);
		void Inorden();
		void Postorden();
		void Niveles();
		int cantidadNodos(Nodo *);
		int cantidadHojas(Nodo *);
		Nodo *buscar(int);
		char menu();
		char menumostrar();
		bool completo(Nodo *);
};

//constructor
ArbolBinario::ArbolBinario(){raiz=NULL;}

Nodo *ArbolBinario::getRaiz(){return raiz;}

void ArbolBinario::setRaiz(Nodo *raiz){this->raiz=raiz;}

Nodo *ArbolBinario::agregariter(Nodo *raiz, int elemento,int id)
{
	Nodo *p;
	if (raiz)
	{
		if (profundidad(raiz->izq)<profundidad(raiz->der))
		    raiz->izq=agregariter(raiz->izq,elemento,id);
		else raiz->der=agregariter(raiz->der,elemento,id);
	}
	else
	{
		p= new Nodo;
		raiz=p;
		raiz->elemento=elemento;
		raiz->id=id;
		raiz->izq=raiz->der=NULL;
	}
	return raiz;
}

Nodo *ArbolBinario::agregar(int elem,int id){return agregariter (this->raiz,elem,id);}

int ArbolBinario::eliminarder(Nodo *raiz)
{
	if(raiz)
	{
		if(raiz->izq||raiz->der)
		{
			if(profundidad(raiz->izq)>profundidad(raiz->der))
			    eliminarder(raiz->izq);
			else eliminarder(raiz->der);
		}
		else
		{
			int a=raiz->elemento;
			delete(raiz);
			return a;
		}
	}
	else return 0;
}

bool ArbolBinario::eliminar(int val){return eliminarder (this->raiz) != 0;}

Nodo *ArbolBinario::buscar(int abuscar){return buscar (this->raiz,abuscar);}

int ArbolBinario::profundidad(Nodo *raiz)
{
	int profizq,profder;
	if(raiz)
	{
		profizq=profundidad(raiz->izq);
		profder=profundidad(raiz->der);
		if(profizq>profder) return profizq+1;
		else return profder+1;
	}
	else return 0;
}

bool ArbolBinario::completo (Nodo * arbol)
{
    if (!arbol){return true;}
    if (arbol->der && arbol->izq)
    {
        return (profundidad (arbol->der)-profundidad (arbol->izq) == 0 ||
            profundidad (arbol->der)-profundidad (arbol->izq) == 2 ||
            profundidad (arbol->der)-profundidad(arbol->izq)==-2) &&
            completo (arbol->der) && completo (arbol->izq);
    }
    if (arbol->der && !arbol->izq)
    {
        return (profundidad (arbol->der)-profundidad (arbol->izq) == 0 ||
            profundidad (arbol->der)-profundidad (arbol->izq) == 2 ||
            profundidad (arbol->der)-profundidad(arbol->izq)==-2) &&
            completo (arbol->der);
    }
    if (arbol->der && !arbol->izq)
    {
        return (profundidad (arbol->der)-profundidad (arbol->izq) == 0 ||
            profundidad (arbol->der)-profundidad (arbol->izq) == 2 ||
            profundidad (arbol->der)-profundidad(arbol->izq)==-2) &&
            completo (arbol->izq);
    }
}

Nodo *ArbolBinario::mostrarPreorden(Nodo *raiz)
{
	if(raiz)
	{
		cout<<raiz->elemento<<" ";
		mostrarPreorden(raiz->izq);
		mostrarPreorden(raiz->der);
	}
	else return NULL;
}

Nodo *ArbolBinario::mostrarInorden(Nodo *raiz)
{
	if(raiz)
	{
		mostrarInorden(raiz->izq);
		cout<<raiz->elemento<<" ";
		mostrarInorden(raiz->der);
	}
	else return NULL;
}

Nodo *ArbolBinario::mostrarPosorden(Nodo *raiz)
{
	if(raiz)
	{
		mostrarPosorden(raiz->izq);
		mostrarPosorden(raiz->der);
		cout<<raiz->elemento<<" ";
	}
	else return NULL;
}

Nodo *ArbolBinario::buscar(Nodo *raiz,int abuscar)
{
	if(raiz)
	{
		if(raiz->elemento==abuscar) return (raiz);
		else
		{
			buscar(raiz->izq, abuscar);
			buscar(raiz->der, abuscar);
		}
	}
	else return NULL;
}

void ArbolBinario::Niveles()
{
	if(raiz)
	{
		queue<Nodo *> q;
		q.push(raiz);
		while(!q.empty())
		{
			Nodo*nodo = q.front();
			cout<< nodo->elemento <<" ";
			q.pop();
			if (nodo->izq!=NULL) q.push(nodo->izq);
			if (nodo->der!=NULL) q.push(nodo->der);
		}
	}
}

bool ArbolBinario::eshoja(Nodo * arbol){return arbol->izq && arbol->der;}

int ArbolBinario::cantidadNodos(Nodo *arbol)
{
    if (!arbol) return 0;
    return 1+cantidadNodos (arbol->izq)+cantidadNodos(arbol->der);
}

int ArbolBinario::cantidadHojas(Nodo *arbol)
{
    if (!arbol) return 0;
    if (!arbol->izq && !arbol->der) return 1;
    return cantidadHojas (arbol->der)+cantidadHojas (arbol->izq);
}

//Arbol binario ordenado que hereda del binario normal

class ArbolBinarioOrdenado: public ArbolBinario
{
	public:
		ArbolBinarioOrdenado();
		Nodo *agregar(int);
		Nodo *buscar(int);
		bool eliminar(int);
};

ArbolBinarioOrdenado::ArbolBinarioOrdenado(){raiz=NULL;}

Nodo *ArbolBinarioOrdenado::agregar(int elemento)
{
	Nodo *R=raiz, *s;
	while(R)
	{
		s=R;
		if(elemento<R->elemento) R=R->izq;
		else R=R->der;
	}
	R=new Nodo;
	R->elemento=elemento;
	R->der=R->izq=NULL;
	if(raiz)
	{
		if(elemento < s->elemento) s->izq=R;
		else s->der=R;
		return raiz;
	}
	raiz=R;
}

Nodo *ArbolBinarioOrdenado::buscar (int val)
{
    Nodo *arbol=this->raiz;
    while(!arbol)
    {
        if (arbol->elemento == val)return arbol;
        else if (arbol->elemento > val)arbol=arbol->der;
        else arbol=arbol->izq;
    }
}

bool ArbolBinarioOrdenado::eliminar (int val)
{
    Nodo *nodo=this->raiz,*padre=NULL;
    while (nodo && nodo->elemento != val)
    {
        padre=nodo;
        if (nodo->elemento > val)nodo=nodo->der;
        else nodo=nodo->izq;
    }
    if (!nodo) return true;
    else
    {
        if (eshoja (nodo))
        {
            if (padre->der == nodo) padre->der=NULL;
            else padre->izq=NULL;
            delete nodo;
            return true;
        }
        Nodo *reemp=nodo->der,*padrereemp;
        if (nodo->der)
        {
            while (reemp->izq){padrereemp=reemp;reemp=reemp->izq;}
            padrereemp->izq=reemp->der;
            reemp->izq=nodo->izq;
            reemp->der=nodo->der;
        }
        else
        {
            while (reemp->der){padrereemp=reemp;reemp=reemp->der;}
            padrereemp->der=reemp->izq;
            reemp->izq=nodo->izq;
            reemp->der=nodo->der;
        }
        if (padre->der == nodo) padre->der=reemp;
        else padre->izq=reemp;
        delete nodo;
        return true;
    }
    return false;
}

class AVL: public ArbolBinarioOrdenado
{
    private:
        Nodo *actualizar_altura(Nodo *, Nodo *);
        Nodo *rotacionSimple(Nodo *, bool);
        Nodo *rotacionDoble(Nodo*,bool);
        Nodo *balancear(Nodo*);
        Nodo *agregarrec(Nodo*, int);
        Nodo *eliminarrec(Nodo*, int);
        int eliminarmin(Nodo *);
	public:
		AVL();
		Nodo *agregar(int);
		bool eliminar(int);
};

AVL::AVL(){this->raiz=NULL;}

Nodo *AVL::rotacionSimple(Nodo * abuelo, bool izq)
{
    Nodo *padre;
    if (izq)
    {
        padre=abuelo->izq;
        abuelo->izq=padre->der;
        padre->der=abuelo;
    }
    else
    {
        padre=abuelo->der;
        abuelo->der=padre->izq;
        padre->izq=abuelo;
    }
    return padre;
}
Nodo *AVL::rotacionDoble(Nodo *abuelo,bool izq)
{
    if (izq)
    {
        rotacionSimple (abuelo->izq,false);
        rotacionSimple (abuelo, true);
    }
    else
    {
        rotacionSimple (abuelo->der, true);
        rotacionSimple (abuelo, false);
    }
}

Nodo *AVL::balancear(Nodo *arbol)
{
    if (arbol)
    {
        if (profundidad (arbol->izq)-profundidad (arbol->der) == 2)
        {
            if (profundidad (arbol->izq->izq)>=profundidad (arbol->izq->der))
                rotacionSimple(arbol,true);
            else rotacionDoble (arbol, true);
        }
        else if (profundidad (arbol->der)-profundidad (arbol->izq) == 2)
        {
            if (profundidad (arbol->der->der) >= profundidad (arbol->der->izq))
                rotacionSimple (arbol, false);
            else rotacionDoble (arbol, false);
        }
    }
    return arbol;
}

Nodo *AVL::agregarrec (Nodo *arbol,int num)
{
    Nodo *nuevo;
    nuevo->izq=nuevo->der=NULL;
    nuevo->elemento=num;
    if (!arbol)arbol=nuevo;
    else
    {
        if (arbol->elemento < num) arbol->izq=agregarrec(arbol->izq,num);
        else arbol->der=agregarrec(arbol->der,num);
        balancear (arbol);
    }
    return arbol;
}

Nodo *AVL::agregar (int num){return agregarrec(this->raiz,num);}

Nodo *AVL::eliminarrec (Nodo *arbol,int num)
{
    Nodo *aux;
    if (num<arbol->elemento){arbol->izq=eliminarrec (arbol->izq, num);}
    else if (num>arbol->elemento){arbol->der=eliminarrec (arbol->der, num);}
    else
    {
        if (!arbol->izq && !arbol->der)
        {
            delete arbol;
            return NULL;
        }
        else if (!arbol->izq)
        {
            aux=arbol;
            arbol=arbol->izq;
            delete aux;
        }
        else
        {
            arbol->elemento=eliminarmin (arbol->der);
        }
    }
    balancear (arbol);
    return arbol;
}

int AVL::eliminarmin (Nodo *arbol)
{
    if (!arbol)
    {
        cout<<"ERROR!!!"<<endl;
    }
    else
    {
        if (arbol->izq)
        {
            int x=eliminarmin (arbol->izq);
            balancear (arbol);
            return x;
        }
        else
        {
            Nodo *aux=arbol;
            int x=arbol->elemento;
            arbol=arbol->der;
            delete aux;
            balancear (arbol);
            return x;
        }
    }
}

bool AVL::eliminar(int num)
{
    this->raiz=eliminarrec(this->raiz,num);
    return true;
}

#endif
