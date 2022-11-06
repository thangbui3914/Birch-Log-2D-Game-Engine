#pragma once
#include "StateMachine.h"
#include "../ECS/Components.h"
#include "../Color.h"

class MenuState : public State
{
private:
	Entity& background;
	Entity& greetText;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupScreen
	};

	std::vector<Entity*>& backgrounds;
	std::vector<Entity*>& screens;
public:
	MenuState()
		: background(StateMachine::manager.addEntity()),
		greetText(StateMachine::manager.addEntity()),
		backgrounds(StateMachine::manager.getGroup(groupMap)),
		screens(StateMachine::manager.getGroup(groupScreen))
	{
		background.addComponent<TransformComponent>(0.0f, 0.0f, 1280, 720, 1);
		background.addComponent<SpriteComponent>("assets/background.jpg");
		background.addGroup(groupMap);

		greetText.addComponent<TransformComponent>(640.0f, 360.0f);
		greetText.addComponent<FrontComponent>("assets/Tinos-Bold.ttf", 64);
		greetText.getComponent<FrontComponent>().setText("Greeting click anywhere to play.", color::black);
		greetText.addGroup(groupScreen);
	}
	void input() override
	{
		while (SDL_PollEvent(&Game::event) != 0)
		{

			switch (Game::event.type)
			{
			case SDL_QUIT:
				Game::isRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				stateMachine->changeState(playState);
			default:
				break;
			}

		}
	}

	void draw() override
	{
		for (auto& c : backgrounds) c->draw();
		for (auto& c : screens) c->draw();
	}
};