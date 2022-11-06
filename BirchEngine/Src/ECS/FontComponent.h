#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"

class FrontComponent : public Component
{
private:
	TransformComponent* transform;
	TTF_Font* font;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	FrontComponent() = default;

	FrontComponent(const char* path, int fSize)
		: texture(nullptr)
	{
		font = TTF_OpenFont(path, fSize);
		if (font == nullptr)
		{
			std::cout << "Can't open font: " << TTF_GetError() << std::endl;
		}
	}

	~FrontComponent()
	{
		if (Game::isRunning)
		{

			TTF_CloseFont(font);
		}
		SDL_DestroyTexture(texture);
	}

	void init() override
	{

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;

	}

	void update() override
	{
		destRect.x = static_cast<int>(transform->position.x - transform->width / 2);
		destRect.y = static_cast<int>(transform->position.y - transform->height / 2);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;

	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void setText(const char* string, SDL_Color textColor)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, string, textColor);
		transform->width = surface->w;
		transform->height = surface->h;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
		texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		SDL_FreeSurface(surface);
	}
};