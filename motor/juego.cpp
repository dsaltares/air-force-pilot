#include <string>
#include <iostream>

#include "participante.h"
#include "protagonista.h"
#include "bala.h"
#include "juego.h"
#include "universo.h"
#include "nivel.h"
#include "galeria.h"
#include "imagen.h"
#include "musica.h"
#include "enemigo.h"

using namespace std;

Juego::Juego(Universo *universo): Escena(universo)
{
	
	nivel = new Nivel(this, "niveles.xml");
	
	protagonista = NULL;
	nnivel = 0;
	
	// Comenzamos
	//reiniciar();
}

Juego::~Juego()
{
	
	// Liberamos memoria
	delete nivel;
	
	// Limpiamos las listas de participantes
	for(list<Enemigo*>::iterator i = lista_enemigos.begin(); i != lista_enemigos.end(); i++){
		delete *i;
		*i = NULL;
	}
	
	lista_enemigos.clear();
	
	for(list<Bala*>::iterator i = lista_balas.begin(); i != lista_balas.end(); i++){
		delete *i;
		*i = NULL;
	}
	
	lista_balas.clear();
	
	if(protagonista){
		delete protagonista;
		protagonista = NULL;
	}
}
		
void Juego::reiniciar()
{
	// Limpiamos las listas de participantes
	for(list<Enemigo*>::iterator i = lista_enemigos.begin(); i != lista_enemigos.end(); i++){
		delete *i;
		*i = NULL;
	}
	
	lista_enemigos.clear();

	for(list<Bala*>::iterator i = lista_balas.begin(); i != lista_balas.end(); i++){
		delete *i;
		*i = NULL;
	}
	
	lista_balas.clear();

	if(protagonista != NULL){
		delete protagonista;
		protagonista = NULL;
	}

	// Empezamos desde el principio
	
	nivel->cargar_nivel(nnivel);
	
	protagonista = new Protagonista(this, "XML/protagonista.xml", 200, nivel->nivel_y() + 300);

	//add_protagonista(p);
	
	// Comienza la música
	galeria.musica("musica")->reproducir();
	
}

void Juego::dibujar()
{
	
	// Dibujamos el nivel
	nivel->dibujar(univ()->superficie(), 0);
	nivel->dibujar(univ()->superficie(), 1);
	
	// Dibujamos personaje, enemigos, items

	if(protagonista != NULL){
		protagonista->dibujar(univ()->superficie());
	}
	
	//for(list<Item*>::iterator i = lista_items.begin(); i != lista_items.end(); i++)
	//	(i*)->dibujar(univ()->superficie());
		
	for(list<Enemigo*>::iterator i = lista_enemigos.begin(); i != lista_enemigos.end(); i++)
		(*i)->dibujar(univ()->superficie());

	for(list<Bala*>::iterator i = lista_balas.begin(); i != lista_balas.end(); i++)
		(*i)->dibujar(univ()->superficie());
		
	// Capa superior del nivel	
	nivel->dibujar(univ()->superficie(), 2);
	//cout << "sale de dibujar" << endl;
	
}

void Juego::actualizar_normal()
{
	// Actualizamos posicion de la ventana
	nivel->mover(nivel->nivel_x(), nivel->nivel_y() - 1);
		
		
	// Actualizamos personaje
	if(protagonista != NULL)
		protagonista->actualizar();
	
	// Actualizamos enemigos, items y balas
	for(list<Enemigo*>::iterator i = lista_enemigos.begin(); i != lista_enemigos.end(); i++)
		if(*i != NULL)
			(*i)->actualizar();
	
	//for(list<Item*>::iterator i = lista_items.begin(); i != lista_items.end(); i++)
	//	(i*)->actualizar();
	
	for(list<Bala*>::iterator i = lista_balas.begin(); i != lista_balas.end(); i++)
		(*i)->actualizar();
		
	// Detectamos colisiones
	if(protagonista)
		avisar_colisiones();
		
	// Eliminamos participantes marcados para eliminar
	eliminar_antiguos_enemigos();
	//eliminar_antiguos_items();
	eliminar_antiguas_balas();	
}

