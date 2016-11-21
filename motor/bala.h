#ifndef _BALA_
#define _BALA_

#include <string>
#include "participante.h"

class Juego;

//!	Objeto que representa los proyectiles del juego

/**	
	Se utiliza para controlar los proyectiles lanzados por el protagonista y los enemigos
	
	Ejemplo de uso:
	
	\code
		#include "juego.h"
		#include "bala.h"
		
		// Imaginamos que estamos en la función en la que un Participante dispara
		void disparar()
		{
			Bala *bala = new Bala(juego, "disp", this->x+40 , this->y+10, -3, this->ataque_);
			juego->add_bala(bala);
		}
	\endcode
*/

class Bala: public Participante{
	public:
		
		/**
			Constructor
			
			@param juego Juego al que pertenece la bala
			@param clave Cadena para asignarle una imagen de la Galeria a la bala
			@param pos_x Coordenada en x donde aparecerá la bala
			@param pos_y Coordenada en y donde aparecerá la bala
			@param vel_y Velocidad en y para la bala
			@param a Daño que producirá la bala al impactar en un enemigo
		*/
		Bala(Juego *juego, const string& clave, int pos_x, int pos_y, int vel_y, int a);
		
		/**
			Destructor
			
			Libera la memoria ocupada por la Bala
		*/
		~Bala();
		
		/**
			Actualiza lógicamente a la bala (la desplaza según su velocidad o la marca para eliminar si se sale de la pantalla, estado ELIMINAR)
		*/
		void actualizar();
		
		/**
			Cuando la bala impacta en algún objetivo se marca para su eliminación (estado ELIMINAR)
		*/
		void colisiona_con(Participante *otro);
		
		/**
			Consultor
			
			@return Daño que produce la bala al impactar sobre un objetivo
		*/
		int ataque() const;
		
	private:
		int ataque_;
};

inline int Bala::ataque() const {return ataque_;}

#endif
