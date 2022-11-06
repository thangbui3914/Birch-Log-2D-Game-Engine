#include <string>

#include "Game.h"
#include "TextureManager.h"

#include "ECS/Components.h"
#include "Vector2D.h"
#include "Animation.h"
#include "Color.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isRunning = false;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = nullptr;
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (window == nullptr)
		{
			std::cout << "Creating window error:" << SDL_GetError() << std::endl;
		}
		renderer = nullptr;
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer == nullptr)
		{
			std::cout << "Creating renderer error:" << SDL_GetError() << std::endl;
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
		if (!IMG_Init(imgFlags))
		{
			std::cout << "IMG_Init error:" << IMG_GetError() << std::endl;
		}

		if (TTF_Init() == -1)
		{
			std::cout << "TTF_Init() error:" << TTF_GetError() << std::endl;
		}
		stateMachine = new StateMachine();
		isRunning = true;
	}
}

void Game::handleEvents()
{
	stateMachine->input();
}

void Game::update()
{
	stateMachine->update();
}



void Game::render()
{
	stateMachine->draw();
}

void Game::clean()
{
	delete stateMachine;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}