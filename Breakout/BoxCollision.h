#pragma once
#include "Component.h"
#include "SDL.h"
#include "Rect.h"
#include "Vector2.h"
#include <vector>

class BoxCollision : public Component
{
	Rect m_rect;
	Rect m_collidedRect;

public:

	enum class Side
	{
		TOP, BOTTOM, LEFT, RIGHT
	};

public:
	~BoxCollision() override {}
	BoxCollision(Vector2 size);

	BoxCollision(BoxCollision& other);

	const Rect& GetCollisionRect();

	const Rect& GetCollidedRect() const;

	void Operation() override {};

	bool Collided();

	bool CheckCollision(const Rect& rect);

	bool CheckPointCollision(const Vector2& point);

	void SetSize(Vector2 size);

	Side GetCollidingSide(Component& circleComp);
};