#include "PlayState.h"
#include "MenuState.h"
#include "../Collider.h"

PlayState::PlayState(Entity& background)
	:background(background),
	cookie(StateMachine::manager->addEntity()),
	score(StateMachine::manager->addEntity()),
	backgrounds(StateMachine::manager->getGroup(groupMap)),
	screens(StateMachine::manager->getGroup(groupScreen))
{
	scores = 0;

	score.addComponent<TransformComponent>(640.0f, 600.0f);
	score.addComponent<FrontComponent>("assets/Tinos-Bold.ttf", 64);
	score.getComponent<FrontComponent>().setText("0", color::black);
	score.addGroup(groupScreen);

	cookie.addComponent<TransformComponent>(512.0f, 232.0f, 32, 32, 8);
	cookie.addComponent<AnimationComponent>("assets/cookie.png", spriteSheetData(2, { 1, 3 }, { 1, 50 }));
	cookie.addGroup(groupScreen);
}

void PlayState::input()
{
	while (SDL_PollEvent(&Game::event) != 0)
	{

		switch (Game::event.type)
		{
		case SDL_QUIT:
			Game::isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&mouse_x, &mouse_y);
			if (AABB::pointAndRect(mouse_x, mouse_y, cookie.getComponent<TransformComponent>().getSDLRect()))
			{
				cookie.getComponent<AnimationComponent>().changeSpriteRowTimes(1, 1);

				scores++;
				str = std::to_string(scores);
				score.getComponent<FrontComponent>().setText(str.c_str(), color::black);
			}
			break;
		default:
			break;
		}

	}
}

void PlayState::draw()
{
	for (auto& i : backgrounds)
	{
		i->draw();
	}
	for (auto& i : screens)
	{
		i->draw();
	}
}

void PlayState::moveToMenuState()
{
	score.destroy();
	cookie.destroy();
	State* temp = new MenuState(background);
	stateMachine->changeState(temp);
}