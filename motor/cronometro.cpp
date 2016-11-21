#include "cronometro.h"

Cronometro::Cronometro()
{
	activo = false;
	ticks_inicio = SDL_GetTicks();
}

void Cronometro::activar()
{
	activo = true;
	ticks_inicio = SDL_GetTicks();
}

void Cronometro::parar()
{
	activo = false;
}

int Cronometro::tiempo() const
{
	if(activo)
		return SDL_GetTicks() - ticks_inicio;
	else
		return 0;
}

bool Cronometro::esta_activo() const
{
	return activo;
}
