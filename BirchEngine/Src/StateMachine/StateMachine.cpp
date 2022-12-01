#include "StateMachine.h"
#include "States.h"
#include "SDL.h"
#include "../Game.h"


Manager* StateMachine::manager = nullptr;
State* StateMachine::uState = nullptr;

StateMachine::StateMachine()
{
	manager = new Manager();
	uState = new MenuState();
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
	uState->update();
	manager->refresh();
	manager->Update();
}

void StateMachine::draw()
{
	SDL_RenderClear(Game::renderer);
	uState->draw();
	SDL_RenderPresent(Game::renderer);
}

void StateMachine::changeState(State* state)
{
	delete uState;
	uState = state;
}