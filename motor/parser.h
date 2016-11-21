#ifndef _PARSER_
#define _PARSER_

#include "ticpp/ticpp.h"
#include <string>
#include <vector>

//!	Parsea ficheros xml

/**	
	Carga ficheros XML y los parsea utilizando por debajo la librería ticpp
	
	@todo Implementar un sistema de salida, es decir, de escritura en ficheros XML (quizás para guardar la partida)
	
	Ejemplo de uso :
	
	Fichero XML:
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
	
	Código del programa (hace uso de la clase Fuente para el ejemplo
	\code
	#include "parser.h"
	#include "fuente.h"
	#include <vector>
	
	using namespace std;
	
	...
	
	// Declaramos el parser
	Parser p("multimedia.xml");
	
	// Vector para almacenar las fuentes
	vector <Fuente*> fuentes;
	
	// Atributos
	string clave, ruta;
	int puntos;
	
	// Construimos las fuentes
	multimedia.encontrar("fuente", fuentes, multimedia.encontrar("fuentes"));
	for(i = fuentes.begin(); i != fuentes.end(); i++){
		clave = multimedia.atributo("nombre", *i);
		ruta = multimedia.atributo("ruta", *i);
		multimedia.atributo("puntos", *i, &puntos);
		fuentes_[clave] = new Fuente(ruta.c_str(), puntos);
	}
	
	\endcode
*/

class Parser{
	public:
		
		/**
			Constructor
			Carga el fichero xml
			@param fichero Ruta del fichero a ser cargado
		*/
		Parser(const char* fichero);
		
		/**
			Constructor
			Carga el fichero xml
			@param fichero Ruta del fichero a ser cargado
		*/
		Parser(const std::string fichero);
		
		/**
			Consultor
			
			Sólo vale para nodos cuyo contendo sea texto
			
			@param elemento Elemento del que se va a extraer el contenido
			@return Cadena con el contenido del elemento
		*/
		std::string contenido(const ticpp::Element* elemento) const;
		
		/**
			Consultor
			@param nombre Cadena con el nombre del atributo a consultar
			@param elemento Elemento cuyo atributo será consultado
			@return Cadena con el atributo, cadena vacía si el elemento no posee el atributo
		*/
		std::string atributo(const std::string& nombre, const ticpp::Element* elemento) const;
		
		/**
			Consultor
			
			Método para consultar atributos de tipo T (de cualquier tipo para los que se haya definido >>)
			
			@param nombre Nombre del atributo a consultar
			@param elemento Elemento cuyo atributo será consultado
			@param valor puntero a variable de tipo T donde se guardará el atributo
			@return Verdadero con éxito Falso ante fracaso
		*/
		template <typename T>
		bool atributo(const std::string& nombre, const ticpp::Element *elemento, T* valor) const{
			if(elemento){
				try{
					elemento->GetAttribute(nombre, valor);
				}
				catch(ticpp::Exception& e){
					return false;
				}
				return true;
			}
			return false;
		}
		
		/**
			@return Elemento raíz del documento
		*/
		ticpp::Element* raiz() {return documento.FirstChildElement();}
		
		
		/**
			Búsqueda recursiva de un elemento con un determinado nombre.
			@param nombre Nombre del nodo a buscar
			@param inicio Elemento raíz del subárbol que se va a explorar (si se omite se toma la raíz del documento)
			@return Primer elemento con el nombre indicado que se encuentra
		*/
		ticpp::Element* encontrar(const std::string& nombre, ticpp::Element* inicio = 0);
		
		/**
			Búsqueda recursiva de varios elementos con un nombre que se guardan en un vector
			@param nombre Nombre de los nodos a buscar
			@param v Vector de ticpp::Element* donde se guardarán los elementos coincidentes con nombre
			@param inicio Elemento raíz del subárbol que se va a explorar (si se omite se toma la raíz del documento)
			@return Verdadero si se ha encontrado algún elemento, Falso en caso contrario
		*/
		bool encontrar(const std::string& nombre, std::vector<ticpp::Element*>& v, ticpp::Element* inicio = 0);
		
		/**
			Guarda el documento actual
			@param filename Nombre del fichero a guardar
		*/
		bool save(const std::string& filename);
		
		/**
			Crea un elemento con ese nombre al final de la lista de hijos del padre
			@param nombre Nombre del elemento a añadir
			@param padre Padre del elemento a añadir, sino se especifica es la raíz.
		*/
		ticpp::Element* add(const std::string& nombre, ticpp::Element* padre = 0);

		/**
			Crea un atributo con ese nombre y ese valor en un elemento
			Es necesario el operador >> para el valor
			@param nombre Nombre del atributo
			@param valor Valor del atributo a añadir
			@param elemento Elemento al que establecer el atributo			
		*/
		template<typename T>
		    bool establece_atributo(const std::string& nombre, const T& valor, ticpp::Element* elemento){
			if(elemento){
			    try{
				elemento->SetAttribute(nombre,valor);
			    }catch(ticpp::Exception& e){
				return false;
			    }
			    return true;
			}
			return false;
		    }

		/**
			Establece el contenido de un elemento con el valor indicado
			@param valor Valor del contenido del elemento
			@param elemento Elemento al que hay que modificarle el contenido
		*/
		template<typename T>
		    bool establece_contenido(const T& valor, ticpp::Element* elemento){
			if(elemento){
			    try{
				elemento->SetText(valor);
			    }catch(ticpp::Exception& e){
				return false;
			    }
			    return true;
			}
			return false;
		    }
		
	private:
		ticpp::Document documento;
		void encontrar_aux(const std::string& nombre, ticpp::Element* padre, ticpp::Element*& elemento, bool& parada);
		void encontrar_aux(const std::string& nombre, ticpp::Element* padre, std::vector<ticpp::Element*>& v);
};

#endif
