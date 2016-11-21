#ifndef _SONIDO_
#define _SONIDO_

#include <SDL/SDL_mixer.h>

//!	Utilizada para cargar y reproducir efectos de sonido del juego.

/**	
	Permite cargar desde memoria secundaria efectos de sonido
	
	
	Ejemplo de uso :
	\code
	#include "sonido.h"
	
	// Se supone pantalla debidamente inicializada y el subsistema de vídeo y audio inicializados
		
	// Creamos un objeto Sonido: ruta
	Sonido disparo("disparo.wav");
	
	// Reproducimos el sonido
	disparo.reproducir();
	\endcode
*/

class Sonido{
	public:
	
		/**
			Constructor
			Carga el fichero de audio
			@param ruta Ruta del fichero de audio a cargar
		*/
		Sonido(const char* ruta);
		
		/**
			Reproduce el efecto de sonido 1 vez
		*/
		void reproducir();
		
		/**
			Destructor
			Libera la memoria ocupada por el efecto
		*/
		~Sonido();
	private:
		Mix_Chunk* sonido;
};

#endif
