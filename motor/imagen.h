#ifndef _IMAGEN_
#define _IMAGEN_

#include <iostream>
#include <string>
#include <SDL/SDL.h>
 
//!	Utilizada para gestionar rejillas de imágenes.

/**	Permite cargar desde memoria secundaria una imagen compuesta por bloques que pueden ser individualmente dibujados en pantalla.
	La idea de utilizar rejillas de imágenes se debe a la facilidad que se gana para manejar Sprites.
	Sino se precisa se pueden utilizar imágenes de 1 fila y 1 columna (imágenes individuales).
	
	Ejemplo de uso:
	\code
	#include "imagen.h"
	
	// Se supone pantalla debidamente inicializada y el subsistema de vídeo inicializado
	SDL_Surface* pantalla;
	
	// Creamos un objeto Imagen: ruta, filas, columnas
	Imagen avion("avion.png", 3, 4);
	
	// Lo dibujamos: superficie, frame, x, y
	avion.dibujar(pantalla, 5, 100, 200);
	
	// Hacemos flip
	SDL_Flip(pantalla);
	\endcode
*/

class Imagen{
	public:
		/**
			Constructor
			Carga la rejilla de imagenes dadas sus filas y columnas que indique ruta. 
			Cualquier formato soportado por SDL_Image es válido
			@param ruta Ruta del fichero que contiene la imagen
			@param filas Número de filas de la rejilla
			@param columnas Número de columnas de la rejilla
		*/
		Imagen(const char* ruta, int filas = 1, int columnas = 1, int x = 0, int y = 0);
		
		
		/**
			Constructor
			Carga la rejilla de imagenes dadas sus filas y columnas que indique ruta. 
			Cualquier formato soportado por SDL_Image es válido
			@param ruta Ruta del fichero que contiene la imagen
			@param filas Número de filas de la rejilla
			@param columnas Número de columnas de la rejilla
		*/
		Imagen(const std::string& ruta, int filas = 1, int columnas = 1, int x = 0, int y = 0);
		
		/**
			Hace blitting sobre la superficie indicada del frame cuadro dado en la posición (x,y)
			@param pantalla Superficie sobre la cual se hará el blitting
			@param cuadro Frame de la rejilla que se eligirá (debe ser un frame válido)
			@param x Coordenada en el eje x donde se dibujará la imagen
			@param y Coordenada en el eje y donde se dibujará la imagen
			@param flip 1 imagen dibujada normal, -1 imagen invertida horizontalmente
		*/
		void dibujar(SDL_Surface* pantalla, int cuadro, int x, int y, int flip = 1);
		
		/**
			Consultor
			@return Número de filas de la rejilla
		*/
		int filas() const;
		
		/**
			Consultor
			@return Número de columnas de la rejilla
		*/
		int columnas() const;
		
		/**
			Consultor
			@return Anchura en píxeles de un cuadro de la rejilla
		*/
		int anchura() const;
		
		/**
			Consultor
			@return Altura en píxeles de un cuadro de la rejilla
		*/
		int altura() const;
		
		/**
			Consultor
			@return Número de cuadros de la rejilla
		*/
		int cuadros() const;
		
		/**
			Destructor.
			Libera los recursos consumidos por la rejilla.
		*/
		~Imagen();
	private:
		SDL_Surface* imagen;
		SDL_Surface* invertida;
		
		SDL_Surface* invertir_imagen();
		
		int  f_, c_, x_, y_;
};

inline int Imagen::filas() const {return f_;}
inline int Imagen::columnas() const {return c_;}
inline int Imagen::anchura() const {return (imagen->w / c_);}
inline int Imagen::altura() const {return (imagen->h / f_);}
inline int Imagen::cuadros() const {return f_*c_;}

#endif
