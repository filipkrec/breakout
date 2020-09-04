#pragma once
#include "CircleCollision.h"
#include "BoxCollision.h"
#include <cmath>
#include <algorithm>
#include <typeinfo>

class Physics : public Component
{
	int m_speed;
	int m_angle;

public:
	Physics();
	void Operation() override;

	void SetSpeed(int units);
	void SetAngle(int degrees);

private:
	Line GetCollidingLine(Vector2 position, BoxCollision& collision);
	void ResolveCollision();
	void Move();
};