#pragma once
#include "SDL.h"

enum animationType
{
	none,
	spriteSheet,
};

struct spriteSheetData
{
	int rows;
	int currentRow;
	int remainder;
	int times;
	int lastrow;
	Uint32 curretTick;
	bool reset;
	std::vector<int>framesPerRow;
	std::vector<int> speedsPerRow;
	spriteSheetData() = default;
	spriteSheetData(int rows, std::vector<int>&& frames, std::vector<int>&& speeds) :
		rows(rows), currentRow(0), remainder(0), times(0), lastrow(0), reset(false)
	{
		framesPerRow = std::move(frames);
		speedsPerRow = std::move(speeds);
	}
};