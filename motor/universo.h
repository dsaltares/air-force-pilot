#ifndef _UNIVERSO_
#define _UNIVERSO_

#include <string>

#include "Teclado.h"
#include "escena.h"
#include "menu.h"
#include "juego.h"
#include "cronometro.h"
#include "transicion.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

class Juego;

//!	Clase que controla el funcionamiento general del juego

/**	
	Se encarga de establecer la configuración, inicializar SDL y cargar los recursos
	
	
	Ejemplo de uso :
	\code
	#include "universo.h"
	
	int main(void)
	{
		Universo universo("configuracion.xml");
		
		while(universo.bucle_principal()){}
		
		return 0;
	}
	\endcode
*/

class Universo{
	public:
		/**
			Constructor
			
			@param ruta Ruta del fichero de configuración del juego
		*/
		Universo(const char *ruta);
		
		/**
			Se encarga de actualizar lógica y gráficamente la pantalla
		*/
		void bucle_principal(void);
		
		/**
			@return Puntero a la superficie principal de SDL (pantalla)
		*/
		SDL_Surface* 	superficie();
		
		/**
			@return Puntero a Teclado
		*/
		Teclado* tecla();
		
		/**
			@return Puntero a Transicion
		*/
		Transicion* transicion();
		
		/**
			Hace que en el siguiente frame se salga del programa
		*/
		void terminar();
		
		/**
			Método consultor
			
			@return Ancho en píxeles de la pantalla
		*/
		int pantalla_ancho() const;
		
		/**
			Método consultor
			
			@return Alto en píxeles de la pantalla
		*/
		int pantalla_alto() const;
		
		/**
			Método consultor
			
			@return Profundidad de color en bits per pixel de la pantalla
		*/
		int pantalla_bpp() const;
		
		/**
			Método consultor
			
			@return Frecuencia de actualización del juego, frames per second, fps
		*/
		int framespersecond() const;
		
		/**
			Destructor
			
			Libera la memoria consumida por el juego
		*/
		~Universo();
	private:
		
		bool salir;
		Escena *actual;
		Juego *juego;
		Menu *menu;
		Transicion *transicion_;
		Teclado teclado;
		SDL_Surface *pantalla;
		
		int ancho, alto, bpp, maxfps;
		
		Cronometro crono;
		
		void iniciar_ventana(bool completa);
		void pantalla_completa();
		void procesar_eventos(void);
		void sincronizar_fps();
		void cambiar_escena(Escena::escenas nueva);
		//void escena_intermedia(const std::string& ruta);
		friend void Menu::seleccionar_opcion();
		friend void Juego::actualizar();
		friend void Transicion::actualizar();
};

inline void Universo::terminar() {salir = true;}

inline SDL_Surface* Universo::superficie(){return pantalla;}
inline Teclado* Universo::tecla(){return &teclado;}
inline int Universo::pantalla_ancho() const {return ancho;}
inline int Universo::pantalla_alto() const {return alto;}
inline int Universo::pantalla_bpp() const {return bpp;}
inline int Universo::framespersecond() const {return maxfps;}
inline Transicion* Universo::transicion() {return transicion_;}

#endif
