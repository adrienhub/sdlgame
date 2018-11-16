#include "game.h"

Game::Game() {
	SDL_Init(0);
	int r = 3;
	SDL_CreateWindowAndRenderer(160*r, 144*r, 0, &win, &ren); //window flags SDL_WINDOW_BORDERLESS 
	SDL_SetWindowTitle( win, "Our first game");
	running = true;
	count = 0;
	loop();
}

Game::~Game() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

void Game::loop() {
	while(running) {

		lastFrame = SDL_GetTicks();
		static int lastTime;
		if (lastFrame >= (lastTime + 1000)) {
			lastTime = lastFrame;
			frameCount = 0;
			count++;
		}
		
		render();
		input();
		update();

		if (count > 3) running = false;
	}
}

void Game::render() {
	//33,11,46 - dark
	//58,101,90 - medium green
	//119,175,104 - light green
	//220,254,207 - light
	SDL_SetRenderDrawColor(ren, 119, 175, 104, 1); //rgba
	SDL_Rect rect;
	rect.x = rect.y = 0;
	rect.w = 160;
	rect.h = 144;
	SDL_RenderFillRect(ren, &rect);
	
	frameCount++;
	int timerFPS = SDL_GetTicks()-lastFrame;
	if (timerFPS < (1000/60)) {
		SDL_Delay((1000/60)-timerFPS);
	}
	
	SDL_RenderPresent(ren);
}
