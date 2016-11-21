
#include <iostream>
#include <string>

#include "menu.h"
#include "imagen.h"
#include "sonido.h"
#include "musica.h"
#include "universo.h"
#include "galeria.h"
#include "parser.h"
#include "escena.h"
#include "transicion.h"

using namespace std;

Menu::Menu(Universo* universo, const std::string& ruta): Escena(universo)
{
	Parser parser(ruta);
	
	// Obtenemos las imágenes de fondo y del cursor
	string clave_fondo = parser.atributo("fondo", parser.raiz());
	string clave_cursor = parser.atributo("cursor", parser.raiz());
	cursor = galeria.imagen(clave_cursor);
	fondo = galeria.imagen(clave_fondo);
	
	// Tenemos que meter todas las opciones en un vector
	vector<ticpp::Element*> v_opciones;
	parser.encontrar("opcion", v_opciones);
	
	int x, y, r1, g1, b1, r2, g2, b2;
	string texto, fuente;
	// Recorremos el vector y creamos las opciones
	for(vector<ticpp::Element*>::iterator i = v_opciones.begin(); i != v_opciones.end(); i++){
		texto = parser.atributo("texto", *i);
		fuente = parser.atributo("fuente", *i);
		parser.atributo("r1", *i, &r1);
		parser.atributo("g1", *i, &g1);
		parser.atributo("b1", *i, &b1);
		parser.atributo("r2", *i, &r2);
		parser.atributo("g2", *i, &g2);
		parser.atributo("b2", *i, &b2);
		parser.atributo("x", *i, &x);
		parser.atributo("y", *i, &y);
		
		opciones.push_back(new Opcion(texto, galeria.fuente(fuente), x, y, r1, g1, b1, r2, g2, b2));
	}
	
	opcion_actual = 0;
	cur_x = cur_y = 0;
	lock = false;
}

Menu::~Menu()
{
	// Eliminamos las opciones
	for(vector<Opcion*>::iterator i = opciones.begin(); i != opciones.end(); i++)
		delete (*i);
}

void Menu::reiniciar()
{
	opcion_actual = 0;
	galeria.musica("menu")->reproducir();
	lock = false;
}

void Menu::dibujar()
{
	int contador = 0;
	
	// Dibujamos el fondo
	fondo->dibujar(univ()->superficie(), 0, 0, 0);
	
	// Dibujamos todas las opciones
	for(vector<Opcion*>::iterator i = opciones.begin(); i != opciones.end(); i++){
		(*i)->dibujar(univ()->superficie(), opcion_actual == contador);
		contador++;
	}

	// Dibujamos el cursor
	cursor->dibujar(univ()->superficie(), 0, cur_x, cur_y); 
}

void Menu::actualizar()
{
	// Según las pulsaciones del teclado hacemos una cosa u otra
	if(univ()->tecla()->pulso(Teclado::TECLA_SUBIR) && !lock){
		// Reproducir sonido mover cursor
		galeria.sonido("click")->reproducir();	
		opcion_actual--;
		if(opcion_actual < 0)
			opcion_actual = opciones.size() - 1;
		lock = true;	
	}
	else if(univ()->tecla()->pulso(Teclado::TECLA_BAJAR) && !lock){
		// Reproducir sonido mover cursor
		galeria.sonido("click")->reproducir();
		opcion_actual++;
		if(opcion_actual >= opciones.size())
			opcion_actual = 0;
		lock = true;
	}
	else if(!univ()->tecla()->pulso(Teclado::TECLA_BAJAR) && !univ()->tecla()->pulso(Teclado::TECLA_SUBIR))
		lock = false;
	
	cur_x = opciones[opcion_actual]->pos_x() - 120; // Números mágicos para centrar el cursor
	cur_y = opciones[opcion_actual]->pos_y() - 26;
	
	
	// ELEGIR UNA OPCIÓN
	if(univ()->tecla()->pulso(Teclado::TECLA_ACEPTAR))
		seleccionar_opcion();
}


void Menu::seleccionar_opcion()
{
	// Reproducir sonido aceptar
	galeria.sonido("aceptar")->reproducir();
	// Espera de 1seg
	SDL_Delay(1000);
	
	if(opciones[opcion_actual]->texto() == "Jugar"){
		//univ()->transicion()->cargar("gameover.xml", this);
		univ()->cambiar_escena(Escena::JUEGO);
	}
	else if(opciones[opcion_actual]->texto() == "Salir")
		univ()->terminar();
}
