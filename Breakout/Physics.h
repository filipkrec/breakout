#pragma once
#include "GameObject.h"
#include "CircleCollision.h"
#include <cmath>
#include <algorithm>

class Physics : public Component
{
	int speed;
	int angle;

	void Operation() override;

	Line GetCollidingLine(Vector2 position, const BoxCollision& collision);
	void ResolveCollision();
	void Move();
};