#ifndef GAME_H
#define GAME_H

#include <iostream>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> //installed separately not comes with SDL https://www.libsdl.org/projects/SDL_image/
#include <SDL2/SDL_ttf.h>
#include "object.h"

class Game {
	public:
		Game();
		~Game();
		void loop();
		void update() {};
		void input() {};
		void render();
		void draw(Object o);
		void draw(const char* msg, int x, int y, int r, int g, int b, int a,int size);
	private:
		SDL_Renderer * ren;
		SDL_Window * win;
		bool running;
		int count;
		int frameCount, timerFPS, lastFrame;
		Object star;
};

#endif //GAME_H
//https://stackoverflow.com/questions/13809187/sdl-c-issues-window-in-wait-status
