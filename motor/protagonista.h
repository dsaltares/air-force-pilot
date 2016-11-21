#ifndef _PROTAGONISTA_
#define _PROTAGONISTA_

#include <string>
#include "participante.h"


/*
	Hay que añadir consultores y modificadores para:
		vida
		
*/


//! Clase descendiente de Participante que controla la lógica y la gestión del protagonista

/**
	Sirve para cargar las características de un fichero xml del Protagonista del juego así como para actualizarlo y gestionar las colisiones.
	
	Veamos un ejemplo de su uso:
	
	\code
		#include "protagonista.h"
		
		Protagonista avion("protagonista.xml");
		
		// Bucle de juego
		while(juego){
			avion.actualizar();
			comprobar_colisiones() // Función inventada para calcular las colisiones
			avion.dibujar(pantalla);
		}	
	\endcode
	
	\code
		// Función imaginaria, de esto se encarga la clase Control
		void comprobar_colisiones(){
			if(colisionan(protagonista, otro))
				protagonista.colisiona_con(otro); // Para restarle vida por ejemplo
		}
	\endcode
*/

class Protagonista: public Participante{
	public:
		
		/**
			Constructor
			
			@param j Escena de Juego con el que se asocia el Protagonista
			@param ruta Ruta del fichero de las características del Protagonista
			@param x Coordenada x del Protagonista
			@param y Coordenada y del Protagonista
			
			Abre el fichero indicado del que se extraen los datos y las características del protagonista. Ejemplo:
		
			\code
				<protagonista vx="5" vy="3" energia="4" ataque="2" vidas="3">
					<colisiones>
						<colision x="51" y="0" w="14" h="129" />
						<colision x="27" y="40" w="63" h="18" />
						<colision x="2" y="57" w="112" h="45" />
					</colisiones>
					<animaciones>
						<animacion nombre="normal" anim="1"/>
						<animacion nombre="acelerado" anim="0"/>
						<animacion nombre="frenado" anim="2"/>
					</animaciones>
				</protagonista>
			\endcode
			
			A medida que aumentan los cuadros de colisión disminuye el rendimiento
		*/
		Protagonista(Juego *j, const std::string& ruta, int x = 0, int y = 0);
		
		/**
			Destructor
			
			Destruye la memoria ocupada por el protagonista
		*/
		~Protagonista();
		
		
		/**
			Actualiza el protagonista según su lógica. Debe llamarse a esta función en cada iteración del bucle del juego
		*/
		void actualizar();
		
		/**
			Función a llamar cuando un enemigo colisiona con el Protagonista. Recalcula los atributos del protagonista en función de los del enemigo.
			
			@param otro Puntero al Participante con el que colisiona
		*/
		void colisiona_con(Participante *otro);
		
		/**
			Método consultor
			
			@return Energía del protagonista, su vida.
		*/
		int energia() const;
		
		/**
			Modificador
			
			@param diferencia Cantidad a sumársele a la energía del protagonista.
		*/
		void energia(int diferencia);
		
		/**
			Método consultor
			
			@return Daño que hace el protagonista cuando impactan sus balas sobre un enemigo
		*/
		int ataque() const;
		
		/**
			Metodo consultor
			
			@return Número de vidas del protagonista
		*/
		int vidas() const;
		
		/**
			Modificador
			
			@param diferencia Cantidad a sumársele al número de vidas del protagonista.
		*/
		void vidas(int diferencia);
		
	private:
		int energia_, vidas_, ataque_;
		
		bool disparo;
		
		void estado_normal();
		void estado_acelerado();
		void estado_frenado();
		void estado_morir();
};

inline int Protagonista::energia()const {return energia_;}
inline void Protagonista::energia(int diferencia) {energia_ += diferencia;}
inline int Protagonista::ataque()const {return ataque_;}
inline int Protagonista::vidas() const {return vidas_;}
inline void Protagonista::vidas(int diferencia){vidas_ += diferencia;}

#endif

