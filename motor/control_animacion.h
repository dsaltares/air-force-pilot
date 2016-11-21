#ifndef _CONTROL_ANIMACION_
#define _CONTROL_ANIMACION_

#include <vector>

//!	Permite manejar secuencias de enteros (cuadros de una animación).

/**	Se crea con una secuencia de caracteres tipo "1,3,2,4,5,10,23" (que posteriormente se convierte a enteros) y un retardo (en frames).
	Sirve para llevar el control de qué cuadro de una rejilla de imágenes (clase Imagen) hay que mostrar en cada iteración
	
	Ejemplo de uso:
	\code
	#include <iostream>
	#include "control_animacion.h"
	
	using namespace std;
	
	...
	
	Control_Animacion animacion("1,2,3,4,5,6,7,8", 10);
	
	// Mientras que no hemos terminado la secuencia
	while(!animacion.avanzar()){
		cout << animacion.cuadro_actual() << endl;
		// Esperamos
		SDL_Delay(40);
	}
	
	// Cada 10 iteraciones del bucle while se avanza un cuadro
	
	\endcode
*/

class Control_Animacion{
	public:
	
		/**
			Constructor
			Toma una secuencia con su retardo
			@param secuencia Secuencia con formato "a1,a2,a3,...,an" donde ai es un entero que contiene la secuencia de cuadros
			@param retardo Tiempo de espera para pasar de un cuadro a otro medido en frames
			Si nuestro objeto control_animacion tiene retardo 100 y nuestro juego corre a 25fps se producirá un cambio de cuadro cada 4 segundos
		*/
		Control_Animacion(const char* secuencia, int retardo);
		
		Control_Animacion(const Control_Animacion& c);
		
		/**
			Método que incrementa el contador de retardo en 1 y si ha pasado el tiempo suficiente pasa al siguiente cuadro
			Si se termina la secuencia y se sigue avanzando se vuelve a empezar
			@return Verdadero si se ha terminado la secuencia, Falso en caso contrario
		*/
		bool avanzar();
		
		/**
			Hace que la secuencia comience de nuevo, independientemente del cuadro en el que se encuentre
		*/
		void reiniciar();
		
		/**
			Método consultor
			@return Cuadro en el que se encuentra actualmente la animación
		*/
		int cuadro_actual() const;
		
		/**
			Método consultor
			@return Número de cuadros que posee la secuencia
		*/
		int ncuadros() const;
	private:
		std::vector<int> animacion;
		int r_, cr_, nc, paso;
};

inline int Control_Animacion::cuadro_actual() const {return animacion[paso];}
inline int Control_Animacion::ncuadros() const {return nc;}

inline void Control_Animacion::reiniciar() {paso = 0; cr_ = 0;}

#endif
