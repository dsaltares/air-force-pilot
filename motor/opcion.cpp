#include <iostream>
#include <SDL/SDL.h>
#include "opcion.h"

using namespace std;

Opcion::Opcion(const std::string& texto, Fuente* fuente, int x, int y, int r1, int g1, int b1, int r2, int g2, int b2):
		texto_(texto), fuente_(fuente), x_(x), y_(y), r1_(r1), g1_(g1), b1_(b1), r2_(r2), g2_(g2), b2_(b2)
{
	if(!fuente_){
		cerr << "Opcion::Opcion(): Fuente inexistente" << endl;
		exit(1);
	}
}

void Opcion::dibujar(SDL_Surface* superficie, bool seleccionada)
{
	SDL_Color color = {r1_, g1_, b1_, 0};
	
	// Vemos si la opción está seleccionada o no
	if(seleccionada){
		color.r = r2_;
		color.g = g2_;
		color.b = b2_;
	}
	
	// Dibujamos
	fuente_->dibujar(superficie, texto_.c_str(), x_, y_, color);
}
