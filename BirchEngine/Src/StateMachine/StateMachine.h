#pragma once
#include "../ECS/ECS.h"

enum gameStates
{
	playState,
	menuState,
};

class StateMachine;

class State
{
public:
	StateMachine* stateMachine;

	virtual void input() {}
	virtual void draw() {}
	virtual ~State() {}
};

class StateMachine
{
public:
	State* uState;
	static Manager* manager;
	gameStates currentState;

	StateMachine();
	~StateMachine();
	void input();
	void update();
	void draw();
	void changeState(gameStates state);
};