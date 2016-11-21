#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include "transicion.h"
#include "juego.h"
#include "menu.h"
#include "parser.h"
#include "universo.h"
#include "Teclado.h"
#include "musica.h"

using namespace std;



Transicion::Transicion(Universo* universo): Escena(universo)
{
	fondo = NULL;
	musica = NULL;
	padre = NULL;
}

Transicion::~Transicion()
{
	for(vector<Texto*>::iterator i = textos.begin(); i != textos.end(); i++)
		delete (*i);
}

void Transicion::reiniciar()
{
	
}

void Transicion::actualizar()
{
	if(univ()->tecla()->pulso(Teclado::TECLA_SALIR)){
		// Devolver el control a la escena padre
		// Hay que saber de qué tipo era la escena
		if(Juego *j = dynamic_cast<Juego*>(padre)){
			padre = NULL;
			univ()->cambiar_escena(Escena::JUEGO);
		}
		else if(Menu *j = dynamic_cast<Menu*>(padre)){
			padre = NULL;
			univ()->cambiar_escena(Escena::MENU);
		}
	}
}

void Transicion::dibujar()
{
	// Dibujamos el fondo
	fondo->dibujar(univ()->superficie(), 0, 0, 0);
	
	// Dibujamos los textos
	for(vector<Texto*>::iterator i = textos.begin(); i != textos.end(); i++)
		(*i)->dibujar(univ()->superficie());
}

void Transicion::cargar(const std::string& ruta, Escena* p)
{	
	limpiar();
	
	Parser parser(ruta);
	
	
	padre = p;
	// Obtenemos las imágenes de fondo y de la musica
	string clave_fondo = parser.atributo("fondo", parser.raiz());
	string clave_musica = parser.atributo("musica", parser.raiz());
	musica = galeria.musica(clave_musica);
	fondo = galeria.imagen(clave_fondo);
	
	// Tenemos que meter todos los textos en un vector
	vector<ticpp::Element*> v_lineas;
	parser.encontrar("linea", v_lineas);
	
	SDL_Rect rect;
	int r, g, b;
	string texto, fuente;
	rect.w = rect.h = 1000;
	// Recorremos el vector y creamos las opciones
	for(vector<ticpp::Element*>::iterator i = v_lineas.begin(); i != v_lineas.end(); i++){
		texto = parser.atributo("texto", *i);
		fuente = parser.atributo("fuente", *i);
		parser.atributo("r", *i, &r);
		parser.atributo("g", *i, &g);
		parser.atributo("b", *i, &b);
		parser.atributo("x", *i, &(rect.x));
		parser.atributo("y", *i, &(rect.y));
		textos.push_back(new Texto(galeria.fuente(fuente), r, g, b, rect, texto));
	}
	
	// Aquí es donde debería reproducirse la música
	musica->reproducir();		
}

void Transicion::cargar_trans_nivel(const std::string& ruta_base, Escena* p, int nivel)
{
	char buffer[5];
	
	sprintf(buffer, "%d", nivel);
	
	string ruta;
	ruta = ruta_base + string(buffer) + string(".xml");
	
	cargar(ruta, p);
}

void Transicion::limpiar()
{
	for(vector<Texto*>::iterator i = textos.begin(); i != textos.end(); i++)
		delete (*i);
	
	textos.clear();
	
	fondo = NULL;
	musica = NULL;
	padre = NULL;
		
}

