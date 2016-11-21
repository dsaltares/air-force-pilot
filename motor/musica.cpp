#include <iostream>
#include "musica.h"

using namespace std;

Musica::Musica(const char* ruta)
{
	// Cargamos la canción indicada por ruta
	if((musica = Mix_LoadMUS(ruta)) == NULL){
		cerr << "Musica::Musica(): " << Mix_GetError() << endl;
		exit(1);
	}
}

void Musica::reproducir()
{
	// Si está en pausa reanudamos y sino la iniciamos
	if(Mix_PausedMusic())
		Mix_ResumeMusic();
	else
		if(Mix_PlayMusic(musica, -1) == -1){
			cerr << "Musica::reproducir(): " << Mix_GetError() << endl;
			exit(1);
		}
}

void Musica::pausar()
{
	Mix_PauseMusic();	
}

void Musica::parar()
{
	Mix_HaltMusic();
}

Musica::~Musica()
{
	Mix_FreeMusic(musica);
}

