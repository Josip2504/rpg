#include "../inc/inc.h"

void render_button(SDL_Renderer* renderer, const Button& button, TTF_Font* font) {
	SDL_Texture* tex = button.normalTexture;
	if (button.isPressed) tex = button.pressedTexture;

	SDL_RenderCopy(renderer, tex, NULL, &button.rect);

	SDL_Color textColor = {255, 255, 255, 255};
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, button.text.c_str(), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_Rect textRect = {
		button.rect.x + (button.rect.w - textSurface->w)/2,
		button.rect.y + (button.rect.h - textSurface->h)/2,
		textSurface->w,
		textSurface->h
	};

	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

GameState handle_main_menu(SDL_WindowData &windowData, TTF_Font* font) {
	SDL_Event event;
	bool running = true;
	GameState currentState = GameState::MENU;
	Button startButton, controlsButton, exitButton;
	currentState = ft_buttons(startButton, controlsButton, exitButton, currentState, windowData);

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
				currentState = GameState::EXIT;
			}

			if (event.type == SDL_MOUSEMOTION) {
				startButton.isHovered = is_mouse_over(startButton, event.motion.x, event.motion.y);
				controlsButton.isHovered = is_mouse_over(controlsButton, event.motion.x, event.motion.y);
				exitButton.isHovered = is_mouse_over(exitButton, event.motion.x, event.motion.y);
			}

			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
					startButton.isPressed = is_mouse_over(startButton, event.motion.x, event.motion.y);
					controlsButton.isPressed = is_mouse_over(controlsButton, event.motion.x, event.motion.y);
					exitButton.isPressed = is_mouse_over(exitButton, event.motion.x, event.motion.y);
			}

			if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
				if (startButton.isPressed && startButton.isHovered) return GameState::GAME;
				if (controlsButton.isPressed && controlsButton.isHovered) return GameState::CONTROLS;
				if (exitButton.isPressed && exitButton.isHovered) {
					running = false;
					currentState = GameState::EXIT;
				}
				exitButton.isPressed = false;
			}
			if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
				if (startButton.isPressed && !startButton.isHovered) startButton.isPressed = false;
				if (controlsButton.isPressed && !controlsButton.isHovered) controlsButton.isPressed = false;
				if (exitButton.isPressed && !exitButton.isHovered) exitButton.isPressed = false;
			}
		}

		SDL_SetRenderDrawColor(windowData.renderer, 78, 181, 181, 255);
		SDL_RenderClear(windowData.renderer);

		//rendering
		render_button(windowData.renderer, startButton, font);
		render_button(windowData.renderer, controlsButton, font);
		render_button(windowData.renderer, exitButton, font);

		render_cursor(windowData);

		SDL_RenderPresent(windowData.renderer);
	}

	return currentState;
}

GameState handle_controls(SDL_WindowData &windowData, TTF_Font* font) {
	if (!font) return GameState::EXIT;

	SDL_Event event;
	GameState currentState = GameState::CONTROLS;

	Button backButton;
	backButton.isPressed = false;
	backButton.rect = {S_WIDTH / 2 - 100, S_HEIGHT - 100, 200, 50};
	backButton.text = "Back";
	if (!load_button_textures(backButton, windowData.renderer, 
		"assets/UI/Buttons/Button_Blue_3Slides.png", 
		"assets/UI/Buttons/Button_Blue_3Slides_Pressed.png")) {
		return GameState::EXIT;
	}

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

			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				backButton.isPressed = is_mouse_over(backButton, event.button.x, event.button.y);
			}

			if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
				if (backButton.isPressed && backButton.isHovered) {
					currentState = GameState::MENU;
				}
				backButton.isPressed = false;
			}
		}

		// Rendering
		SDL_SetRenderDrawColor(windowData.renderer, 78, 181, 181, 255);
		SDL_RenderClear(windowData.renderer);

		// Render controls text
		SDL_Color textColor = {255, 255, 255, 255};
		int yOffset = 150;
		for (const auto& line : controlsText) {
			SDL_Surface* textSurface = TTF_RenderText_Solid(font, line.c_str(), textColor);
			if (textSurface) {
				SDL_Texture* textTexture = SDL_CreateTextureFromSurface(windowData.renderer, textSurface);
				if (textTexture) {
					int textWidth = textSurface->w;
					SDL_Rect textRect = {S_WIDTH / 2 - textWidth / 2, yOffset, textWidth, textSurface->h};
					SDL_RenderCopy(windowData.renderer, textTexture, nullptr, &textRect);
					SDL_DestroyTexture(textTexture);
				}
				SDL_FreeSurface(textSurface);
			}
			yOffset += 30;
		}

		render_button(windowData.renderer, backButton, font);
		render_cursor(windowData);

		SDL_RenderPresent(windowData.renderer);
	}

	return currentState;
}