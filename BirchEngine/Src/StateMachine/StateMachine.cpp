#include "StateMachine.h"
#include "SDL.h"
#include "../Game.h"
#include "States.h"

Manager StateMachine::manager;

StateMachine::StateMachine()
	:currentState(playState), uState(nullptr)
{
	changeState(currentState);
}

void StateMachine::input()
{
	uState->input();
}

void StateMachine::update()
{
	manager.refresh();
	manager.Update();
}

void StateMachine::draw()
{
	SDL_RenderClear(Game::renderer);
	uState->draw();
	SDL_RenderPresent(Game::renderer);
}

void StateMachine::changeState(gameStates state)
{
	/*if (state == currentState)
	{
		std::cout << "Error try to change state to current state";
		return;
	}*/
	manager.deleteAllEntities();
	delete uState;
	switch (state)
	{
	case playState:
		uState = new PlayState();
		break;
	default:
		break;
	}
}