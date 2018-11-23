#include "game.h"

bool debugmode = 0;
int resize = 1;
int res_w = 160;
int res_h = 144;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_DisplayMode desktop;  
	SDL_GetDesktopDisplayMode(0,&desktop);
	cout << "Display desktop WxH:" << desktop.w << "x" << desktop.h << endl; 
	//SDL_Log("Display resolution is: %d %d  %d", desktop.w, desktop.h, desktop.refresh_rate);
	// SDL_DisplayMode current;  
	// SDL_GetCurrentDisplayMode(0,&current);
	// cout << "Current Display WxH:" << current.w << "x" << current.h << endl;
	//TODO Use current size to make a proper rescale 	

	//ratio wide 1.78 gb rez 160*144, 427*240
	SDL_CreateWindowAndRenderer(res_w * resize, res_h * resize, 0, & win, & ren); //window flags SDL_WINDOW_BORDERLESS
	SDL_SetWindowTitle( win, "Our first game");
	TTF_Init();
	font = TTF_OpenFont("assets/fonts/m3x6.ttf", 18*resize);

	
	//Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        cout << "Error opening sound device" << endl;  
    }
	Mix_Init(MIX_INIT_OGG); //http://lazyfoo.net/SDL_tutorials/lesson11/index.php
	
	running = true;
	//count = 0;

	star.setDest(80 - 8, 72 - 8, 16, 16);
	star.setSource(0, 0, 16, 16);
	star.setImage("assets/medal.png", ren);
	
	effect.load("assets/sounds/fusil-tiro.wav");

	player.setImage("", ren);
	player.setDest(res_w/2, res_h/2, 16, 16);
	// idle = player.createCycle(); //row 0- pixel wdth
	// attack = player ~15m
	
	loop();
}

Game::~Game() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	Mix_CloseAudio();
	SDL_Quit();
	TTF_Quit();
}

void Game::loop() {
	//while loop makes mouse windows wait mode? -> try SDL EVENT
	//https://stackoverflow.com/questions/13809187/sdl-c-issues-window-in-wait-status
	
	while(running) {
		// SDL_Event event; //thaey say you need to process your events inside game loop
		// while (SDL_PollEvent( & event)) {
		lastFrame = SDL_GetTicks();
		static int lastTime;
		//if (debugmode) cout << "lastFrame " << lastFrame << endl;
		if (lastFrame >= (lastTime + 1000)) {
			lastTime = lastFrame;
			frameCount = 0;
			//if (debugmode) cout << "frameCount " << frameCount << endl;
			//count++;
		}

		//star.setImage("dada", ren);
		render();
		input();
		update();
		//draw(star); //layer? superposition stuff?
		//if (count > 3) running = false;
		// }
	}
}

void Game::render() {
	//33,11,46 - dark
	//58,101,90 - medium green
	//119,175,104 - light green
	//220,254,207 - light

	SDL_SetRenderDrawColor(ren, 33, 11, 46, 255); //rgba
	SDL_SetRenderDrawColor(ren, 58, 101, 90, 255); //rgba
	SDL_Rect rect;
	if (resize > 1) {
		   int W = res_w*resize;
		   int H = res_h*resize;
		   int midleX = W/2;
		   int midleY = H/2;
		   	rect.x = rect.y = 0;
			rect.w = W; //160;
			rect.h = H; //144;
			SDL_SetRenderDrawColor(ren, 33, 11, 46, 255); //dark
			SDL_RenderFillRect(ren, & rect); // Draw Rect
			rect.x = midleX - (res_w/2);
			rect.y = midleY - (res_h/2);
			rect.w = res_w; //160;
			rect.h = res_h; //144;
			SDL_SetRenderDrawColor(ren, 58, 101, 90, 255); //rgba
			SDL_RenderFillRect(ren, & rect); // Draw Rect
		   	
	} else {
		rect.x = rect.y = 0;
		rect.w = res_w; //160;
		rect.h = res_h; //144;
		SDL_RenderFillRect(ren, & rect); //? fills screen and cover all of imgs on top :/
		//why
	}

	draw(star);
	draw("bla bla game?", 10, 10, 255, 255, 255, 255);
	//if (debugmode) cout << "render()" << endl;

	frameCount++;
	int timerFPS = SDL_GetTicks() - lastFrame;
	if (timerFPS < (1000 / 60)) {
		SDL_Delay((1000 / 60) - timerFPS);
		//if (debugmode) cout << "Delay " << frameCount << endl;
	}
	//trying to commit
	SDL_RenderPresent(ren);
	//SDL_RenderClear(ren);
}
//rescale https://gamedev.stackexchange.com/questions/102870/rescale-pixel-art-scenery-before-rendering-in-sdl2
void Game::draw(Object o) {
	//rescale obj?
	SDL_Rect dest = o.getDest();
	dest.w = dest.w*resize;
	dest.h = dest.h*resize;
	SDL_Rect src = o.getSource();
	SDL_RenderCopyEx(ren, o.getTex(), & src, & dest, 0, NULL, SDL_FLIP_NONE); //SDL_RendererFlip
}

void Game::draw(const char * msg, int x, int y , int r, int g, int b, int a) {
	SDL_Surface * surf;
	SDL_Texture * tex;
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	SDL_Rect rect;
	surf = TTF_RenderText_Solid(font, msg, color);
	tex = SDL_CreateTextureFromSurface(ren, surf);
	rect.x = x;
	rect.y = y;
	rect.w = surf->w;
	rect.h = surf->h;
	SDL_FreeSurface(surf);
	SDL_RenderCopy(ren, tex, NULL, & rect);
	SDL_DestroyTexture(tex);
}

void Game::input() {
	SDL_Event e; //thaey say you need to process your events inside loop
	while(SDL_PollEvent( & e)) {
		//wcout << "Event " << e.type << endl;
		if (e.type == SDL_QUIT) {
			running = false;
			cout << "Quiting" << endl;
		}
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
				cout << "escape?" << endl;
			}
			if (e.key.keysym.sym == SDLK_w) {
				cout << "w down" << endl;
				effect.play();
			}
		}
		if (e.type == SDL_KEYUP) {
			if (e.key.keysym.sym == SDLK_w) {
				cout << "w up" << endl;
			}
		}
		SDL_GetMouseState( & mousex, & mousey);
	}
}

void Game::update(){
	
}
