#ifndef _MUSICA_
#define _MUSICA_

#include <SDL/SDL_mixer.h>

//!	Utilizada para cargar y reproducir la BSO del juego.

/**	
	Permite cargar desde memoria secundaria músicas
	
	
	Ejemplo de uso :
	\code
	#include "musica.h"
	
	// Se supone pantalla debidamente inicializada y el subsistema de vídeo y audio inicializados
		
	// Creamos un objeto Musica: ruta
	Musica ambiente("ambiente.wav");
	
	// Reproducimos el sonido
	ambiente.reproducir();
	
	// Pausamos el sonido
	ambiente.pausar();
	
	// Paramos el sonido
	ambiente.parar();
	\endcode
*/

class Musica{
	public:
		
		/**
			Constructor
			Carga en memoria un fichero de audio indicado por ruta
			@param ruta Ruta del fichero de audio
		*/
		Musica(const char* ruta);
		
		/**
			Reproduce la música si está parada, la reanuda si está pausada
		*/
		void reproducir();
		
		/**
			Pausa la música
		*/
		void pausar();
		
		/**
			Para la música
		*/
		void parar();
		
		/**
			Destructor.
			Libera la memoria ocupada por el objeto
		*/
		~Musica();
	private:
		Mix_Music* musica;
};

#endif
