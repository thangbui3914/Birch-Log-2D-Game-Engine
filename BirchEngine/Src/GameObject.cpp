#include "GameObject.h"
#include "TextureManager.h"



GameObject::GameObject(const char* textureSheet, int x, int y)
{
	objectTexture = TextureManager::loadTexture(textureSheet);

	xpos = x;
	ypos = y;
}

void GameObject::Update()
{
	xpos++;
	ypos++;

	srcRect.h = 30;
	srcRect.w = 30;
	srcRect.x = 0;
	srcRect.y = 0;

	destRec.x = xpos;
	destRec.y = ypos;
	destRec.w = srcRect.w * 2;
	destRec.h = srcRect.h * 2;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &destRec);
}