#ifndef _OPCION_
#define _OPCION_

#include <string>
#include <SDL/SDL.h>

#include "fuente.h"
#include "galeria.h"

//! Utilizada como elemento del menú del juego

/**
	Permite almacenar el texto, color y posición de cada opción del menu de juego
	
	Ejemplo de uso:
	\code
	#include "opcion.h"
	
	...
	
	Opcion jugar("Jugar", galeria.fuente("stencil"), 100, 100) // Hacemos uso del Singleton Galeria
	
	...
	
	jugar->dibujar(pantalla);
	\endcode
	
	En la clase Menu iteraríamos por las opciones dibujándolas.
	En dicha clase cargamos las opciones mediante un xml.
*/


class Opcion{
	public:
		/**
			Constructor
			
			@param texto Texto de la opción
			@param fuente Puntero a Fuente, tipografía para mostrar el texto de la opción
			@param x Coordenada en el eje x donde se mostrará la opción
			@param y Coordenada en el eje y donde se mostrará la opción
			@param r1 Componente RGB rojo para el color de la opción no seleccionada
			@param g1 Componente RGB verde para el color de la opción no seleccionada
			@param b1 Componente RGB azul para el color de la opción no seleccionada
			@param r2 Componente RGB rojo para el color de la opción seleccionada
			@param g2 Componente RGB verde para el color de la opción seleccionada
			@param b2 Componente RGB azul para el color de la opción seleccionada
		*/		
		Opcion(const std::string& texto, Fuente* fuente, int x, int y, int r1 = 0, int g1 = 0, int b1 = 0, int r2 = 0, int g2 = 0, int b2 = 0);
		
		/**
			Dibuja la opción en sus coordenadas x e y en un color según esté seleccionada o no
			
			@param superficie Superficie donde sobre la que se hará blitting
			@seleccionada Verdadero si se utiliza el color para la opción seleccionada y falso en caso contrario
		*/
		void dibujar(SDL_Surface* superficie, bool seleccionada = false);
		
		/**
			Consultora
			
			@return Coordenada en el eje x de la opción
		*/
		int pos_x() const;
		
		/**
			Consultora
			
			@return Coordenada en el eje y de la opción
		*/
		int pos_y() const;
		
		/**
			Consultora
			
			@return Texto de la opción
		*/
		const std::string& texto() const;
			
	private:
		std::string texto_;
		Fuente *fuente_;
		int x_, y_;
		int r1_, g1_, b1_, r2_, g2_, b2_;
};

inline int Opcion::pos_x() const {return x_;}
inline int Opcion::pos_y() const {return y_;}
inline const std::string& Opcion::texto() const {return texto_;}

#endif

