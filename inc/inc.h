#ifndef INC_H
#define INC_H

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_ttf.h>
#include <vector>

#define S_WIDTH 800
#define S_HEIGHT 600

struct SDL_WindowData {
	SDL_Window *window;
	SDL_Renderer *renderer;
};

struct Button {
	SDL_Rect rect;
	SDL_Color color;
	std::string text;
	bool isHovered;
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

#endif