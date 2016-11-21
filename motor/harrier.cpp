#include <vector>
#include <string>

#include "harrier.h"
#include "parser.h"
#include "bala.h"
#include "juego.h"
#include "universo.h"
#include "sonido.h"
#include "imagen.h"
#include "nivel.h"
#include "galeria.h"

using namespace std;

Harrier::Harrier(Juego* j, const std::string& ruta, int x, int y): Enemigo(j)
{
	Parser harrier(ruta);
	
	ticpp::Element* elemento = harrier.raiz();
	
	// Coordenadas
	this->x = x;
	this->y = y;
	
	contador = 0;
	
	string img;
	
	// Atributos
	harrier.atributo("energia", elemento, &energia_);
	harrier.atributo("vx", elemento, &vx);
	harrier.atributo("vy", elemento, &vy);
	harrier.atributo("ataque", elemento, &ataque_);
	harrier.atributo("cadencia", elemento, &cadencia_);
	img = harrier.atributo("imagen", elemento);
	
	imagen = galeria.imagen(img);
	
	// Cajas de colisión
	SDL_Rect caja_colision;
	vector<ticpp::Element*> colisiones;
	
	harrier.encontrar("colision", colisiones, harrier.encontrar("colisiones"));
	
	for(vector<ticpp::Element*>::iterator i = colisiones.begin(); i != colisiones.end(); i++){
		harrier.atributo("x", *i, &(caja_colision.x));
		harrier.atributo("y", *i, &(caja_colision.y));
		harrier.atributo("w", *i, &(caja_colision.w));
		harrier.atributo("h", *i, &(caja_colision.h));
		cajas_colision.push_back(caja_colision);
	}
	
	// Animaciones
	vector<ticpp::Element*> anim;
	string nombre;
	string animacion;
	int retardo;
	
	harrier.encontrar("animacion", anim, harrier.encontrar("animaciones"));
	
	for(vector<ticpp::Element*>::iterator i = anim.begin(); i != anim.end(); i++){
		nombre = harrier.atributo("nombre", *i);
		animacion = harrier.atributo("anim", *i);
		harrier.atributo("retardo", *i, &retardo);
		
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

Harrier::Harrier(const Harrier& harrier): Enemigo(harrier.juego)
{
	imagen = harrier.imagen;
	x = harrier.x;
	y = harrier.y;
	vx = harrier.vx;
	vy = harrier.vy;
	estado = harrier.estado;
	estado_anterior = harrier.estado_anterior;
	
	// Tenemos que recorrer el map de animaciones e ir copiando una a una las animaciones
	for(Animaciones::const_iterator i = harrier.animaciones.begin(); i != harrier.animaciones.end(); i++)
		animaciones[i->first] = new Control_Animacion(*(i->second));
	
	cajas_colision = harrier.cajas_colision;
	cadencia_ = harrier.cadencia_;
	energia_ = harrier.energia_;
	ataque_ = harrier.ataque_;
	contador = harrier.contador;
}

Harrier::~Harrier()
{
	for(map<enum estados, Control_Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
		delete i->second;
}

void Harrier::actualizar()
{
	// Si está en pantalla lo movemos
		// Va hacia un lado, si llega a un extremo de la pantalla cambia de direccion
		// Si la cadencia lo permite dispara
	if(estado != MORIR && estado != ELIMINAR && this->esta_en_pantalla()){
		
		x += vx;
		if((x /*+ this->imagen->anchura()*/) < 0 || (x + this->imagen->anchura()) > 800){
			
			cout << "Cambio de sentido" << endl;
			
			if(vx > 0)
				x = 800 - this->imagen->anchura();
			else
				x = 0;
			
			vx = vx * (-1);
		}
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

void Harrier::colisiona_con(Participante *otro)
{
	/*if(estado != MORIR){
		
		/*if(ArticuloAlmacenable *a = dynamic_cast<ArticuloAlmacenable*>(i->first))
		
		energia_ -= otro->ataque();
		
		if(harrier 
		
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

Harrier* Harrier::copia()
{
	Harrier* harrier = new Harrier(*this);
	
	return harrier;
}


