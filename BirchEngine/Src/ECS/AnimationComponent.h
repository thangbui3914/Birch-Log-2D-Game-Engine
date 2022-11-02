#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "../Animation.h"

class AnimationComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	animationType animType = none;
	spriteSheetData s_data;

	int temp;
public:
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	AnimationComponent() = default;

	// No animation
	AnimationComponent(const char* path)
	{
		setTex(path);
	}

	// SpriteSheet animation
	AnimationComponent(const char* path, spriteSheetData&& data)
	{
		setTex(path);

		animType = spriteSheet;
		s_data = std::move(data);
	}

	~AnimationComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path)
	{
		texture = TextureManager::loadTexture(path);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override
	{
		if (animType == spriteSheet)
		{
			Uint32 temp = SDL_GetTicks();
			int temp2 = static_cast<int>((temp - s_data.remainder) / s_data.speedsPerRow[s_data.currentRow]);
			if (s_data.reset)
			{
				s_data.reset = false;
				s_data.remainder = temp;
				srcRect.x = 0;
			}
			else
			{
				if (s_data.times && (temp > (s_data.curretTick + s_data.speedsPerRow[s_data.currentRow] * s_data.framesPerRow[s_data.currentRow])))
				{
					s_data.times--;
					s_data.curretTick = SDL_GetTicks();
					if (s_data.times == 0)
					{
						changeSpriteRow(s_data.lastrow);
					}
				}
				srcRect.x = srcRect.w * (temp2 % s_data.framesPerRow[s_data.currentRow]);
			}
			srcRect.y = s_data.currentRow * transform->height;
		}
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;

	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void resetAnimation()
	{
		s_data.reset = true;
	}

	void changeSpriteRow(int row)
	{
		resetAnimation();
		s_data.currentRow = row;
	}

	void changeSpriteRowTimes(int row, int times)
	{
		s_data.times = times;
		s_data.lastrow = 0;
		changeSpriteRow(row);
		s_data.curretTick = SDL_GetTicks();
	}
};