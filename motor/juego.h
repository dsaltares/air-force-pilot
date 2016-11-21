#ifndef _JUEGO_
#define _JUEGO_

#include <list>
#include <SDL/SDL.h>

#include "escena.h"
//#include "participante.h"

class Universo;
class Nivel;
class Participante;
class Protagonista;
class Enemigo;
class Item;
class Harrier;
class Bala;

//!	Clase derivada de Escena utilizada para el Juego y su lógica

/**	
	Con Juego gestionamos la escena de juego y todos sus elementos
*/

class Juego: public Escena{
	public:
		
		/**
			Constructor
			
			Reserva memoria para la escena de juego. Utiliza la clase Nivel para cargar el escenario y los personajes
			
			@param universo Universo al que asociar la escena de juego
		*/
		Juego(Universo *universo);
		
		/**
			Destructor
			
			Libera la memoria ocupada por la escena
		*/			
		~Juego();
		
		/**
			Reinicia el juego, carga el primer nivel y elimina lo anterior
		*/
		void reiniciar();
		
		/**
			Dibuja la escena en pantalla con todos los participantes y el nivel en el siguiente orden:
			<ul>
				<li>Capa 0 del nivel (Terreno)</li>
				<li>Capa 1 del nivel (Objetos)</li>
				<li>Protagonista</li>
				<li>Items</li>
				<li>Enemigos</li>
				<li>Balas</li>
				<li>Capa 2 del nivel (Nubes)</li>
			</ul>
		*/
		void dibujar();
		
		/**
			Actualiza lógicamente todos los elementos del nivel
		*/
		void actualizar();
		
		/**
			Añade un Enemigo al nivel
			
			@param e Puntero al Enemigo que se añadirá
		*/
		void add_enemigo(Enemigo* e);
		
		/*
			Añade un Item al nivel
			
			@param i Puntero al Item que se añadirá
		*/
		//void add_item(Item& i);
		
		/**
			Añade el Protagonista al nivel (sólo puede añadirse uno)
			
			@param p Puntero al Protagonista que se añadirá
		*/
		void add_protagonista(Protagonista *p);
		
		/**
			Añade la Bala al nivel
			
			@param b Puntero a la Bala que se añadirá
		*/
		void add_bala(Bala *b);
		
		/**
			@return Puntero al nivel asociado al juego
		*/
		Nivel* niv();
		
	private:
		
		// Niveles del juego
		Nivel *nivel;
		int nnivel;
		
		// Participantes
		Protagonista *protagonista;
		std::list<Enemigo*> lista_enemigos;
		//std::list<Item*> lista_items;
		std::list<Bala*> lista_balas;
		
		// Funciones auxiliares
		bool colision(Participante *a, Participante *b); // Determina si dos participantes están colisionando
		//void eliminar_antiguos_items(); // Borra de la lista objetos adquiridos
		void eliminar_antiguos_enemigos(); // Borra de la lista enemigos eliminados
		void eliminar_antiguas_balas();
		void avisar_colisiones(); // Comprueba las colisiones
		
		void actualizar_normal(); // Actualiza la lógica del juego cuando no hay que cambiar de nivel ni reiniciar
};

//inline const Universo* Juego::univ() const {return universo_;}
inline Nivel* Juego::niv(){return nivel;}

#endif
