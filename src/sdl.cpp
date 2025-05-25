#include "../inc/inc.h"

bool sdl_init(SDL_WindowData &windowData) {
	windowData.window = nullptr;
	windowData.renderer = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	windowData.window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, S_WIDTH, S_HEIGHT, SDL_WINDOW_SHOWN);
	if (!windowData.window) {
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	windowData.renderer = SDL_CreateRenderer(windowData.window, -1, SDL_RENDERER_ACCELERATED);
	if (!windowData.renderer) {
		std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(windowData.window);
		SDL_Quit();
		return false;
	}

	return true;
}

void sdl_clean(SDL_WindowData &windowData) {
	SDL_DestroyRenderer(windowData.renderer);
	SDL_DestroyWindow(windowData.window);
	SDL_Quit();
}
