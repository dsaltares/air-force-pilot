#include <iostream>
#include "fuente.h"

using namespace std;

Fuente::Fuente(const char* ruta, int puntos): puntos_(puntos)
{
	// Abrimos la fuente
	if((fuente = TTF_OpenFont(ruta, puntos)) == NULL){
		cerr << "Fuente::Fuente(): " << TTF_GetError() << endl;
		exit(1);
	}
}

void Fuente::dibujar(SDL_Surface* superficie, const char* cadena, int x, int y, SDL_Color color)
{
	SDL_Surface* tmp;
	
	if(cadena == NULL)
		cout << "Cadena nula" << endl;
	
	// Renderizamos la fuente en una superficie temporal
	if((tmp = TTF_RenderUTF8_Solid(fuente, cadena, color)) == NULL){
		cerr << "Fuente::dibujar(): " << TTF_GetError() << endl;
		exit(1);
	}
	
	// Adaptamos la superficie al formato de la pantalla
	if((renderizada = SDL_DisplayFormat(tmp)) == NULL){
		cerr << "Fuente::dibujar(): " << TTF_GetError() << endl;
		exit(1);
	}
	
	SDL_FreeSurface(tmp);
	
	// Destino
	SDL_Rect destino;
	destino.x = x;
	destino.y = y;
	destino.w = renderizada->w;
	destino.h = renderizada->h;
	
	// Blitting
	SDL_BlitSurface(renderizada, NULL, superficie, &destino);
	
	SDL_FreeSurface(renderizada);
}

Fuente::~Fuente()
{
	TTF_CloseFont(fuente);
}

