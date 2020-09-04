#pragma once
#include "Scene.h"
#include "SDL.h"
#include "Vector2.h"
#include <vector>

class BoxCollision : public Component
{
	SDL_Rect m_rect;

public:
	BoxCollision(Vector2 size, Vector2 position);

	const SDL_Rect& GetCollisionRect() const;

	void Operation() override {};
};