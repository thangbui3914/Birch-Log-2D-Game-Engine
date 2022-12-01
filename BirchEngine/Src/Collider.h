#pragma once
#include "SDL.h"

namespace AABB
{
	bool pointAndRect(int x, int y, SDL_Rect rect)
	{
		if (x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h) return true;
		return false;
	}
	bool RectAndRect(SDL_Rect rect1, SDL_Rect rect2)
	{
		if (rect1.x < rect2.x + rect2.w &&
			rect1.x + rect1.w > rect2.x &&
			rect1.y < rect2.y + rect2.h &&
			rect1.y + rect1.h > rect2.y)
		{
			return true;
		}
		return false;
	}
}