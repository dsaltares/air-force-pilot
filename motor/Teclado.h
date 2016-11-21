// Listado: Teclado.h
// Control del dispositivo de entrada


#ifndef _TECLADO_H_
#define _TECLADO_H_

#include <SDL/SDL.h>
#include <map>

using namespace std;


class Teclado {

 public:

    // Teclas a usar en la aplicación

    enum teclas_utilizadas {

	TECLA_SALIR,
	TECLA_SUBIR,
	TECLA_BAJAR,
	TECLA_ACEPTAR,
	TECLA_GOLPEAR,
	TECLA_IZQUIERDA,
	TECLA_DERECHA,
	TECLA_SALTAR,
	TECLA_GUARDAR
	
    };

    // Constructor

    Teclado();

    // Consultoras

    // Actualiza la información del teclado

    void actualizar(void);

    // Informa si una tecla ha sido pulsada
    
    bool pulso(teclas_utilizadas tecla);

		
 private:

    // Para conocer el estado de la pulsación
    // de las teclas en todo momento

    Uint8* teclas;


    // Asocia las teclas que necesitamos a la 
    // constate SDL que la representa
    
    map<teclas_utilizadas, SDLKey> teclas_configuradas;
};

#endif 
