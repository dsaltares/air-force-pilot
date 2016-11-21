#include <vector>
#include <string>
#include "parser.h"
#include "bala.h"
#include "protagonista.h"
#include "juego.h"
#include "universo.h"
#include "sonido.h"
#include "imagen.h"
#include "Teclado.h"
#include "nivel.h"

using namespace std;

Protagonista::Protagonista(Juego *j, const std::string& ruta, int x, int y): Participante(j)
{
	Parser protagonista(ruta);
	
	ticpp::Element* elemento = protagonista.raiz();
	
	// Coordenadas
	this->x = x;
	this->y = y;
	
	string img;
	
	// Atributos
	protagonista.atributo("energia", elemento, &energia_);
	protagonista.atributo("vidas", elemento, &vidas_);
	protagonista.atributo("vx", elemento, &vx);
	protagonista.atributo("vy", elemento, &vy);
	protagonista.atributo("ataque", elemento, &ataque_);
	img = protagonista.atributo("imagen", elemento);
	
	imagen = galeria.imagen(img);
	
	// Cajas de colisión
	SDL_Rect caja_colision;
	vector<ticpp::Element*> colisiones;
	
	protagonista.encontrar("colision", colisiones, protagonista.encontrar("colisiones"));
	
	for(vector<ticpp::Element*>::iterator i = colisiones.begin(); i != colisiones.end(); i++){
		protagonista.atributo("x", *i, &(caja_colision.x));
		protagonista.atributo("y", *i, &(caja_colision.y));
		protagonista.atributo("w", *i, &(caja_colision.w));
		protagonista.atributo("h", *i, &(caja_colision.h));
		cajas_colision.push_back(caja_colision);
	}
	
	// Animaciones
	vector<ticpp::Element*> anim;
	string nombre;
	string animacion;
	int retardo;
	
	protagonista.encontrar("animacion", anim, protagonista.encontrar("animaciones"));
	
	for(vector<ticpp::Element*>::iterator i = anim.begin(); i != anim.end(); i++){
		nombre = protagonista.atributo("nombre", *i);
		animacion = protagonista.atributo("anim", *i);
		protagonista.atributo("retardo", *i, &retardo);
		
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
	disparo = false;
}

Protagonista::~Protagonista()
{
	for(map<enum estados, Control_Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
		delete i->second;
}

void Protagonista::actualizar()
{
	if(estado != estado_anterior){
		estado_anterior = estado;
		animaciones[estado]->reiniciar();
	}
	
	switch (estado){
		case NORMAL:
			estado_normal();
			break;
		case ACELERADO:
			estado_acelerado();
			break;
		case FRENADO:
			estado_frenado();
			break;
		case MORIR:
			estado_morir();
			break;
		default:
			cout << "Protagonista::actualizar(): Estado no contemplado" << endl;
			break;
	}
}

void Protagonista::colisiona_con(Participante *otro)
{
	/*if(estado != MORIR){
		
		energia_--;
		
		if(energia_ <= 0){
			estado = MORIR;
			vidas_--;
		}
		
		// reproducir sonido de ataque
	}*/
	galeria.sonido("expl")->reproducir();
	estado = MORIR;
}


void Protagonista::estado_normal()
{
	animaciones[estado]->avanzar();
	
	y -= 1;
	
	if(juego->univ()->tecla()->pulso(Teclado::TECLA_SUBIR)){
		y -= vy;
		estado = ACELERADO;
		if(y < juego->niv()->nivel_y())
			y = juego->niv()->nivel_y();
	}
	if(juego->univ()->tecla()->pulso(Teclado::TECLA_BAJAR)){
		y += vy - 1;
		estado = FRENADO;
		if(y > juego->niv()->nivel_y() + juego->univ()->pantalla_alto() - imagen->altura())
			y = juego->niv()->nivel_y() + juego->univ()->pantalla_alto() - imagen->altura();
	}
	if(juego->univ()->tecla()->pulso(Teclado::TECLA_DERECHA)){
		x += vx;
		if(x + imagen->anchura() > juego->univ()->pantalla_ancho())
			x = juego->univ()->pantalla_ancho() - imagen->anchura();
	}
	if(juego->univ()->tecla()->pulso(Teclado::TECLA_IZQUIERDA)){
		x -= vx;
		if(x < 0)
			x = 0;
	}
	if(juego->univ()->tecla()->pulso(Teclado::TECLA_GOLPEAR) && disparo){
		// Disparar
		
		galeria.sonido("disp")->reproducir();
		
		Bala *bala1 = new Bala(juego, "bala", x + 26, y + 45, -8, ataque_);
		Bala *bala2 = new Bala(juego, "bala", x + 83, y + 45, -8, ataque_);
		
		
		
		juego->add_bala(bala1);
		juego->add_bala(bala2);
		
		disparo = false;
	}
	if(!juego->univ()->tecla()->pulso(Teclado::TECLA_GOLPEAR)){
		disparo = true;
	}
}

void Protagonista::estado_acelerado()
{
	animaciones[estado]->avanzar();
	
	if(juego->univ()->tecla()->pulso(Teclado::TECLA_SUBIR)){
		y -= vy;
		estado = ACELERADO;
		if(y < juego->niv()->nivel_y())
			y = juego->niv()->nivel_y();
	}
	if(!juego->univ()->tecla()->pulso(Teclado::TECLA_SUBIR)){
		estado = NORMAL;
	}
	if(juego->univ()->tecla()->pulso(Teclado::TECLA_BAJAR)){
		y += vy - 1;
		estado = FRENADO;
		if(y > juego->niv()->nivel_y() + juego->univ()->pantalla_alto() - imagen->altura())
			y = juego->niv()->nivel_y() + juego->univ()->pantalla_alto() - imagen->altura();
	}
	if(juego->univ()->tecla()->pulso(Teclado::TECLA_DERECHA)){
		x += vx;
		if(x + imagen->anchura() > juego->univ()->pantalla_ancho())
			x = juego->univ()->pantalla_ancho() - imagen->anchura();
	}
	if(juego->univ()->tecla()->pulso(Teclado::TECLA_IZQUIERDA)){
		x -= vx;
		if(x < 0)
			x = 0;
	}
	if(juego->univ()->tecla()->pulso(Teclado::TECLA_GOLPEAR) && disparo){
		// Disparar
		
		galeria.sonido("disp")->reproducir();
		
		Bala *bala1 = new Bala(juego, "bala", x + 26, y + 45, -8, ataque_);
		Bala *bala2 = new Bala(juego, "bala", x + 83, y + 45, -8, ataque_);
		
		juego->add_bala(bala1);
		juego->add_bala(bala2);
		
		disparo = false;
	}
	if(!juego->univ()->tecla()->pulso(Teclado::TECLA_GOLPEAR)){
		disparo = true;
	}
}

void Protagonista::estado_frenado()
{
	animaciones[estado]->avanzar();
	
	if(juego->univ()->tecla()->pulso(Teclado::TECLA_SUBIR)){
		y -= vy;
		estado = ACELERADO;
		if(y < juego->niv()->nivel_y())
			y = juego->niv()->nivel_y();
	}
	if(!juego->univ()->tecla()->pulso(Teclado::TECLA_BAJAR)){
		estado = NORMAL;
	}
	if(juego->univ()->tecla()->pulso(Teclado::TECLA_BAJAR)){
		y += vy - 1;
		estado = FRENADO;
		if(y > juego->niv()->nivel_y() + juego->univ()->pantalla_alto() - imagen->altura())
			y = juego->niv()->nivel_y() + juego->univ()->pantalla_alto() - imagen->altura();
	}
	if(juego->univ()->tecla()->pulso(Teclado::TECLA_DERECHA)){
		x += vx;
		if(x + imagen->anchura() > juego->univ()->pantalla_ancho())
			x = juego->univ()->pantalla_ancho() - imagen->anchura();
	}
	if(juego->univ()->tecla()->pulso(Teclado::TECLA_IZQUIERDA)){
		x -= vx;
		if(x < 0)
			x = 0;
	}
	if(juego->univ()->tecla()->pulso(Teclado::TECLA_GOLPEAR) && disparo){
		// Disparar
		
		galeria.sonido("disp")->reproducir();
		
		Bala *bala1 = new Bala(juego, "bala", x + 26, y + 45, -8, ataque_);
		Bala *bala2 = new Bala(juego, "bala", x + 83, y + 45, -8, ataque_);
		
		juego->add_bala(bala1);
		juego->add_bala(bala2);
		
		disparo = false;
	}
	if(!juego->univ()->tecla()->pulso(Teclado::TECLA_GOLPEAR)){
		disparo = true;
	}	
}

void Protagonista::estado_morir()
{
	if(animaciones[estado]->avanzar()){
		// Ya ha muerto quitamos vida
		vidas_--;
		cout << "Vidas: " << vidas_ << endl;
		if(vidas_ > 0){
			juego->reiniciar();
		}
		else
			juego->univ()->terminar();
	}
}

