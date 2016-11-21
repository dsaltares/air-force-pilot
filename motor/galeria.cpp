#include <iostream>
#include <vector>
#include "imagen.h"
#include "sonido.h"
#include "musica.h"
#include "fuente.h"
#include "galeria.h"
#include "parser.h"


using namespace std;

Galeria::GaleriaPtr& Galeria::get_instance()
{
	static GaleriaPtr la_galeria(new Galeria);
	
	return la_galeria;
}

Galeria& Galeria::Instanciar()
{
	return *get_instance();
}

Galeria::Galeria()
{
	vector<ticpp::Element*> recursos;
	vector<ticpp::Element*>::iterator i;
	string clave, ruta;
	int filas, columnas, puntos;
	
	Parser multimedia("./multimedia/multimedia.xml");
	
	new TDestructor<Galeria>(this, DestructionPhase(2));
	
	// Construimos las imagenes
	multimedia.encontrar("imagen", recursos, multimedia.encontrar("imagenes"));
	for(i = recursos.begin(); i != recursos.end(); i++){
		clave = multimedia.atributo("nombre", *i);
		ruta = multimedia.atributo("ruta", *i);
		multimedia.atributo("filas", *i, &filas);
		multimedia.atributo("columnas", *i, &columnas);
		imagenes_[clave] = new Imagen(ruta.c_str(), filas, columnas);
	}
	
	recursos.clear();
		
	// Construimos los sonidos
	multimedia.encontrar("sonido", recursos, multimedia.encontrar("sonidos"));
	for(i = recursos.begin(); i != recursos.end(); i++){
		clave = multimedia.atributo("nombre", *i);
		ruta = multimedia.atributo("ruta", *i);
		sonidos_[clave] = new Sonido(ruta.c_str());
	}
	
	recursos.clear();
	
	// Construimos las musicas
	multimedia.encontrar("musica", recursos, multimedia.encontrar("musicas"));
	for(i = recursos.begin(); i != recursos.end(); i++){
		clave = multimedia.atributo("nombre", *i);
		ruta = multimedia.atributo("ruta", *i);
		musicas_[clave] = new Musica(ruta.c_str());
	}
	
	recursos.clear();
	
	// Construimos las fuentes
	multimedia.encontrar("fuente", recursos, multimedia.encontrar("fuentes"));
	for(i = recursos.begin(); i != recursos.end(); i++){
		clave = multimedia.atributo("nombre", *i);
		ruta = multimedia.atributo("ruta", *i);
		multimedia.atributo("puntos", *i, &puntos);
		fuentes_[clave] = new Fuente(ruta.c_str(), puntos);
	}
}

Galeria::~Galeria()
{
	// Destruimos las imagenes
	for(Imagenes::iterator i = imagenes_.begin(); i != imagenes_.end(); i++)
		delete i->second;

	// Destruimos los sonidos
	for(Sonidos::iterator i = sonidos_.begin(); i != sonidos_.end(); i++)
		delete i->second;
	
	// Destruimos las musicas
	for(Musicas::iterator i = musicas_.begin(); i != musicas_.end(); i++)
		delete i->second;
		
	// Destruimos las fuentes
	for(Fuentes::iterator i = fuentes_.begin(); i != fuentes_.end(); i++)
		delete i->second;
}

