#ifndef _PARTICIPANTE_
#define _PARTICIPANTE_

#include <map>
#include <vector>
#include <SDL/SDL.h>
#include "galeria.h"
#include "control_animacion.h"
#include "juego.h"


/**
	\enum estados
	
	Diferentes estados en los que puede encontrarse un Participante
*/
enum estados{
	NORMAL,
	ACELERADO,
	FRENADO,
	MORIR,
	ELIMINAR
};

//!	Clase virtual pura para gestionar el comportamiento común de todos los participantes

/**	
	Al ser una clase virtual pura no se pueden construir objetos de ella, pero sí de sus clases derivadas:
	
	<ul>
		<li>Protagonista</li>
		<li>Enemigo</li>
		<li>Item</li>
	</ul>
	
	Al no poder utilizarse como tal, no coloco ningún código de ejemplo
*/

class Participante{
	public:
		
		/**
			@typedef Animaciones
			Diccionario que relaciona un estado con una con secuencia de cuadros (animación).
		*/
		typedef std::map<estados, Control_Animacion*> Animaciones;
		
		//Participante(const std::string& tipo, int x, int y);
		
		/**
			Constructor
			
			@param j Escena Juego con la que se asocia el Participante
		*/
		Participante(Juego *j): juego(j){};
		
		/**
			Destructor
			
			Libera la memoria ocupada por el participante
		*/
		~Participante(){};
		
		/**
			Método consultor
			
			@return Coordenada en el eje x del participante
		*/
		int pos_x() const;
		
		/**
			Método consultor
			
			@return Coordenada en el eje y del participante
		*/
		int pos_y() const;
		
		/**
			Método consultor
			
			@return Velocidad en el eje y del participante
		*/
		int vel_y() const;
		
		/**
			Método consultor
			
			@return Velocidad en el eje x del participante
		*/
		int vel_x() const;
		
		/**
			Método modificador
			
			@param a Nueva coordenada en el eje x del participante
		*/
		void pos_x(int a);
		
		/**
			Método modificador
			
			@param a Nueva coordenada en el eje y del participante
		*/
		void pos_y(int a);
		
		/**
			Método modificador
			
			@param a Nueva velocidad en el eje x del participante
		*/
		void vel_x(int a);
		
		/**
			Método modificador
			
			@param a Nueva velocidad en el eje y del participante
		*/
		void vel_y(int a);
		
		/**
			Método virtual puro
			
			Actualizaría el participante según su lógica específica
		*/
		virtual void actualizar() = 0;
		
		/**
			Carga el cuadro correspondiente al participante según su estado y su animación en la superficie indicada
			
			@param superficie Superficie donde se cargará el participante
		*/
		void dibujar(SDL_Surface *superficie);
		
		/**
			Método virtual puro
			
			Haría colisionar el participante con otro de algún tipo y reaccionaría según la lógica del tipo de participante
			
			@param otro Participante con el que hace colisión
		*/
		virtual void colisiona_con(Participante *otro) = 0;
		
		/**
			Consultor
			
			@return Vector de cajas de colisiones del Participante
		*/
		const std::vector<SDL_Rect>& zona_colision() const;
		
		/**
			Método consultor
			
			@return Estado en el que se encuentra el participante	
		*/
		enum estados estado_actual() const;
		
		/**
			Método consultor
			
			@return true si el participante está total o parcialmente en la pantalla, false en caso contrario
		*/
		bool esta_en_pantalla();
		
	protected:
		Juego *juego;
		
		Imagen *imagen;
		int x, y, vx, vy;
		
		enum estados estado, estado_anterior;
		Animaciones animaciones;
		
		std::vector<SDL_Rect> cajas_colision;
		
		void mover_sobre_x(int incremento);
		void mover_sobre_y(int incremento);
};


inline enum estados Participante::estado_actual() const {return estado;}
inline const std::vector<SDL_Rect>& Participante::zona_colision() const {return cajas_colision;}
inline int Participante::pos_x() const {return x;}
inline int Participante::pos_y() const {return y;}
inline void Participante::pos_x(int a) {x = a;}
inline void Participante::pos_y(int a) {y = a;}
inline int Participante::vel_y() const {return vy;}
inline int Participante::vel_x() const {return vx;}
inline void Participante::vel_y(int a){vy = a;}
inline void Participante::vel_x(int a){vx = a;}

#endif
