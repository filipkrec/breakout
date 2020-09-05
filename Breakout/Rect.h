#pragma once
#include "SDL.h"
#include "Vector2.h"

class Rect
{
	static float ratioX;
	static float ratioY;
	

public:
	int x;
	int y;
	int w;
	int h;

	Rect();
	Rect(Vector2 position, Vector2 size);
	SDL_Rect SDLRect();
	static void SetRatio(Vector2 resolution);
};