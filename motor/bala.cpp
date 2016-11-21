#include "bala.h"
#include <iostream>
#include "juego.h"
#include "galeria.h"
#include "imagen.h"

Bala::Bala(Juego *juego, const string& clave, int pos_x, int pos_y, int vel_y, int a): Participante(juego), ataque_(a)
{
	x = pos_x;
	y = pos_y;
	vy = vel_y;
	vx = 0;
	
	animaciones[NORMAL] = new Control_Animacion("0", 1);
	animaciones[ELIMINAR] = new Control_Animacion("0", 1);
	
	estado = estado_anterior = NORMAL;
	
	imagen = galeria.imagen(clave);
	
	SDL_Rect caja_colision;
	
	caja_colision.x = 0;
	caja_colision.y = 0;
	caja_colision.w = imagen->anchura();
	caja_colision.h = imagen->altura();
	
	cajas_colision.push_back(caja_colision);
}

Bala::~Bala()
{
	for(map<enum estados, Control_Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
		delete i->second;
}

void Bala::actualizar()
{	
	if(estado != ELIMINAR){
		//Mover
		x += vx;
		y += vy;
		//Si se sale de la pantalla eliminar
		if(!this->esta_en_pantalla())
			estado = ELIMINAR;
	}
}

void Bala::colisiona_con(Participante *otro)
{
	//Marcar con eliminar
	estado = ELIMINAR;
}

