#ifndef _ESCENA_
#define _ESCENA_

class Universo;

//!	Clase abstracta que representa una escena del Sistema

/**	
	Se utiliza como base para las distintas escenas del juego (menú, juego etc).
*/
class Escena{
	public:
		
		/**
			Las distintas escenas del juego
		*/
		enum escenas{
			JUEGO,
			MENU,
			TRANSICION
		};
		
		/**
			Constructor
			
			@param universo Universo con el que se asocia la escena
		*/
		Escena(Universo *universo);
		
		/**
			Destructor
			
			Libera la memoria ocupada por la escena
		*/
		virtual ~Escena();
		
		/**
			Método virtual puro
			
			Reinicia la escena
		*/
		virtual void reiniciar() = 0;
		
		/**
			Método virtual puro
			
			Actualiza lógicamente la escena y todos los elementos contenidos en ella
		*/
		virtual void actualizar() = 0;
		
		/**
			Método virtual puro
			
			Dibuja la escena en la pantalla
		*/
		virtual void dibujar() = 0;
		
		
		/**
			@return Puntero al universo al que pertenece la escena
		*/
		Universo* univ();
		
	protected:
		Universo *universo_;
};

inline Universo* Escena::univ() {return universo_;}

#endif
