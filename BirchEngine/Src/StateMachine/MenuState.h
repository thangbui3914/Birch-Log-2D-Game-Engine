#pragma once
#include "PlayState.h"
#include "../ECS/Components.h"
#include "../Color.h"

class PlayState;

class MenuState : public State
{
private:
	Entity& greetText;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupScreen
	};

	std::vector<Entity*>& backgrounds;
	std::vector<Entity*>& screens;
public:
	MenuState();

	void input() override;

	void draw() override;

	void moveToGameState();
};