void Juego::actualizar()
{
	// Si pulsamos la tecla de salir, salimos al menu
	if(univ()->tecla()->pulso(Teclado::TECLA_SALIR))
		univ()->cambiar_escena(MENU);
	
	// Si terminamos un nivel, pasamos al siguiente, sino hay más vamos al menu
	if(nivel->nivel_y() <= 1){
		nnivel++; // Incrementamos el nivel actual
		// Si hemos llegado al último nivel
		if(nnivel >= nivel->n_niveles()){
			// Ponemos nnivel a 0
			nnivel = 0;
			// Se muestra escena final de juego
			// Le devolvemos el control a Menu
			univ()->transicion()->cargar("finaljuego.xml", univ()->menu);
			univ()->cambiar_escena(Escena::TRANSICION);
		}
		else{
			// Cargamos la transición del siguiente nivel
			univ()->transicion()->cargar_trans_nivel("transfinalnivel", this, nnivel);
			univ()->cambiar_escena(Escena::TRANSICION);
		}
	}	
	else
		actualizar_normal();	
}

bool Juego::colision(Participante *a, Participante *b)
{
	int w1, h1, w2, h2, x1, y1, x2, y2;
	
	for(vector<SDL_Rect>::const_iterator i = a->zona_colision().begin(); i != a->zona_colision().end(); i++){
		w1 = (*i).w;
		h1 = (*i).h;
		x1 = (*i).x + a->pos_x();
		y1 = (*i).y + a->pos_y();
		
		for(vector<SDL_Rect>::const_iterator j = b->zona_colision().begin(); j != b->zona_colision().end(); j++){
			w2 = (*j).w;
			h2 = (*j).h;
			x2 = (*j).x + b->pos_x();
			y2 = (*j).y + b->pos_y();
			
			if(((x1 + w1) > x2) && ((y1 + h1) > y2) && ((x2 + w2) > x1) && ((y2 + h2) > y1)){
				return true;
			}
		}
	}
	
	
	
	return false;
}

/*void Juego::eliminar_antiguos_items()
{
	bool eliminado = false;
	
	for(list<Item*>::iterator i = lista_items.begin(); i != lista_items.end() && !eliminado; i++){
		if((*i)->estado_actual() == ELIMINAR){
			eliminado = true;
			lista_items.erase(i);
		}
	}
}*/

void Juego::eliminar_antiguos_enemigos()
{
	bool eliminado = false;
	
	for(list<Enemigo*>::iterator i = lista_enemigos.begin(); i != lista_enemigos.end() && !eliminado; i++){
		if((*i)->estado_actual() == ELIMINAR){
			cout << "va a eliminar" << endl;
			eliminado = true;
			lista_enemigos.erase(i);
			cout << "elimina" << endl;
		}
	}
	
	if(eliminado)
		cout << "termina de eliminar" << endl;
}

void Juego::eliminar_antiguas_balas()
{
	bool eliminado = false;
	
	for(list<Bala*>::iterator i = lista_balas.begin(); i != lista_balas.end() && !eliminado; i++){
		if((*i)->estado_actual() == ELIMINAR){
			eliminado = true;
			lista_balas.erase(i);
		}
	}
}

void Juego::avisar_colisiones()
{
	// Colisiones con los enemigos
	for(list<Enemigo*>::iterator i = lista_enemigos.begin(); i != lista_enemigos.end(); i++)
		if(colision(protagonista, *i)){
			protagonista->colisiona_con(*i);
			(*i)->colisiona_con(protagonista);
		}

	/*// Colisiones con los items
	for(list<Item*>::iterator i = lista_items.begin(); i != lista_items.end(); i++)
		if(colision(protagonista, *i)){
			protagonista->colisiona_con(*i);
			(*i)->colisiona_con(protagonista);
		}*/
	
	// Colisiones con las balas
	for(list<Bala*>::iterator i = lista_balas.begin(); i != lista_balas.end(); i++){
		// Si la bala va en dirección a los enemigos
		if((*i)->vel_y() < 0){
			for(list<Enemigo*>::iterator j = lista_enemigos.begin(); j != lista_enemigos.end(); j++){
				if(colision(*j, *i) && (*j)->estado_actual() != MORIR && (*j)->estado_actual() != ELIMINAR){
					cout << "Bala impacta a enemigo" << endl;
					(*j)->colisiona_con(*i);
					(*i)->colisiona_con(*j);
				}
			}
		}
		else{
			if(colision(protagonista, *i)){
				cout << "Bala impacta a protagonista" << endl;
				protagonista->colisiona_con(*i);
				(*i)->colisiona_con(protagonista);
			}
		}
		
	}
}

void Juego::add_enemigo(Enemigo *e)
{
	lista_enemigos.push_back(e);
}

//void add_item(Item& i);

void Juego::add_protagonista(Protagonista *p)
{
	if(protagonista != NULL){
		cerr << "Juego::add_protagonista(): Ya existe protagonista" << endl;
		exit(1);
	}
	
	protagonista = p;
}

void Juego::add_bala(Bala *b)
{
	lista_balas.push_back(b);
}


