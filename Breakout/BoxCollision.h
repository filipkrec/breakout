#pragma once
#include "Component.h"
#include "SDL.h"
#include "Vector2.h"
#include <vector>

class BoxCollision : public Component
{
	SDL_Rect m_rect;

public:
	BoxCollision(Vector2 size);

	const SDL_Rect& GetCollisionRect();

	void Operation() override {};
};