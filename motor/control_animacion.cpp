#include <iostream>
#include <cstring>
#include <cstdlib>
#include "control_animacion.h"

using namespace std;

Control_Animacion::Control_Animacion(const char* secuencia, int retardo): r_(retardo)
{
	int longitud = strlen(secuencia);
	char* temporal;
	char* paso_sig;
	
	// Creamos una cadena temporal para realizar la partición de la secuencia
	if((temporal = (char*)malloc((longitud + 1)* sizeof(char))) == NULL){
		cerr << "Control_Animacion::Control_Animacion(): No hay memoria suficiente" << endl;
	}
	
	strcpy(temporal, secuencia);
	nc = 0;
	
	// Extraemos cada elemento de la secuencia separado por ',' y lo convertimos en entero
	for(paso_sig = strtok(temporal, ","); paso_sig;){
		animacion.push_back(atoi(paso_sig));
		nc++;
		paso_sig = strtok(NULL, ",\0");
	}
	
	cr_ = 0;
	paso = 0;
	free(temporal);
}

Control_Animacion::Control_Animacion(const Control_Animacion& c)
{
	animacion = c.animacion;
	r_ = c.r_;
	cr_ = c.cr_;
	nc = c.nc;
	paso = c.paso;	
}

bool Control_Animacion::avanzar()
{
	// Si ha pasado el tiempo de retardo entre cuadro y cuadro
	if(++cr_ >= r_){
		cr_ = 0;
		if(++paso == nc){
			paso = 0;
			return true;
		}
	}
	return false;
}

