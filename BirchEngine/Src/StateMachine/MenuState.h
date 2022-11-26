#pragma once
#include "PlayState.h"
#include "../ECS/Components.h"
#include "../Color.h"

class PlayState;

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
	MenuState();

	MenuState(Entity& background);

	void input() override;

	void draw() override;

	void moveToGameState();
};