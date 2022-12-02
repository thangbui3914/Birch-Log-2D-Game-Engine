#pragma once

#include "Components.h"
#include "../Vector2D.h"
#include "SDL.h"

class TransformComponent : public Component
{
public:

	Vector2D position;
	Vector2D velocity;

	int width = 32;
	int height = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent() = default;

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int w, int h, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	SDL_Rect getSDLRect()
	{
		return { static_cast<int>(position.x),static_cast<int>(position.y), width * scale, height * scale };
	}

	SDL_FPoint getCenter()
	{
		return { position.x + width * static_cast<float>(scale) / 2.0f, position.y + height * static_cast<float>(scale) / 2.0f };
	}
};