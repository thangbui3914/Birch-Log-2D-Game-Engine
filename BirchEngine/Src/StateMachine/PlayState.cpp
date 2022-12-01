#include "PlayState.h"
#include "MenuState.h"
#include "../Collider.h"



PlayState::PlayState()
	:player1(StateMachine::manager->addEntity()),
	player2(StateMachine::manager->addEntity()),
	ball(StateMachine::manager->addEntity()),
	score1(StateMachine::manager->addEntity()),
	score2(StateMachine::manager->addEntity()),
	separator(StateMachine::manager->addEntity()),
	backgrounds(StateMachine::manager->getGroup(groupMap)),
	screens(StateMachine::manager->getGroup(groupScreen))
{
	player1.addComponent<TransformComponent>(50.0f, 255.0f, 2, 7, 20);
	player1.addComponent<SpriteComponent>("assets/Player.png");
	player1.addGroup(groupScreen);

	player2.addComponent<TransformComponent>(1170.0f, 255.0f, 2, 7, 20);
	player2.addComponent<SpriteComponent>("assets/Player.png");
	player2.addGroup(groupScreen);

	ball.addComponent<TransformComponent>(200.0f, 330.0f, 2, 2, 30);
	ball.addComponent<SpriteComponent>("assets/Player.png");
	ball.addGroup(groupScreen);

	score1.addComponent<TransformComponent>(500.0f, 50.0f);
	score1.addComponent<FrontComponent>("assets/Minecraft.ttf", 64);
	score1.getComponent<FrontComponent>().setText("0", color::white);
	score1.addGroup(groupMap);

	score2.addComponent<TransformComponent>(760.0f, 50.0f);
	score2.addComponent<FrontComponent>("assets/Minecraft.ttf", 64);
	score2.getComponent<FrontComponent>().setText("0", color::white);
	score2.addGroup(groupMap);

	separator.addComponent<TransformComponent>(610.0f, 0.0f, 2, 24, 30);
	separator.addComponent<SpriteComponent>("assets/separator.png");
	separator.addGroup(groupMap);
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


		case SDL_KEYDOWN:
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP:
				buttons[button::Player2Up] = true;
				break;
			case SDLK_DOWN:
				buttons[button::Player2Down] = true;
				break;
			case SDLK_w:
				buttons[button::Player1Up] = true;
				break;
			case SDLK_s:
				buttons[button::Player1Down] = true;
				break;
			default:
				break;
			}
			break;


		case SDL_KEYUP:
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP:
				buttons[button::Player2Up] = false;
				break;
			case SDLK_DOWN:
				buttons[button::Player2Down] = false;
				break;
			case SDLK_w:
				buttons[button::Player1Up] = false;
				break;
			case SDLK_s:
				buttons[button::Player1Down] = false;
				break;
			default:
				break;
			}
			break;


		default:
			break;
		}

	}
}

void update_ballRestart(PlayState& state)
{
	state.ball.getComponent<TransformComponent>().position.x = 200.0f;
	state.ball.getComponent<TransformComponent>().position.y = 330.0f;
	state.ball.getComponent<TransformComponent>().velocity.x = 5.0f;
	state.ball.getComponent<TransformComponent>().velocity.y = 5.0f;
}

void PlayState::update()
{
	//player 1
	if (buttons[button::Player1Up] && buttons[button::Player1Down])
	{
		player1.getComponent<TransformComponent>().velocity.y = 0;
	}
	else if (buttons[button::Player1Up])
	{
		player1.getComponent<TransformComponent>().velocity.y = -5.0f;
	}
	else if (buttons[button::Player1Down])
	{
		player1.getComponent<TransformComponent>().velocity.y = 5.0f;
	}
	else
	{
		player1.getComponent<TransformComponent>().velocity.y = 0.0f;
	}


	if (player1.getComponent<TransformComponent>().position.y < 0)
	{
		player1.getComponent<TransformComponent>().position.y = 0;
	}
	else if (player1.getComponent<TransformComponent>().position.y > 580)
	{
		player1.getComponent<TransformComponent>().position.y = 580;
	}

	//player 2
	if (buttons[button::Player2Up] && buttons[button::Player2Down])
	{
		player2.getComponent<TransformComponent>().velocity.y = 0;
	}
	else if (buttons[button::Player2Up])
	{
		player2.getComponent<TransformComponent>().velocity.y = -5.0f;
	}
	else if (buttons[button::Player2Down])
	{
		player2.getComponent<TransformComponent>().velocity.y = 5.0f;
	}
	else
	{
		player2.getComponent<TransformComponent>().velocity.y = 0.0f;
	}


	if (player2.getComponent<TransformComponent>().position.y < 0)
	{
		player2.getComponent<TransformComponent>().position.y = 0;
	}
	else if (player2.getComponent<TransformComponent>().position.y > 580)
	{
		player2.getComponent<TransformComponent>().position.y = 580;
	}

	//ball
	if (started == false)
	{
		for (bool& key : buttons)
		{
			if (key == true)
			{
				started = true;
				update_ballRestart(*this);
			}
		}
	}

	if (ball.getComponent<TransformComponent>().position.y > 660)
	{
		ball.getComponent<TransformComponent>().position.y = 660;
		ball.getComponent<TransformComponent>().velocity.y *= -1;
		ball.getComponent<TransformComponent>().velocity.x *= 1.05f;
		ball.getComponent<TransformComponent>().velocity.y *= 1.05f;
	}
	if (ball.getComponent<TransformComponent>().position.y < 0)
	{
		ball.getComponent<TransformComponent>().position.y = 0;
		ball.getComponent<TransformComponent>().velocity.y *= -1;
		ball.getComponent<TransformComponent>().velocity.x *= 1.05f;
		ball.getComponent<TransformComponent>().velocity.y *= 1.05f;
	}
	if (ball.getComponent<TransformComponent>().position.x > 1220)
	{
		update_ballRestart(*this);
		scores1++;
		str = std::to_string(scores1);
		score1.getComponent<FrontComponent>().setText(str.c_str(), color::white);
	}
	if (ball.getComponent<TransformComponent>().position.x < 0)
	{
		update_ballRestart(*this);
		scores2++;
		str = std::to_string(scores2);
		score2.getComponent<FrontComponent>().setText(str.c_str(), color::white);
	}

	if (AABB::RectAndRect(ball.getComponent<TransformComponent>().getSDLRect(), player1.getComponent<TransformComponent>().getSDLRect()))
	{
		if (ball.getComponent<TransformComponent>().velocity.x < 0)
		{
			ball.getComponent<TransformComponent>().velocity.x *= -1;
			if (ball.getComponent<TransformComponent>().position.y > player1.getComponent<TransformComponent>().position.y + 40)
			{
				ball.getComponent<TransformComponent>().velocity.y *= -1;
			}
		}
	}
	if (AABB::RectAndRect(ball.getComponent<TransformComponent>().getSDLRect(), player2.getComponent<TransformComponent>().getSDLRect()))
	{
		if (ball.getComponent<TransformComponent>().velocity.x > 0)
		{
			ball.getComponent<TransformComponent>().velocity.x *= -1;
			if (ball.getComponent<TransformComponent>().position.y > player2.getComponent<TransformComponent>().position.y + 40)
			{
				ball.getComponent<TransformComponent>().velocity.y *= -1;
			}
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
