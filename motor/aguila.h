#ifndef _AGUILA_
#define _AGUILA_

#include <string>
#include "participante.h"
#include "enemigo.h"

class Aguila: public Enemigo {
	
	public:
	
		Aguila(Juego *j, const std::string& ruta, int x = 0, int y = 0);
		Aguila(const Aguila& aguila);
		~Aguila();
	
		/**
			Actualiza el Aguila según su lógica. Debe llamarse a esta función en cada iteración del bucle del juego
		*/
		void actualizar();
		
		/**
			Función a llamar cuando un Aguila colisiona con el Aguila. Recalcula los atributos del Aguila en función de los del Aguila.
			
			@param otro Puntero al Participante con el que colisiona
		*/
		void colisiona_con(Participante *otro);
		
		/**
			Método consultor
			
			@return Energía del Aguila, su vida.
		*/
		int energia() const;
		
		/**
			Modificador
			
			@param diferencia Cantidad a sumársele a la energía del Aguila.
		*/
		void energia(int diferencia);
		
		/**
			Método consultor
			
			@return Daño que hace el Aguila cuando impactan sus balas sobre un Aguila
		*/
		int ataque() const;
		
		/**
			Metodo consultor
			
			@return Número de frames que deben pasar para que el Aguila vuelva a disparar
		*/
		int cadencia() const;
		
		/**
			@return Puntero a un Aguila nuevo copia de este
		*/
		Aguila* copia();
		
	private:
		int energia_, ataque_;
		
		int cadencia_, contador;
		
		void estado_normal();
		void estado_acelerado();
		void estado_frenado();
		void estado_morir();
};

inline int Aguila::energia()const {return energia_;}
inline void Aguila::energia(int diferencia) {energia_ += diferencia;}
inline int Aguila::ataque()const {return ataque_;}
inline int Aguila::cadencia()const {return cadencia_;}

#endif
