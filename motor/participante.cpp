#include <iostream>
#include "imagen.h"
#include "participante.h"
#include "universo.h"
#include "nivel.h"

bool Participante::esta_en_pantalla()
{
	int x1, x2, y1, y2, w1, w2, h1, h2;
	
	x1 = x/* - juego->niv()->nivel_x()*/;
	y1 = y/* - juego->niv()->nivel_y()*/;
	w1 = this->imagen->anchura();
	h1 = this->imagen->altura();
	x2 = 0;
	y2 = juego->niv()->nivel_y();
	h2 = juego->univ()->pantalla_alto();
	w2 = juego->univ()->pantalla_ancho();

	return (((x1 + w1) > x2) && ((y1 + h1) > y2) && ((x2 + w2) > x1) && ((y2 + h2) > y1));
}

void Participante::dibujar(SDL_Surface *superficie)
{
	// Si está en pantalla se dibuja
	if(this->esta_en_pantalla())
		imagen->dibujar(superficie, animaciones[estado]->cuadro_actual(), x - juego->niv()->nivel_x(), y - juego->niv()->nivel_y());	
}

void Participante::mover_sobre_x(int incremento)
{
	if(!(x + vx < 0 || x + vx + imagen->anchura() > 800))
		x += vx;
}

void Participante::mover_sobre_y(int incremento)
{
	if(!(y + vy < 0 || y + vy + imagen->altura() > 600))
		y += vy;
}
