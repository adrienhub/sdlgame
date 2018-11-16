#ifndef GAME_H
#define GAME_H

#include <iostream>
using namespace std;
#include <SDL2/SDL.h>

class Game {
public:
		Game();
		~Game();
		void loop();
		void update(){};
		void render();
		void input(){};
private:	
	SDL_Renderer* ren;
	SDL_Window* win;	
	bool running;
	int count;
	int frameCount, timerFPS, lastFrame;
};

#endif //GAME_H