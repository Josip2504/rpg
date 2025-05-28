#ifndef INC_H
#define INC_H

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <SDL2/SDL_image.h>

#define S_WIDTH 800
#define S_HEIGHT 600

struct SDL_WindowData {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *cursorTexture;
	int cursorWidth, cursorHeight;
};

struct Button {
	SDL_Rect rect;
	SDL_Texture *normalTexture;
	SDL_Texture *pressedTexture;
	std::string text;
	bool isHovered;
	bool isPressed;
};

enum class GameState {
	MENU,
	GAME,
	CONTROLS,
	EXIT
};

bool		sdl_init(SDL_WindowData &windowData);
void		sdl_clean(SDL_WindowData &windowData);

GameState	handle_main_menu(SDL_WindowData &windowData, TTF_Font *font);
GameState	handle_controls(SDL_WindowData &windowData, TTF_Font* font);
void		render_button(SDL_Renderer *renderer, const Button &button, TTF_Font *font);

bool		is_mouse_over(const Button &button, int mouseX, int mouseY);
void		render_cursor(SDL_WindowData &windowData);

GameState	ft_buttons(Button &startButton, Button &controlsButton, Button &exitButton, GameState currentState, SDL_WindowData &windowData);

bool load_button_textures(Button& btn, SDL_Renderer* renderer, 
						const std::string& normalPath, 
						const std::string& pressedPath);

#endif