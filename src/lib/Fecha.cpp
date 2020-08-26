#include <stdio.h>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

#ifndef FECHA
#define FECHA

class Fecha
{
    private:
        int dia,mes,ano,hora,minuto;
	    string diasem;

	public:
	    bool poner(int d,int me, int a, int h, int mi);
        void ponerIntervalo(string ds, int h, int m);
        void ponerfechaact();
        bool mayorQue(Fecha *comp);
        bool menorQue(Fecha *comp);
        bool igualQue(Fecha comp);
        void agregar(int d, int me, int a, int h, int mi);
        void quitar(int d, int me, int a, int h, int mi);
        void modficarHora(int);
        string imprimir();
        string obtenerDiaOfSemana(int d, int m, int a);
        int zeller(int y, int m, int d);

        //Gets
		int getdia(){return dia;}
		int getmes(){return mes;}
		int getano(){return ano;}
		int gethora(){return hora;}
		int getminuto(){return minuto;}
};

 /*-----
  * * pone y modifca la fecha
  * * d=dia (depende del mes)
  * * me=mes (entre 1 y 12)
  * * a=año (debe estar entre 0 y ...)
  * * h=hora(debe estar entre 0 y 24)
  * * mi=minuto(debe estar entre 0 y 59)
  * * retorna booleano que asegura que la fecha y hora sea correcta
  * * ----
  * * */
bool Fecha::poner(int d,int me, int a, int h, int mi)
{
	bool res=true;
	if ((d<=31) && (d>0) && (me<=12) && (me>0) && (a>0) &&
            (h>=0) && (h<=23) && (mi>=0) && (mi<60))
	{
		if (me == 2){if (d>29){res=false;}}
		else if ((me == 4) || (me == 6 ) || (me == 9) || (me == 11)){if (d>30){res=false;}}
                if (res)
		{
            diasem=obtenerDiaOfSemana(d,me,a);
			dia=d;
			mes=me;
			ano=a;
			hora=h;
			minuto=mi;
		}
	}
	return res;
}

/*
* pone en una fecha un intervalo de tiempo
* ds=dia de la semana
* */
void Fecha::ponerIntervalo(string ds, int h, int m)
{
	dia=0;
	mes=0;
	ano=0;
	hora=h;
	minuto=m;
    diasem=ds;
}

/*
 * la fecha del sistema actual
* */
void Fecha::ponerfechaact()
{
	time_t fecha_sistema;
	time(&fecha_sistema);
	struct tm *tiempo;
	tiempo=localtime(&fecha_sistema);
	dia=tiempo->tm_mday;
	mes=tiempo->tm_mon + 1;
	ano=tiempo->tm_year + 1900;
	hora=0;
	minuto=0;
	diasem=obtenerDiaOfSemana(dia,mes,ano);
}

/*
* compara entre dos fechas esta y otra
* returna verdadero si es mayor, no en caso contrario
* */
bool Fecha::mayorQue(Fecha *comp)
{
	bool res=false;

	if (ano > comp->getano()){res=true;}
	else if(mes > comp->getmes()){res=true;}
	else if(dia > comp->getdia()){res=true;}
	else if(hora > comp->gethora()){res=true;}
	else if (minuto > comp->getminuto()){res=true;}

	return res;
}

/*
 * compara entre dos fechas esta y otra
 * returna verdadero si es menor, no en caso contrario
* */
bool Fecha::menorQue(Fecha *comp)
{
	bool res=false;

	if (ano < comp->getano()){res=true;}
	else if(mes < comp->getmes()){res=true;}
	else if(dia < comp->getdia()){res=true;}
	else if(hora < comp->gethora()){res=true;}
	else if (minuto < comp->getminuto()){res=true;}

	return res;
}

/*
* compara entre dos fechas esta y otra
* returna verdadero si es igual, no en caso contrario
* */
bool Fecha::igualQue(Fecha comp)
{
	bool res=false;
	if ((ano == comp.getano()) && (mes == comp.getmes())
            && (dia == comp.getdia())){res=true;}
    return res;
}

