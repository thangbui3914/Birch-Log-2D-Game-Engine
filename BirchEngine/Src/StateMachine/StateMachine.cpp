#include "StateMachine.h"
#include "SDL.h"
#include "../Game.h"
#include "States.h"

Manager* StateMachine::manager = nullptr;

StateMachine::StateMachine()
	:currentState(menuState), uState(nullptr)
{
	manager = new Manager();
	changeState(currentState);
}

StateMachine::~StateMachine()
{
	delete manager;
}

void StateMachine::input()
{
	uState->input();
}

void StateMachine::update()
{
	manager->refresh();
	manager->Update();
}

void StateMachine::draw()
{
	SDL_RenderClear(Game::renderer);
	uState->draw();
	SDL_RenderPresent(Game::renderer);
}

void StateMachine::changeState(gameStates state)
{
	manager->deleteAllEntities();
	delete uState;
	switch (state)
	{
	case playState:
		uState = new PlayState();
		uState->stateMachine = this;
		break;
	case menuState:
		uState = new MenuState();
		uState->stateMachine = this;
		break;
	default:
		break;
	}
}