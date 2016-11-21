#include <iostream>
#include "universo.h"
#include "juego.h"
#include "menu.h"
#include "galeria.h"
#include "parser.h"

Universo::Universo(const char *ruta)
{
	Parser configuracion(ruta);
	
	iniciar_ventana(false);
	
	// Leer configuracion con el parser...
	configuracion.atributo("ancho", configuracion.encontrar("pantalla"), &ancho);
	configuracion.atributo("alto", configuracion.encontrar("pantalla"), &alto);
	configuracion.atributo("valor", configuracion.encontrar("fps"), &maxfps);
	configuracion.atributo("valor", configuracion.encontrar("bpp"), &bpp);

	juego = new Juego(this);
	menu = new Menu(this, "XML/menu.xml");
	transicion_ = new Transicion(this);
	salir = false;
	actual = menu;
	cambiar_escena(Escena::MENU);
	
	crono.activar();	
}

void Universo::bucle_principal(void)
{
	
	while(salir == false){
		SDL_FillRect(pantalla, NULL, SDL_MapRGB(pantalla->format, 0, 0, 0)); // Rellenamos de negro
		procesar_eventos();
		teclado.actualizar(); // Estado del teclado
		actual->actualizar(); // Actualizamos lógicamente la escena
		actual->dibujar(); // Actualizamos gráficamente la pantalla
		SDL_Flip(pantalla);
		sincronizar_fps();
	}
}

Universo::~Universo()
{
	//delete menu;
	delete juego;
}

void Universo::iniciar_ventana(bool completa)
{
	int flags = 0;
	
	// Iniciamos todos los subsistemas
	if(SDL_Init(0) < 0) {
		cerr << "Universo::iniciar_ventana():" << SDL_GetError() << endl;
		exit(1);
	}

	// Al salir, cerramos libSDL
	atexit(SDL_Quit);
	
	if(completa)
		flags |= SDL_FULLSCREEN;
		
	flags |= SDL_HWSURFACE | SDL_DOUBLEBUF;

	// Establecemos el modo de video

	pantalla = SDL_SetVideoMode(800, 600, 32, flags);

	if(pantalla == NULL) {
		cerr << "Universo::iniciar_ventana:" << SDL_GetError() << endl;
		exit(1);
	}

	SDL_WM_SetCaption("Air Force Pilot", NULL);

	// Ocultamos el cursor
	SDL_ShowCursor(SDL_DISABLE);

	// Inicializamos la librería SDL_Mixer
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT,\
                     1, 2048) < 0) {
		cerr << "Subsistema de Audio no disponible" << endl;
		exit(1);
	}
	
	// Al salir cierra el subsistema de audio
	atexit(Mix_CloseAudio);

	// Inicializamos la librería SDL_ttf
	TTF_Init();
	
	// Al salir cerramos el subsistema de texto
	atexit(TTF_Quit);
}

void Universo::pantalla_completa()
{
	SDL_WM_ToggleFullScreen(pantalla);
}

void Universo::procesar_eventos(void)
{
	static SDL_Event event; // Con "memoria"
	
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				salir = true;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_q)
					salir = true;
				if(event.key.keysym.sym == SDLK_f)
					pantalla_completa();
				break;
		}
	}
}

void Universo::sincronizar_fps()
{	    
	if(crono.tiempo() < (1000/maxfps))
		SDL_Delay((1000/maxfps) - crono.tiempo());
	
	crono.activar();
}


void Universo::cambiar_escena(Escena::escenas nueva)
{
	Escena *anterior = actual;
	
	switch(nueva){
		case Escena::JUEGO:
			actual = juego;
			break;
		case Escena::MENU:
			actual = menu;
			break;
		case Escena::TRANSICION:
			actual = transicion_;
			break;
	}
	
	actual->reiniciar();
}

