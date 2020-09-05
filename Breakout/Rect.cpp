#include "Rect.h"

float Rect::ratioX;
float Rect::ratioY;

Rect::Rect()
{}

Rect::Rect(Vector2 position, Vector2 size)
{
	x = position.x;
	y = position.y;
	w = size.x;
	h = size.y;
}

SDL_Rect Rect::SDLRect()
{
	return SDL_Rect{ 
		(int)((float)	x * ratioX	), 
		(int)((float)	(900  - y - h) * ratioY		),
		(int)((float)   w * ratioX				),
		(int)((float)   h * ratioY				) };
}

void Rect::SetRatio(Vector2 resolution)
{
	ratioX = (float)resolution.x / 1600;
	ratioY = (float)resolution.y / 900;
}