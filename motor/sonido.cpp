#include <iostream>
#include "sonido.h"

using namespace std;

Sonido::Sonido(const char* ruta)
{
	if((sonido = Mix_LoadWAV(ruta)) == NULL){
		cerr << "Sonido::Sonido(): " << Mix_GetError() << endl;
		exit(1);
	}
}

void Sonido::reproducir()
{
	Mix_PlayChannel(-1, sonido, 0);
}

Sonido::~Sonido()
{
	Mix_FreeChunk(sonido);
}
