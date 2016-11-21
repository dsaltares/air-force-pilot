#include <iostream>
#include <algorithm>
#include "fuente.h"
#include "texto.h"

using namespace std;

Texto::Texto(Fuente* fuente, int r, int g, int b, SDL_Rect caja, string cadena): fuente_(fuente), r_(r), g_(g), b_(b), caja_(caja), cadena_(cadena)
{
	cambio_ = true;
}

void Texto::dibujar(SDL_Surface* superficie)
{
	
	/*int longitud = cadena_.length();
	char* temporal;
	char* palabra_sig;
	int palabras_linea = 0;
	int ancho_linea = 0, alto_linea = 0, alto_texto = 0, ancho_palabra = 0, alto_palabra = 0;
	int x = caja_.x, y = caja_.y;
		
		// Creamos una cadena temporal para realizar la partición del texto
		if((temporal = (char*)malloc((longitud + 1)* sizeof(char))) == NULL){
			cerr << "Texto::dibujar(): No hay memoria suficiente" << endl;
		}
	
		strcpy(temporal, cadena_.c_str());
	
		// Extraemos cada palabra y la procesamos
		for(palabra_sig = strtok(temporal, " "); palabra_sig;){
			TTF_SizeText(fuente_->tipo_fuente(), palabra_sig, &ancho_palabra, &alto_palabra);
			ancho_linea += ancho_palabra;
			alto_linea = max(alto_palabra, alto_linea);

			if(ancho_linea > caja_.w && palabras_linea == 0){ // No cabe ni una palabra en la caja
				cerr << "Texto::dibujar(): " << palabra_sig << " supera el ancho de la caja de texto" << endl;
				exit(1);
			}
		
			if(ancho_linea > caja_.w){ // Habremos superado el ancho de la caja y debemos saltar una línea
				x = caja_.x; // Volvemos al comienzo de la línea
				ancho_linea = 0; // Por ahora la linea no tiene ancho
				y += TTF_FontLineSkip(fuente_->tipo_fuente()); //+ fuente_->puntos()/10; // Bajamos una linea
				palabras_linea = 0;
				alto_linea = 0;
			}
			
			cout << color_.r << " " << color_.g << " " << color_.b << endl;
			fuente_->dibujar(superficie, palabra_sig, x, y, color_);
			palabras_linea++;
			x += ancho_palabra + fuente_->puntos()/4;
		
			palabra_sig = strtok(NULL, " \0");
		}
		free(temporal);*/
	int x = (int)caja_.x;
	int y = (int)caja_.y;
	SDL_Color color;
	color.r = r_;
	color.g = g_;
	color.b = b_;
	color.unused = 0;
	fuente_->dibujar(superficie, cadena_.c_str(), x, y, color);
}

void Texto::dibujar(SDL_Surface* superficie, int x, int y)
{
	caja_.x = x;
	caja_.y = y;
	dibujar(superficie);
}

void Texto::dibujar(SDL_Surface* superficie, const string& cadena)
{
	cadena_ = cadena;
	dibujar(superficie);
}
