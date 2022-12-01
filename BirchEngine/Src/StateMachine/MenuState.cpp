#include "MenuState.h"

MenuState::MenuState()
	: greetText(StateMachine::manager->addEntity()),
	backgrounds(StateMachine::manager->getGroup(groupMap)),
	screens(StateMachine::manager->getGroup(groupScreen))
{
	greetText.addComponent<TransformComponent>(640.0f, 360.0f);
	greetText.addComponent<FrontComponent>("assets/Minecraft.ttf", 64);
	greetText.getComponent<FrontComponent>().setText("Greeting click anywhere to play.", color::white);
	greetText.addGroup(groupScreen);
}

void MenuState::input() 
{
	while (SDL_PollEvent(&Game::event) != 0)
	{

		switch (Game::event.type)
		{
		case SDL_QUIT:
			Game::isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			moveToGameState();
			break;
		default:
			break;
		}

	}
}

void MenuState::draw() 
{
	for (auto& c : backgrounds) c->draw();
	for (auto& c : screens) c->draw();
}

void MenuState::moveToGameState()
{
	greetText.destroy();
	State* temp = new PlayState();
	stateMachine->changeState(temp);
}