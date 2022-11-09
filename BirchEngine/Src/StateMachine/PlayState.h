#pragma once
#include "../ECS/Components.h"
#include "StateMachine.h"
#include "../Color.h"
#include <string>

class PlayState : public State
{
private:
	Entity& background;
	Entity& cookie;
	Entity& score;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupScreen,
	};

	std::vector<Entity*>& backgrounds;
	std::vector<Entity*>& screens;

	int scores;
	std::string str;

public:
	PlayState()
		:background(StateMachine::manager->addEntity()),
		cookie(StateMachine::manager->addEntity()),
		score(StateMachine::manager->addEntity()),
		backgrounds(StateMachine::manager->getGroup(groupMap)),
		screens(StateMachine::manager->getGroup(groupScreen))
	{
		scores = 0;

		background.addComponent<TransformComponent>(0.0f, 0.0f, 1280, 720, 1);
		background.addComponent<SpriteComponent>("assets/background.jpg");
		background.addGroup(groupMap);

		score.addComponent<TransformComponent>(640.0f, 600.0f);
		score.addComponent<FrontComponent>("assets/Tinos-Bold.ttf", 64);
		score.getComponent<FrontComponent>().setText("0", color::black);
		score.addGroup(groupScreen);

		cookie.addComponent<TransformComponent>(512.0f, 232.0f, 32, 32, 8);
		cookie.addComponent<AnimationComponent>("assets/cookie.png", spriteSheetData(2, { 1, 3 }, { 1, 50 }));
		cookie.addGroup(groupScreen);
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
				cookie.getComponent<AnimationComponent>().changeSpriteRowTimes(1, 1);

				scores++;
				str = std::to_string(scores);
				score.getComponent<FrontComponent>().setText(str.c_str(), color::black);
				break;
			default:
				break;
			}

		}
	}

	void draw() override
	{
		for (auto& i : backgrounds)
		{
			i->draw();
		}
		for (auto& i : screens)
		{
			i->draw();
		}
	}
};