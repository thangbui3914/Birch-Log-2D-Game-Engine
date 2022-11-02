#pragma once

#include "SDL.h"
#include <SDL_ttf.h>
#include <iostream>
#include "SDL_image.h"
#include <vector>

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer* renderer;
	static TTF_Font* gFont;
	static SDL_Event event;
	static bool isRunning;

private:
	int cnt = 0;
	SDL_Window* window;
};