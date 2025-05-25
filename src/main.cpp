#include "../inc/inc.h"

int main(int ac, char **av) {
	SDL_WindowData windowData;

	if (!sdl_init(windowData)) {
		return 1;
	}

	SDL_Event event;
	bool running = true;

	// game loop
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				SDL_DestroyRenderer(windowData.renderer);
				SDL_DestroyWindow(windowData.window);
				SDL_Quit();
				return 0;
			}

			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
			}
		}

		SDL_SetRenderDrawColor(windowData.renderer, 0, 0, 0, 255);
		SDL_RenderClear(windowData.renderer);

		// Render your game objects here

		SDL_RenderPresent(windowData.renderer);
	}

	sdl_clean(windowData);
	return 0;
}
