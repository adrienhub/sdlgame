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
	string f = "G#GDRIVEGameMakerProjectsGBMiniShmupspritesplayer/player_eject_north.png";
	tex = SDL_CreateTextureFromSurface(ren, NULL);	 
  	SDL_Surface* image =  IMG_Load(f.c_str());
/*	  if (!image ) {
	  	cout << "img not found";
	  }
	  */		
//	tex = SDL_CreateTextureFromSurface(ren, image);	  

	/*
	SDL_Surface* image = IMG_Load("sample.png"); //filename! CARE when using files/load/save etc, acces and shiet can happen
	if (!image ) {
		//SDL_LogError(0, "Image fail " );
	} else {
			tex = SDL_CreateTextureFromSurface(ren, image);	  		
	}
	*/

}