#include "object.h"

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
	SDL_Surface* surf = IMG_Load(fileName.c_str());
	tex = SDL_CreateTextureFromSurface(rem, surf);
}