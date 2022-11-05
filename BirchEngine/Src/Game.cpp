#include <string>

#include "Game.h"
#include "TextureManager.h"

#include "ECS/Components.h"
#include "Vector2D.h"
#include "Animation.h"
#include "Color.h"


//Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isRunning = false;

// Entity
//auto& background(manager.addEntity());
//auto& cookie(manager.addEntity());
//auto& score(manager.addEntity());

// Group
//enum groupLabels : std::size_t
//{
//	groupMap,
//	groupScreen,
//};
//
//auto& backgrounds(manager.getGroup(groupMap));
//auto& screens(manager.getGroup(groupScreen));

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
	/*background.addComponent<TransformComponent>(0.0f, 0.0f, 1280, 720, 1);
	background.addComponent<SpriteComponent>("assets/background.jpg");
	background.addGroup(groupMap);

	score.addComponent<TransformComponent>(640.0f, 600.0f);
	score.addComponent<FrontComponent>("assets/Tinos-Bold.ttf", 64);
	score.getComponent<FrontComponent>().setText("0", color::black);
	score.addGroup(groupScreen);

	cookie.addComponent<TransformComponent>(512.0f, 232.0f, 32, 32, 8);
	cookie.addComponent<AnimationComponent>("assets/cookie.png", spriteSheetData(2, { 1, 3 }, { 1, 50 }));
	cookie.addGroup(groupScreen);*/

}

void Game::handleEvents()
{
	stateMachine->input();
	/*static int scores = 0;
	static std::string str;
	while (SDL_PollEvent(&event) != 0)
	{
		
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			cookie.getComponent<AnimationComponent>().changeSpriteRowTimes(1, 1);

			scores++;
			str = std::to_string(scores);
			score.getComponent<FrontComponent>().setText(str.c_str(), color::black);
			break;
		default:
			break;
		}

	}*/
}

void Game::update()
{
	stateMachine->update();
	/*manager.refresh();
	manager.Update();*/
}



void Game::render()
{
	stateMachine->draw();
	/*SDL_RenderClear(renderer);
	for (auto& i : backgrounds)
	{
		i->draw();
	}
	for (auto& i : screens)
	{
		i->draw();
	}
	SDL_RenderPresent(renderer);*/
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}