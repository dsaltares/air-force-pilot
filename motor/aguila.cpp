#include <vector>
#include <string>

#include "aguila.h"
#include "parser.h"
#include "bala.h"
#include "juego.h"
#include "universo.h"
#include "sonido.h"
#include "imagen.h"
#include "nivel.h"
#include "galeria.h"


Aguila::Aguila(Juego *j, const std::string& ruta, int x, int y): Enemigo(j)
{
	Parser aguila(ruta);
	
	ticpp::Element* elemento = aguila.raiz();
	
	// Coordenadas
	this->x = x;
	this->y = y;
	
	contador = 0;
	
	string img;
	
	// Atributos
	aguila.atributo("energia", elemento, &energia_);
	aguila.atributo("vx", elemento, &vx);
	aguila.atributo("vy", elemento, &vy);
	aguila.atributo("ataque", elemento, &ataque_);
	aguila.atributo("cadencia", elemento, &cadencia_);
	img = aguila.atributo("imagen", elemento);
	
	imagen = galeria.imagen(img);
	
	// Cajas de colisión
	SDL_Rect caja_colision;
	vector<ticpp::Element*> colisiones;
	
	aguila.encontrar("colision", colisiones, aguila.encontrar("colisiones"));
	
	for(vector<ticpp::Element*>::iterator i = colisiones.begin(); i != colisiones.end(); i++){
		aguila.atributo("x", *i, &(caja_colision.x));
		aguila.atributo("y", *i, &(caja_colision.y));
		aguila.atributo("w", *i, &(caja_colision.w));
		aguila.atributo("h", *i, &(caja_colision.h));
		cajas_colision.push_back(caja_colision);
	}
	
	// Animaciones
	vector<ticpp::Element*> anim;
	string nombre;
	string animacion;
	int retardo;
	
	aguila.encontrar("animacion", anim, aguila.encontrar("animaciones"));
	
	for(vector<ticpp::Element*>::iterator i = anim.begin(); i != anim.end(); i++){
		nombre = aguila.atributo("nombre", *i);
		animacion = aguila.atributo("anim", *i);
		aguila.atributo("retardo", *i, &retardo);
		
		if(nombre == "normal")
			animaciones[NORMAL] = new Control_Animacion(animacion.c_str(), retardo);
		else if(nombre == "acelerado")
			animaciones[ACELERADO] = new Control_Animacion(animacion.c_str(), retardo);
		else if(nombre == "frenado")
			animaciones[FRENADO] = new Control_Animacion(animacion.c_str(), retardo);
		else if(nombre == "morir")
			animaciones[MORIR] = new Control_Animacion(animacion.c_str(), retardo);
		else if(nombre == "eliminar")
			animaciones[ELIMINAR] = new Control_Animacion(animacion.c_str(), retardo);
	}
	
	estado = estado_anterior = NORMAL;
	
}

Aguila::Aguila(const Aguila& aguila): Enemigo(aguila.juego)
{
	imagen = aguila.imagen;
	x = aguila.x;
	y = aguila.y;
	vx = aguila.vx;
	vy = aguila.vy;
	estado = aguila.estado;
	estado_anterior = aguila.estado_anterior;
	
	// Tenemos que recorrer el map de animaciones e ir copiando una a una las animaciones
	for(Animaciones::const_iterator i = aguila.animaciones.begin(); i != aguila.animaciones.end(); i++)
		animaciones[i->first] = new Control_Animacion(*(i->second));
	
	cajas_colision = aguila.cajas_colision;
	cadencia_ = aguila.cadencia_;
	energia_ = aguila.energia_;
	ataque_ = aguila.ataque_;
	contador = aguila.contador;
}

Aguila::~Aguila()
{
	for(map<enum estados, Control_Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
		delete i->second;
}

void Aguila::actualizar()
{
	// Si está en pantalla se desplaza hacia abajo y dispara
	if(estado != MORIR && estado != ELIMINAR && this->esta_en_pantalla()){
		y += vy;
		
		if(contador >= cadencia_){
			// Disparar
		
			galeria.sonido("disp")->reproducir();
		
			Bala *bala1 = new Bala(juego, "bala", x + 21, y + 59, 4, ataque_);
			Bala *bala2 = new Bala(juego, "bala", x + 103, y + 59, 4, ataque_);
		
			juego->add_bala(bala1);
			juego->add_bala(bala2);
			
			contador = 0;
		}
		else
			contador++;
	}
	else if(estado == MORIR){
		if(animaciones[estado]->avanzar()){
			cout << "Cuadro: " << animaciones[estado]->cuadro_actual() << endl;
			estado = ELIMINAR;
		}
	}
}

void Aguila::colisiona_con(Participante *otro)
{
	estado = MORIR;
}

Aguila* Aguila::copia()
{
	Aguila* aguila = new Aguila(*this);
	
	return aguila;
}

