#ifndef _FUENTE_
#define _FUENTE_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

//!	Utilizada para gestionar fuentes ttf.

/**	
	Permite cargar desde memoria secundaria fuentes en formato ttf y posteriormente dibujarlas en pantalla
	
	@todo Abstraer el tema del color, incluir un atributo color para hacer más sencillo su uso.
	
	Ejemplo de uso :
	\code
	#include "fuente.h"
	
	// Se supone pantalla debidamente inicializada y el subsistema de vídeo inicializado
	SDL_Surface* pantalla;
	
	// Creamos un objeto Fuente: ruta, tamaño (supones SDL_TTF inicializada)
	Fuente sans("free-sans.ttf", 12);
	
	SDL_Color color = SDL_MapRGB(pantalla->format, 255, 0, 0);
	
	// Lo dibujamos: superficie, cadena, x, y, color
	sans.dibujar(pantalla, "Hola a todos", 100, 100, color);
	
	// Hacemos flip
	SDL_Flip(pantalla);
	\endcode
*/

class Fuente{
	public:
		
		/**
			Constructor
			Carga un fichero .ttf en memoria con un tamaño determinado.
			@param ruta Ruta del fichero ttf con la fuente
			@param puntos Tamaño de la fuente, por defecto 20
		*/
		Fuente(const char* ruta, int puntos = 20);
		
		/**
			Dibuja en la superficie una cadena dada en las cordenadas (x,y)
			@param superficie Superficie donde se va a hacer el blitting
			@param cadena Cadena que se va a dibujar
			@param x Coordenada en el eje x donde se va a dibujar
			@param y Coordenada en el eje y donde se va a dibujar
			@param color Color con el que se mostrara cadena
		*/
		void dibujar(SDL_Surface* superficie, const char* cadena, int x, int y, SDL_Color color);
		
		
		/**
			Consultor
			@return Puntero a TTF_Font con la fuente utilizada
		*/
		TTF_Font* tipo_fuente() const;
		
		/**
			Consultor
			@return Tamaño en puntos de la fuente
		*/
		int puntos() const;
		
		/**
			Destructor.
			Libera la memoria ocupada por la fuente
		*/
		~Fuente();
	private:
		TTF_Font* fuente;
		int puntos_;
		SDL_Surface* renderizada;
};

inline TTF_Font* Fuente::tipo_fuente() const {return fuente;}
inline int Fuente::puntos() const {return puntos_;}

#endif
