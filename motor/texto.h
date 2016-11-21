#ifndef _TEXTO_
#define _TEXTO_

#include <SDL/SDL.h>

class Fuente;

//!	Gestor de cuadros de texto

/**	
	Utiliza la clase Fuente y se encarga de almacenar un texto que puede ser dibujado en pantalla dentro de unos limites establecidos por un SDL_RECT
	Si no cabe el texto en una línea se encarga de introducir saltos de línea cuando sea oportuno
	
	@todo Mejorar el salto de línea y los espaciados
	@todo Detectar que "\n" es un salto de línea
	
	Ejemplo de uso :
	\code
	#include "texto.h"
	
	// Se supone SDL inicializado, así como SDL_TTF
	SDL_Surface *pantalla;
	
	// Fuente
	Fuente arial("arial.ttf", 12);
	
	//Color del texto
	SDL_Color color = SDL_MapRGB(pantalla->pixelformat, 100, 0, 0);
	
	// Límites de impresión
	SDL_Rect rect = {10, 10, 400, 400};
		
	Texto texto1(&arial, color, rect);
	
	texto1.dibujar(pantalla, "Hola, muy buenas, esto es una prueba de mi clase Texto");
	
	SDL_Flip(pantalla);
	
	\endcode
*/

class Texto{
	public:
		/**
			Constructor
			Asocia un texto con una fuente, le asigna un color y un recuadro donde dibujarse, opcionalmente puede incluirse una cadena
			@param fuente Puntero a Fuente que se utilizará para blitear el texto en la pantalla
			@param color Color con el que se dibujará el texto
			@param caja Límites de la pantalla donde se colocará el texto
			@param cadena Cadena que contiene el texto a dibujar
		*/
		Texto(Fuente* fuente, int r, int g, int b, SDL_Rect caja, std::string cadena = "");
		
		/**
			Dibuja la cadena almacenada en el objeto, con la fuente asociada, en el color correspondiente en las coordenadas (x,y).
			Se utilizan la anchura y altura definidas en el recuadro como límites (SDL_Rect con el se construyó el objeto).
			
			@param superficie Superficie donde se dibujará el texto
			@param x Coordenada en el eje x donde se dibujará el texto
			@param y Coordenada en el eje y donde se dibujará el texto
		*/
		void dibujar(SDL_Surface* superficie, int x, int y); // Se puede dibujar en unas coordenadas determinadas o en las de la caja
		
		/**
			Dibuja la cadena almacenada en el objeto, con la fuente asociada, en el color correspondiente.
			Se utilizan la anchura, la altura y las coordenadas (x,y) del recuadro (SDL_Rect con el se construyó el objeto).
			
			@param superficie Superficie donde se dibujará el texto
		*/
		void dibujar(SDL_Surface* superficie);
		
		/**
			Idéntico al método anterior sólo que asigna la cadena al contenido del objeto y lo dibuja.
			Ahorraría hacer:
			
			\code
			texto.cadena = "Hola, esto es otra cadena";
			texto.dibujar(pantalla);
			\endcode
			
			@param superficie Superficie donde se dibujará el texto
			@param cadena Cadena que se le asigna al objeto y que se dibujará
		*/
		void dibujar(SDL_Surface* superficie, const std::string& cadena);
		
		/**
			Consultor
			@return Cuadro que límita y sitúa al texto en la pantalla
		*/			
		const SDL_Rect& caja() const;
		
		/**
			Consultor
			@return Cadena del texto
		*/
		const std::string& cadena() const;
		
		/**
			Consultor
			@return Color utilizado para dibujar el texto
		*/
		//const SDL_Color& color() const;
		
		/**
			Modificador
			@return Referencia al recuadro que límita y sitúa al texto en la pantalla
		*/
		SDL_Rect& caja(); // Modificar la caja
		
		/**
			Modificador
			@return Referencia a la cadena que contiene el texto
		*/
		std::string& cadena(); // Modificar la cadea
		
		/**
			Modificador
			@return Referencia al color con el que se dibuja el texto
		*/
		//SDL_Color& color(); // Modificar el color
	private:
		Fuente* fuente_;
		SDL_Surface* renderizado_;
		//SDL_Color color_;
		int r_, g_, b_;
		bool cambio_;
		SDL_Rect caja_;
		std::string cadena_;
};

inline const SDL_Rect& Texto::caja() const {return caja_;}
inline const std::string& Texto::cadena() const {return cadena_;}
//inline const SDL_Color& Texto::color() const {return color_;}
inline SDL_Rect& Texto::caja() {return caja_;}
inline std::string& Texto::cadena() {cambio_ = 0; return cadena_;}
//inline SDL_Color& Texto::color() {return color_;}

#endif
