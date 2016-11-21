#ifndef _ENEMIGO_
#define _ENEMIGO_

#include "participante.h"

class Juego;

//! Clase virtual pura para tratar a todos los enemigos de manera uniforme

/**
	Esta clase sirve para tratar en la función que controla el juego a todos los enemigos de manera uniforme
	Utiliza el polimorfismo para permitir que se elija la función actualizar en tiempo de ejecución según la
	clase de la hija de Enemigo.
*/

class Enemigo: public Participante{
	public:
		Enemigo(Juego* j);
		~Enemigo();
		
		virtual Enemigo* copia() = 0;
};

#endif
