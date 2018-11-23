#include "audio.h"
#include <stdio.h>

Audio::~Audio(){
	// SDL_CloseAudioDevice(deviceID);
	// SDL_FreeWAV(wavBuffer);
	Mix_FreeChunk(chunk);
}

void Audio::load(const char* filename){
	// SDL_LoadWAV(filename, &wavSpec, &wavBuffer, &wavLength);
	// deviceID = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
	chunk = Mix_LoadWAV(filename);
	if (chunk == NULL) 
		printf("load sound name: %s error, an error : %s", filename, Mix_GetError());
}

void Audio::play() {
	//SDL_QueueAudio(deviceID, wavBuffer, wavLength);
	//SDL_PauseAudioDevice(deviceID, 0);
	Mix_PlayChannel(-1, chunk, 0);
}