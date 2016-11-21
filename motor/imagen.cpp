#include <SDL/SDL_image.h>
#include "imagen.h"

using namespace std;

Imagen::Imagen(const char* ruta, int filas, int columnas, int x, int y): f_(filas), c_(columnas), x_(x), y_(y)
{
	SDL_Surface *tmp;
	
	// Cargamos la imagen en una superficie temporal;
	if((tmp = IMG_Load(ruta)) == NULL){
		cerr << "Imagen::Imagen(): " << SDL_GetError() << endl;
		exit(1);
	}
	
	// La adaptamos al formato de pantalla
	
	if((imagen = SDL_DisplayFormatAlpha(tmp)) == NULL){
		cerr << "Imagen::Imagen(): " << SDL_GetError() << endl;
		exit(1);
	}
	SDL_FreeSurface(tmp);
	
	if((invertida = invertir_imagen()) == NULL){
		cerr << "Imagen::Imagen(): " << SDL_GetError() << endl;
		exit(1);
	}
	
	
	
	/* Calculamos el color transparente, en nuestro caso el magenta

	Uint32 colorkey = SDL_MapRGB(imagen->format, 255, 0, 255);

	// Lo establecemos como color transparente

	SDL_SetColorKey(imagen, SDL_SRCCOLORKEY, colorkey);
	SDL_SetColorKey(invertida, SDL_SRCCOLORKEY, colorkey);*/

}

Imagen::Imagen(const std::string& ruta, int filas, int columnas, int x, int y): f_(filas), c_(columnas), x_(x), y_(y)
{
	SDL_Surface *tmp;
	
	// Cargamos la imagen en una superficie temporal;
	if((tmp = IMG_Load(ruta.c_str())) == NULL){
		cerr << "Imagen::Imagen(): " << SDL_GetError() << endl;
		exit(1);
	}
	
	// La adaptamos al formato de pantalla
	
	if((imagen = SDL_DisplayFormat(tmp)) == NULL){
		cerr << "Imagen::Imagen(): " << SDL_GetError() << endl;
		exit(1);
	}
	SDL_FreeSurface(tmp);
	
	if((invertida = invertir_imagen()) == NULL){
		cerr << "Imagen::Imagen(): " << SDL_GetError() << endl;
		exit(1);
	}
	
	// Calculamos el color transparente, en nuestro caso el magenta

	Uint32 colorkey = SDL_MapRGB(imagen->format, 255, 0, 255);

	// Lo establecemos como color transparente

	SDL_SetColorKey(imagen, SDL_SRCCOLORKEY, colorkey);
	SDL_SetColorKey(invertida, SDL_SRCCOLORKEY, colorkey);
}

void Imagen::dibujar(SDL_Surface* pantalla, int cuadro, int x, int y, int flip)
{
	// Comprobamos que el cuadro pertenezca a la rejilla
	if(cuadro < 0 || cuadro >= (f_*c_)){
		cerr << "Imagen::dibujar(): El cuadro " << cuadro << " no existe" << endl;
		exit(1);
	}
	
	SDL_Rect origen;
	origen.w = anchura()/* - 2*/;
	origen.h = altura()/* - 2*/;
	
	// Dónde se dibujará
	SDL_Rect destino;
	destino.x = x;
	destino.y = y;
	
	switch(flip){
		
		case 1:
			// Seleccionamos la porción (cuadro) de la rejilla que se dibujará
			origen.x = ((cuadro%c_) * anchura())/* + 2*/;
			origen.y = ((cuadro/c_) * altura())/* + 2*/;

			// Blitting
			SDL_BlitSurface(imagen, &origen, pantalla, &destino);
			break;
			
		case -1:
			// Seleccionamos la porción (cuadro) de la rejilla que se dibujará
			origen.x = ((c_-1) - (cuadro % c_)) * anchura()/* + 1*/;
	 		origen.y = (cuadro / c_) * altura()/* + 2*/;

			// Blitting
			SDL_BlitSurface(invertida, &origen, pantalla, &destino);
			break;
		
		default:
			cerr << "Imagen::dibujar(): Valor inválido para flip" << endl;
			exit(1);
			break;
	}
}

SDL_Surface * Imagen::invertir_imagen() {

	SDL_Rect origen;
	SDL_Rect destino;

// Origen y destino preparados para copiar línea a línea

    origen.x = 0;
    origen.y = 0;
    origen.w = 1;
    origen.h = imagen->h;

    destino.x = imagen->w;
    destino.y = 0;
    destino.w = 1;
    destino.h = imagen->h;

    SDL_Surface* invertida_;

    // Pasamos imagen a formato de pantalla

    if((invertida_ = SDL_DisplayFormat(imagen)) == NULL){
    	cerr << "No podemos convertir la imagen al formato de pantalla" << endl;
	return NULL;
    }

    // Preparamos el rectángulo nuevo vacío del color transparente

    SDL_FillRect(invertida_, NULL, SDL_MapRGB(invertida_->format, 0, 255, 0));

    // Copiamos linea vertical a linea vertical, inversamente

    for(int i = 0; i < imagen->w; i++) {

	SDL_BlitSurface(imagen, &origen, invertida_, &destino);
	origen.x = origen.x + 1;
	destino.x = destino.x - 1;

    }

    return invertida_;
}

Imagen::~Imagen()
{
	// Liberamos la memoria ocupada
	SDL_FreeSurface(imagen);
	SDL_FreeSurface(invertida);
}

