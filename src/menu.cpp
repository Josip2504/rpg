#include "../inc/inc.h"

bool is_mouse_over(const Button &button, int mouseX, int mouseY) {
	return (mouseX >= button.rect.x && mouseX <= button.rect.x + button.rect.w &&
			mouseY >= button.rect.y && mouseY <= button.rect.y + button.rect.h);
}

void render_button(SDL_Renderer* renderer, const Button& button, TTF_Font* font) {
	SDL_SetRenderDrawColor(renderer, button.color.r, button.color.g, button.color.b, button.color.a);
	SDL_RenderFillRect(renderer, &button.rect);

	if (font) {
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, button.text.c_str(), {255, 255, 255, 255});
		if (textSurface) {
			SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
			if (textTexture) {
				int textWidth = textSurface->w;
				int textHeight = textSurface->h;
				SDL_Rect textRect = {button.rect.x + (button.rect.w - textWidth) / 2,
									 button.rect.y + (button.rect.h - textHeight) / 2,
									 textWidth, textHeight};
				SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
				SDL_DestroyTexture(textTexture);
			}
			SDL_FreeSurface(textSurface);
		}
	}
}

GameState handle_main_menu(SDL_WindowData &windowData, TTF_Font* font) {
	SDL_Event event;
	bool running = true;
	GameState currentState = GameState::MENU;

	Button startButton = {{100, 100, 200, 50}, {0, 255, 0, 255}, "Start Game", false};
	Button controlsButton = {{100, 200, 200, 50}, {0, 0, 255, 255}, "Controls", false};
	Button exitButton = {{100, 300, 200, 50}, {255, 0, 0, 255}, "Exit", false};

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
				currentState = GameState::EXIT;
			}

			if (event.type == SDL_MOUSEMOTION) {
				int mouseX = event.motion.x;
				int mouseY = event.motion.y;

				startButton.isHovered = is_mouse_over(startButton, mouseX, mouseY);
				controlsButton.isHovered = is_mouse_over(controlsButton, mouseX, mouseY);
				exitButton.isHovered = is_mouse_over(exitButton, mouseX, mouseY);
			}

			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				int mouseX = event.button.x;
				int mouseY = event.button.y;

				if (is_mouse_over(startButton, mouseX, mouseY)) {
					currentState = GameState::GAME;
					running = false;
				} else if (is_mouse_over(controlsButton, mouseX, mouseY)) {
					currentState = GameState::CONTROLS;
					running = false;
				} else if (is_mouse_over(exitButton, mouseX, mouseY)) {
					currentState = GameState::EXIT;
					running = false;
				}
			}
		}

		SDL_SetRenderDrawColor(windowData.renderer, 0, 0, 0, 255);
		SDL_RenderClear(windowData.renderer);

		render_button(windowData.renderer, startButton, font);
		render_button(windowData.renderer, controlsButton, font);
		render_button(windowData.renderer, exitButton, font);

		SDL_RenderPresent(windowData.renderer);
	}

	return currentState;
}

GameState handle_controls(SDL_WindowData &windowData, TTF_Font* font) {
	SDL_Event event;
	GameState currentState = GameState::CONTROLS;

	Button backButton = {{300, 450, 200, 50}, {255, 200, 0, 255}, "Back", false};

	std::vector<std::string> controlsText = {
		"Controls:",
		"W - Move Up",
		"A - Move Left",
		"S - Move Down",
		"D - Move Right",
		"ESC - Pause Game"
	};

	while (currentState == GameState::CONTROLS) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return GameState::EXIT;
			}

			if (event.type == SDL_MOUSEMOTION) {
				backButton.isHovered = is_mouse_over(backButton, event.motion.x, event.motion.y);
			}

			if (event.type == SDL_MOUSEBUTTONDOWN && 
				event.button.button == SDL_BUTTON_LEFT && 
				is_mouse_over(backButton, event.button.x, event.button.y)) {
				return GameState::MENU;
			}
		}

		// Rendering
		SDL_SetRenderDrawColor(windowData.renderer, 30, 30, 50, 255);
		SDL_RenderClear(windowData.renderer);

		SDL_Color textColor = {255, 255, 255, 255};
		int yOffset = 150;
		for (const auto& line : controlsText) {
			SDL_Surface* textSurface = TTF_RenderText_Solid(font, line.c_str(), textColor);
			if (textSurface) {
				SDL_Texture* textTexture = SDL_CreateTextureFromSurface(windowData.renderer, textSurface);
				if (textTexture) {
					int textWidth = textSurface->w;
					int textHeight = textSurface->h;
					SDL_Rect textRect = {S_WIDTH / 2 - textWidth / 2, yOffset, textWidth, textHeight};
					SDL_RenderCopy(windowData.renderer, textTexture, nullptr, &textRect);
					SDL_DestroyTexture(textTexture);
				}
				SDL_FreeSurface(textSurface);
			}
			yOffset += 30;
		}

		render_button(windowData.renderer, backButton, font);

		SDL_RenderPresent(windowData.renderer);
	}

	return currentState;
}