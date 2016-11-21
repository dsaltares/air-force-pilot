#ifndef _MENU_
#define _MENU_

#include <iostream>
#include <vector>

#include "escena.h"
#include "opcion.h"

class Universo;
class Imagen;

class Menu: public Escena {
	public:
		/**
			Constructor
			
			Carga en memoria todas las opciones del menu desde un xml
			
			@param universo Puntero a Universo en el que está ubicado menú.
			@param ruta Ruta del XML que contiene las opciones
		*/
		Menu(Universo* universo, const std::string& ruta);
		
		/**
			Destructor
			
			Libera la memoria ocupada por todas las opciones y elementos del menú
		*/
		~Menu();
		
		/**
			Restaura el menú en su estado por defecto
		*/
		void reiniciar();
		
		/**
			Dibuja en pantalla el menú en su estado actual
		*/
		void dibujar();
		
		/**
			Actualiza lógicamente el menú (posición del cursor etc)
		*/
		void actualizar();
		
		/**
			Elije la opción seleccionada en ese momento
			No debe ser llamada a la ligera
		*/
		void seleccionar_opcion();
	private:
		/*
			Debería haber funciones a llamar cuando se pulsa una opción
		*/
		
		std::vector<Opcion*> opciones;
		int opcion_actual;
		Imagen* cursor;
		Imagen* fondo;
		int cur_x, cur_y;
		bool lock;
		
};

#endif
