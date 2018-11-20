#include "object.h"
#include <SDL2/SDL_image.h>

void Object::setDest(int x, int y, int w, int h) {
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;	
}

void Object::setSource(int x, int y, int w, int h) {
	src.x = x;
	src.y = y;
	src.w = w;
	src.h = h;
}

void Object::setImage(string fileName, SDL_Renderer* ren){

	SDL_Surface* image = IMG_Load(fileName.c_str()); //filename! CARE when using files/load/save etc, acces and shiet can happen
	tex = SDL_CreateTextureFromSurface(ren, image);
	// if (image == NULL) {
	// 	SDL_Window* w = SDL_CreateWindow("erro", 0 ,0 ,100 ,100, 0);
	// 	SDL_ShowWindow(w);
	// } else {
 	// tex = SDL_CreateTextureFromSurface(ren, image);	  		
	//}
}

