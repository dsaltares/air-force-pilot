#ifndef _TRANSICION_
#define _TRANSICION_

#include <string>
#include <vector>

#include "escena.h"
#include "galeria.h"
#include "imagen.h"
#include "fuente.h"
#include "texto.h"

//! Clase hija de Escena utilizada para transiciones entre otras escenas

/**
	Transicion carga un fichero XML con las líneas de texto, el fondo que se mostrarán y la música que sonará.
	Sirve para mostrar pantallas del tipo (NIVEL 1 -START!-)
	Contiene información de la escena que la llamó para volver a ella cuando se pulse la tecla ESC
	
	Ejemplo de uso:
	
	\code
	// Estamos en la función actualizar de la clase Juego y hemos detectado que se ha completado el nivel
	universo->crear_transicion("nivel_completado.xml", this); // Debemos poder volver
	universo_->cambiar_escena(Escena::TRANSICION);
	// En la función actualizar de Transición se comprueba la pulsación de ESC.
	// Cuando se pulse se vuelve a la escena que se pretendía
	\endcode
	
	"nivel_completado.xml" podría contener:
	\code
	<transicion fondo="cielo" musica="victoria">
		<Elemento x="300" y="250" texto="¡HAS COMPLETADO ESTE NIVEL!" fuente="stencil" r="0" g="0" b="0"/>
		<Elemento x="300" y="320" texto="Ya queda menos para el final" fuente="stencil" r="0" g="0" b="0"/>
		<Elemento x="300" y="430" texto="Pulsa ESC para continuar" fuente="stencil" r1="0" g1="0" b1="0" r="0" g="0" b="0"/>
	</transicion>
	\endcode
*/

class Transicion: public Escena{
	public:
		/**
			Constructor
			
			Crea una escena asociada a un universo que aún no se puede utilizar, es necesario cargarle un fichero
			
			@param universo Universo al que se asocia la escena de transición
		*/
		Transicion(Universo* universo);
		
		/**
			Destructor
			
			Libera la memoria ocupada por la Transición
		*/
		~Transicion();
		
		/**
			Reinicia la transición
		*/
		void reiniciar();
		
		/**
			Actualiza lógicamente la transición (consulta si se quiere salir)
		*/
		void actualizar();
		
		/**
			Dibuja en la pantalla la transición con todos sus elementos
		*/
		void dibujar();
		
		/**
			Carga el fichero XML indicado por ruta para posteriormente pasar a Escena Transicion
			
			@param ruta Ruta del fichero XML
			@param p Puntero a Escena para que la transición sepa a quién tiene que devolver el control
		*/
		void cargar(const std::string& ruta, Escena* p);
		
		/**
			Carga el fichero XML indicado por ruta para posteriormente pasar a Escena Transicion
			Sirve para poner transiciones relacionadas con un nivel en sí
			
			Las rutas estarán formadas por una base, un nivel y una extensión. Ejemplo:
			
			"trans_inicio_nivel" + "1" + ".xml"
			
			@param ruta_base Ruta base del fichero XML.
			@param nivel Nivel de la que se quiere cargar la transición.
			@param p Puntero a Escena para que la transición sepa a quién tiene que devolver el control
		*/
		void cargar_trans_nivel(const std::string& ruta_base, Escena* p, int nivel);
	private:
	
		void limpiar();
		
		Escena *padre;
		Imagen *fondo;
		Musica *musica;
		std::vector<Texto*> textos;
};

#endif
