#include "../inc/inc.h"

bool	is_mouse_over(const Button &button, int mouseX, int mouseY) {
	return (mouseX >= button.rect.x && mouseX <= button.rect.x + button.rect.w &&
			mouseY >= button.rect.y && mouseY <= button.rect.y + button.rect.h);
}

void render_cursor(SDL_WindowData &windowData) {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	SDL_Rect cursorRect = {
		mouseX - windowData.cursorWidth/2,
		mouseY - windowData.cursorHeight/2,
		windowData.cursorWidth,
		windowData.cursorHeight
	};
	SDL_RenderCopy(windowData.renderer, windowData.cursorTexture, NULL, &cursorRect);
}

bool load_button_textures(Button& btn, SDL_Renderer* renderer, 
						const std::string& normalPath, 
						const std::string& pressedPath) {
	btn.normalTexture = IMG_LoadTexture(renderer, normalPath.c_str());
	btn.pressedTexture = IMG_LoadTexture(renderer, pressedPath.c_str());

	if (!btn.normalTexture || !btn.pressedTexture) {
		std::cerr << "Failed to load button textures!" << std::endl;
		return false;
	}
	return true;
}

GameState	ft_buttons(Button &startButton, Button &controlsButton, Button &exitButton, GameState currentState, SDL_WindowData &windowData) {
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	startButton.rect = {(dm.w - 200) / 2, (dm.h - 250) / 2, 200, 50};
	controlsButton.rect = {(dm.w - 200) / 2, (dm.h - 50) / 2, 200, 50};
	exitButton.rect = {(dm.w - 200) / 2, (dm.h + 180) / 2, 200, 50};

	startButton.text = "Start Game";
	controlsButton.text = "Controls";
	exitButton.text = "Exit";

	if (!load_button_textures(startButton, windowData.renderer, 
		"assets/UI/Buttons/Button_Blue_3Slides.png", 
		"assets/UI/Buttons/Button_Blue_3Slides_Pressed.png") ||
		!load_button_textures(controlsButton, windowData.renderer, 
		"assets/UI/Buttons/Button_Blue_3Slides.png", 
		"assets/UI/Buttons/Button_Blue_3Slides_Pressed.png") ||
		!load_button_textures(exitButton, windowData.renderer, 
		"assets/UI/Buttons/Button_Blue_3Slides.png", 
		"assets/UI/Buttons/Button_Blue_3Slides_Pressed.png")) {
			return GameState::EXIT;
	}

	startButton.isPressed = false;
	controlsButton.isPressed = false;
	exitButton.isPressed = false;
	
	return currentState;
}