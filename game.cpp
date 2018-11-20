#include "game.h"

Game::Game() {
	SDL_Init(0);
	int r = 1;
	//ratio wide 1.78 gb rez 160*144, 427*240
	SDL_CreateWindowAndRenderer(160 * r, 144 * r, 0, & win, & ren); //window flags SDL_WINDOW_BORDERLESS
	SDL_SetWindowTitle( win, "Our first game");
	TTF_Init();
	running = true;
	count = 0;
	
	star.setDest(80-8,72-8,16,16);
	star.setSource(0,0,16,16);	
	star.setImage("assets/medal.png", ren);
	
	loop();
}

Game::~Game() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	TTF_Quit();
}

void Game::loop() {
	//while loop makes mouse windows wait mode? -> try SDL EVENT
	//https://stackoverflow.com/questions/13809187/sdl-c-issues-window-in-wait-status
	
	
	
	while(running) {
		SDL_Event event; //thaey say you need to process your events inside loop
		while (SDL_PollEvent( & event)) {
			lastFrame = SDL_GetTicks();
			static int lastTime;
			if (lastFrame >= (lastTime + 1000)) {
				lastTime = lastFrame;
				frameCount = 0;
				count++;
			}

			//star.setImage("dada", ren);
			
			
			render();
			input();
			update();
			draw(star); //layer? superposition stuff?
			if (count > 3) running = false;
		}
	}
}

void Game::render() {
	//33,11,46 - dark
	//58,101,90 - medium green
	//119,175,104 - light green
	//220,254,207 - light
	
	SDL_SetRenderDrawColor(ren, 33, 11, 46, 256); //rgba
	SDL_SetRenderDrawColor(ren, 58, 101, 90, 256); //rgba	
	SDL_Rect rect;
	rect.x = rect.y = 0;
	rect.w = 160;
	rect.h = 144;
	SDL_RenderFillRect(ren, & rect); //? fills screen and cover all of imgs on top :/
	
	draw(star);
	draw("bla bla game?", 10, 10, 255,255,255,255, 18);
	
	frameCount++;
	int timerFPS = SDL_GetTicks() - lastFrame;
	if (timerFPS < (1000 / 60)) {
		SDL_Delay((1000 / 60) - timerFPS);
	}
	//trying to commit
	SDL_RenderPresent(ren);
	//SDL_RenderClear(ren);
}

void Game::draw(Object o){
	SDL_Rect dest = o.getDest();
	SDL_Rect src = o.getSource();	
	SDL_RenderCopyEx(ren, o.getTex(), &src, &dest, 0, NULL, SDL_FLIP_NONE); //SDL_RendererFlip 
}

void Game::draw(const char* msg, int x, int y, int r, int g, int b, int a,int size) {
	SDL_Surface* surf;
	SDL_Texture* tex;
	TTF_Font* font = TTF_OpenFont("assets/fonts/m3x6.ttf", size);
	SDL_Color color;
	color.r=r;
	color.g=g;
	color.b=b;
	color.a=a;
	SDL_Rect rect;
	surf = TTF_RenderText_Solid(font, msg, color);
	tex = SDL_CreateTextureFromSurface(ren, surf);
	rect.x = x;
	rect.y = y;
	rect.w = surf->w;
	rect.h = surf->h;
	SDL_FreeSurface(surf);
	SDL_RenderCopy(ren, tex, NULL, &rect);
	SDL_DestroyTexture(tex);
}
