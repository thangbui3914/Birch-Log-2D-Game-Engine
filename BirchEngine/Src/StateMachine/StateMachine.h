#pragma once
#include "../ECS/ECS.h"

class StateMachine;

class State
{
public:
	StateMachine* stateMachine;

	virtual void input() {}
	virtual void update() {}
	virtual void draw() {}
	virtual ~State() {}
};

class StateMachine
{
public:
	static State* uState;
	static Manager* manager;

	StateMachine();
	~StateMachine();
	void input();
	void update();
	void draw();
	void changeState(State* state);
};