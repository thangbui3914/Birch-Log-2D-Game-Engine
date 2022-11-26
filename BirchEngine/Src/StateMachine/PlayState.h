#pragma once
#include "../ECS/Components.h"
#include "../Color.h"
#include <string>


class PlayState : public State
{
private:
	Entity& background;
	Entity& cookie;
	Entity& score;
	int mouse_x = 0;
	int mouse_y = 0;

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
	PlayState(Entity& background);

	void input() override;

	void draw() override;

	void moveToMenuState();
};