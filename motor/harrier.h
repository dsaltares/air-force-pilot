#ifndef _HARRIER_
#define _HARRIER_

#include <string>
#include "participante.h"
#include "enemigo.h"

class Juego;

class Harrier: public Enemigo{
	public:
		Harrier(Juego* j, const std::string& ruta, int x = 0, int y = 0);
		Harrier(const Harrier& harrier);
		~Harrier();
		
		/**
			Actualiza el harrier según su lógica. Debe llamarse a esta función en cada iteración del bucle del juego
		*/
		void actualizar();
		
		/**
			Función a llamar cuando un harrier colisiona con el harrier. Recalcula los atributos del harrier en función de los del harrier.
			
			@param otro Puntero al Participante con el que colisiona
		*/
		void colisiona_con(Participante *otro);
		
		/**
			Método consultor
			
			@return Energía del harrier, su vida.
		*/
		int energia() const;
		
		/**
			Modificador
			
			@param diferencia Cantidad a sumársele a la energía del harrier.
		*/
		void energia(int diferencia);
		
		/**
			Método consultor
			
			@return Daño que hace el harrier cuando impactan sus balas sobre un harrier
		*/
		int ataque() const;
		
		/**
			Metodo consultor
			
			@return Número de frames que deben pasar para que el harrier vuelva a disparar
		*/
		int cadencia() const;
		
		/**
			@return Puntero a un Harrier nuevo copia de este
		*/
		Harrier* copia();
		
	private:
		int energia_, ataque_;
		
		int cadencia_, contador;
		
		void estado_normal();
		void estado_acelerado();
		void estado_frenado();
		void estado_morir();
};

inline int Harrier::energia()const {return energia_;}
inline void Harrier::energia(int diferencia) {energia_ += diferencia;}
inline int Harrier::ataque()const {return ataque_;}
inline int Harrier::cadencia()const {return cadencia_;}

#endif
