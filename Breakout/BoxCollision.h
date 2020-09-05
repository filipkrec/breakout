#pragma once
#include "Component.h"
#include "SDL.h"
#include "Rect.h"
#include "Vector2.h"
#include <vector>

class BoxCollision : public Component
{
	Rect m_rect;

public:
	BoxCollision(Vector2 size);

	const Rect& GetCollisionRect();

	void Operation() override {};
};