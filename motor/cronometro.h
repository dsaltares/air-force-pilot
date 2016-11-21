#ifndef _CRONOMETRO_
#define _CRONOMETRO_

#include <SDL/SDL.h>

//! Cronómetro utilizado en el control del framerrate (utilizando funciones de SDL)

/**
	Es una clase sencilla que utilizamos para el control del tiempo en el juego.
	Como ejemplo puedo usar el del control del framerrate en Universo::sincronizar_fps();
	
	\code
	...
	crono.activar(); // Se activa en el constructor de Universo
	...
	void Universo::sincronizar_fps()
	{	    
		if(crono.tiempo() < (1000/maxfps))			// Si vamos demasiaod rápido...
			SDL_Delay((1000/maxfps) - crono.tiempo());	// ... Esperamos para estabilizar los fps
	
		crono.activar();
	}
	\endcode
*/

class Cronometro{
	public:
		/**
			Constructor
			Pone el contador a 0 y establece como inactivo el cronómetro
		*/
		Cronometro();
		
		/**
			Activa el cronómetro y pone la cuenta a 0
		*/
		void activar();
		
		/**
			Para el cronómetro
		*/
		void parar();
		
		/**
			Método consultor
			
			@return Tiempo en ms transcurrido desde que se activó el cronómetro por última vez.
			
		*/
		int tiempo() const;
		
		/**
			Método consultor
			
			@return Verdadero si el cronómetro está activo o falso en caso contrario
		*/
		bool esta_activo() const;
	private:
		bool activo;
		int ticks_inicio;
};

#endif
