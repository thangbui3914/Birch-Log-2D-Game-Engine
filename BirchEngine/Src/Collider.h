#pragma once
#include "SDL.h"

namespace AABB
{
	bool pointAndRect(int x, int y, SDL_Rect rect)
	{
		if (x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h) return true;
		else return false;
	}
}