/*
* agrega o quita tiempo sea en dias, meses, años...
* no posee retorno, modifica la fecha actual
* */
void Fecha::agregar(int d, int me, int a, int h, int mi)
{
	int temp=mi+minuto;
	if (temp >59)
	{
		hora=hora+1;
		minuto=temp-60;
	}
	else
	{
		minuto=temp;
	}
	temp=h+hora;
	if (temp > 23)
	{
		dia=dia+1;
		hora=temp-24;
	}
	else
	{
                hora=temp;
	}
	temp=d+dia;
	if (mes == 2)
	{
		if (temp > 29)
		{
		    mes=mes+1;
			dia=temp-28;
		}
		else
		{
			dia=temp;
		}
	}
	else if ((me == 4) || (me == 6 ) || (me == 9) || (me == 11))
	{
		if (temp > 30)
		{
			mes=mes+1;
			dia=temp-29;
		}
		else
		{
			dia=temp;
		}
	}
	else
	{
		if (temp > 31)
		{
			mes=mes+1;
			dia=temp-30;
		}
		else
		{
            dia=temp;
		}
	}
        temp=me+mes;
        if (temp>12)
	{
		ano=ano+1;
		mes=temp-11;
	}
	else
	{
		mes=temp;
	}
	temp=a+ano;
	ano=temp;
    diasem=obtenerDiaOfSemana(dia,mes,ano);
}

/*
 * * agrega o quita tiempo sea en dias, meses, años...
 * no posee retorno, modifica la fecha actual
 * */
void Fecha::quitar(int d, int me, int a, int h, int mi)
{
	int temp=minuto-mi;
	if (temp < 0)
	{
		hora=hora-1;
		minuto=60+temp;
	}
	else
	{
		minuto=temp;
	}
	temp=hora-h;
	if (temp < 0)
	{
		dia=dia-1;
		hora=24+temp;
	}
	else
	{
		hora=temp;
	}
	temp=dia-d;
	if (mes == 2)
        {
		if (temp < 1)
		{
            mes=mes-1;
			dia=28+temp;
		}
		else
		{
			dia=temp;
		}
	}
	else if ((me == 4) || (me == 6 ) || (me == 9) || (me == 11))
	{
		if (temp < 1)
		{
			mes=mes-1;
			dia=29+temp;
		}
		else
		{
			dia=temp;
		}
	}
	else
	{
		if (temp < 1)
		{
			mes=mes-1;
			dia=30+temp;
		}
		else
		{
			dia=temp;
		}
	}
	temp=mes-me;
	if (temp < 1)
	{
		ano=ano-1;
		mes=12+temp;
	}
	else
	{
		mes=temp;
	}
        temp=ano-a;
        ano=temp;
        diasem=obtenerDiaOfSemana(dia,mes,ano);
}

/*
* Genera el dia de la semana
* */
string Fecha::obtenerDiaOfSemana(int d, int m, int a)
{
        int res;
        string dia_sem;
        if (m < 3) a = a - 1;
        res = zeller(a,m,d);
        switch (res)
        {
                case 0:
                        dia_sem = "Domingo";
                break;
                case 1:
                        dia_sem = "Lunes";
                break;
                case 2:
                        dia_sem = "Martes";
                break;
                case 3:
                        dia_sem = "Miercoles";
                break;
                case 4:
                        dia_sem = "Jueves";
                break;
                case 5:
                        dia_sem = "Viernes";
                break;
                case 6:
                        dia_sem = "Sabado";
                break;
        }
        return dia_sem;
}

int Fecha::zeller(int y, int m, int d)
{
        int t[12] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        return (y + (y / 4) - (y / 100) + (y / 400) + t[m-1] + d) % 7;
}

//Una especia de set
void Fecha::modficarHora (int hora){this->hora=hora;}

#endif
