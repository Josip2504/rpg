#ifndef INC_H
#define INC_H

#include <iostream>
#include <SDL2/SDL.h>
#include <string>

#define S_WIDTH 800
#define S_HEIGHT 600

struct SDL_WindowData {
	SDL_Window *window;
	SDL_Renderer *renderer;
};

bool sdl_init(SDL_WindowData &windowData);
void sdl_clean(SDL_WindowData &windowData);

#endif