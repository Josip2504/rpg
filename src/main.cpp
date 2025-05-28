#include "../inc/inc.h"

int main(int ac, char **av) {
	SDL_WindowData windowData;


	if (!sdl_init(windowData)) {
		return 1;
	}

	TTF_Font* font = TTF_OpenFont("assets/fonts/test.ttf", 24);
	if (!font) {
		std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
		sdl_clean(windowData);
		return 1;
	}

	GameState currentState = GameState::MENU;

	while (currentState != GameState::EXIT) {
		switch(currentState) {
			case GameState::MENU:
				currentState = handle_main_menu(windowData, font);
				break;
			case GameState::CONTROLS:
				currentState = handle_controls(windowData, font);
				break;
		}
	}
	TTF_CloseFont(font);
	sdl_clean(windowData);
	return 0;
}
