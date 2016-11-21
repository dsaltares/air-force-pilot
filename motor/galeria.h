#ifndef _GALERIA_
#define _GALERIA_

// Declaraciones adelantadas

#include <memory>
#include <map>
#include <string>

#include "dphase.h"
#include "destructor.h"

class Imagen;
class Sonido;
class Musica;
class Fuente;


/**
	@typedef Imagenes
	Diccionario que relaciona una clave (string) con un puntero a Imagen.
	Facilita el acceso a los recursos.
*/
typedef std::map<std::string, Imagen*> Imagenes;

/**
	@typedef Sonidos
	Diccionario que relaciona una clave (string) con un puntero a Sonido.
	Facilita el acceso a los recursos.
*/
typedef std::map<std::string, Sonido*> Sonidos;

/**
	@typedef Musicas
	Diccionario que relaciona una clave (string) con un puntero a Musica.
	Facilita el acceso a los recursos.
*/
typedef std::map<std::string, Musica*> Musicas;

/**
	@typedef Fuentes
	Diccionario que relaciona una clave (string) con un puntero a Fuente.
	Facilita el acceso a los recursos.
*/
typedef std::map<std::string, Fuente*> Fuentes;

//!	Gestor de recursos multimedia, emplea el patrón Singleton

/**	
	Utiliza las clases Imagen, Sonido, Musica y Fuente y se utiliza para manejar todos los recursos multimedia del juego.
	Si tenemos 50 enemigos del tipo caza no necesitamos tener 50 rejillas cargadas en memoria, simplemente guardamos referencias.
	Los recursos se guardan en la galeria y en el exterior se mantienen referencias a ellos.
	
	Se trata de una clase de tipo Singleton, sólo puede haber una instancia suya en el sistema.
	Además, podrá ser utilizada en cualquier módulo del programa.
	
	Galeria lee el fichero "./../multimedia/multimedia.xml" para saber qué recursos tiene que cargar. Dicho fichero tiene el siguiente formato:
	
	\code
	<galeria>

		<imagenes>
			<imagen nombre="avion" ruta="multimedia/avion-normal-acelerado-p.png" filas="1" columnas="1"/>
		</imagenes>
	
		<fuentes>
			<fuente nombre="comic" ruta="multimedia/comic.ttf" puntos="12"/>
			<fuente nombre="arial" ruta="multimedia/arial.ttf" puntos="12"/>
			<fuente nombre="times" ruta="multimedia/times.ttf" puntos="12"/>
		</fuentes>
	
		<sonidos>
			<sonido nombre="muere" ruta="multimedia/muere.wav"/>
		</sonidos>
	
		<musicas>
			<musica nombre="juego" ruta="multimedia/juego.wav"/>
		</musicas>
	
	</galeria>
	\endcode
	
	Los recursos se acceden mediante una cadena, mejor mirar el siguiente ejemplo.
	
	Ejemplo de uso :
	\code
	#include "galeria.h"
	
	...
	
	// Se supone SDL inicializado al completo
	SDL_Surface *pantalla;
	
	// No tenemos que crear una instancia, ya que existe:
	// #define galeria Galeria::Instanciar()
	
	// Puntero a imagen a la que se le asocia 
	Imagen *avion = galeria.imagen("avion");
	
	avion->dibujar(pantalla, 0, 100, 100);
	
	SDL_Flip(pantalla);
	
	\endcode
*/

class Galeria{
	public:
		
		/**
			Devuelve una referencia a la única instancia posible de Galeria. Si no existe, la crea.
			No es necesario llamar a su destructor (de hecho es privado), la memoria se libera cuando termina el programa.
			
			@return Referencia a la única instancia de Galeria que puede existir en el sistema
		*/
		static Galeria& Instanciar();
		
		/**
			@return Devuelve un map<const string&, Imagen*> con las imágenes asociadas a claves
		*/
		Imagenes& imagenes();
		
		/**
			@return map<const string&, Sonido*> con los sonidos asociadas a claves
		*/
		Sonidos& sonidos();
		
		/**
			@return map<const string&, Musica*> con las músicas asociadas a claves
		*/
		Musicas& musicas();
		
		/**
			@return map<const string&, Fuente*> con las fuentes asociadas a claves
		*/
		Fuentes& fuentes();
		
		/**
			Permite acceder a una Imagen dada una clave
			
			@param clave Cadena que identifica a una Imagen dentro del diccionario de imágenes
			@return Puntero a Imagen correspondiente
		*/
		Imagen* imagen(std::string clave);
		
		/**
			Permite acceder a un Sonido dada una clave
			
			@param clave Cadena que identifica a un Sonido dentro del diccionario de sonidos
			@return Puntero a Sonido correspondiente
		*/
		Sonido* sonido(std::string clave);
		
		/**
			Permite acceder a una Música dada una clave
			
			@param clave Cadena que identifica a una Musica dentro del diccionario de músicas
			@return Puntero a Musica correspondiente
		*/
		Musica* musica(std::string clave);
		
		/**
			Permite acceder a una Fuente dada una clave
			
			@param clave Cadena que identifica a una Fuente dentro del diccionario de fuentes
			@return Puntero a Fuente correspondiente
		*/
		Fuente* fuente(std::string clave);
		
	private:
	
		Galeria();
		~Galeria();
		Galeria(const Galeria&);
		Galeria& operator = (const Galeria&);
		
		typedef auto_ptr<Galeria> GaleriaPtr;
		
		static GaleriaPtr& get_instance();
		static void destroy_instance(){delete get_instance().release();}
		
		friend class auto_ptr<Galeria>;
		friend class TDestructor<Galeria>;
		
		Imagenes imagenes_;
		Sonidos sonidos_;
		Musicas musicas_;
		Fuentes fuentes_;
};

/**
	@def galeria
	Permite acceder más fácilmente a la instancia única de Galeria:
	\code
	galeria.imagen("avion")->dibujar(pantalla, 0, 100, 100);
	\endcode
*/
#define galeria Galeria::Instanciar()

inline Imagenes& Galeria::imagenes(){return imagenes_;}
inline Sonidos& Galeria::sonidos(){return sonidos_;}
inline Musicas& Galeria::musicas(){return musicas_;}
inline Fuentes& Galeria::fuentes(){return fuentes_;}


inline Imagen* Galeria::imagen(std::string clave) {return imagenes_[clave];}
inline Sonido* Galeria::sonido(std::string clave) {return sonidos_[clave];}
inline Musica* Galeria::musica(std::string clave) {return musicas_[clave];}
inline Fuente* Galeria::fuente(std::string clave) {return fuentes_[clave];}

#endif

