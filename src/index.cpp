#include <stdio.h>
#include <cstdlib>
#include <iostream>

#include "cli/interfaz.cpp"
#include "ctrl/Controller.cpp"
#include "db/BaseDatos.cpp"
#include "lib/Lista.cpp"

using namespace std;

int main ()
{
	//implemenatacion mvc
    BaseDatos *bd = new BaseDatos();
    Controller *ctrl = new Controller(bd);
    Interfaz *interfaz = new Interfaz(ctrl);
    interfaz->run();
    return 0;
}

