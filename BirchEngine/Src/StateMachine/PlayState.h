#pragma once
#include "../ECS/Components.h"
#include "../Color.h"
#include <string>


class PlayState : public State
{
private:
	Entity& player1;
	Entity& player2;
	Entity& ball;
	Entity& score1;
	Entity& score2;
	Entity& separator;

	enum button
	{
		Player1Up = 0,
		Player1Down,
		Player2Up,
		Player2Down,
	};
	bool buttons[4] = {};


	enum groupLabels : std::size_t
	{
		groupMap,
		groupScreen,
	};

	std::vector<Entity*>& backgrounds;
	std::vector<Entity*>& screens;

	int scores1 = 0;
	int scores2 = 0;
	std::string str;
	bool started = false;

	friend void update_ballRestart(PlayState& state);

public:
	PlayState();

	void input() override;

	void update() override;

	void draw() override;
};