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
	bool m_collisionResolved;

public:
	Physics();
	void Operation() override;

	void SetSpeed(int units);
	void SetAngle(int degrees);

private:
	bool CollidingLineHorizontal(Vector2 position, BoxCollision& collision);
	void ResolveCollision();
	void OnCircleEnterBox();
	void OnCircleExitBox();
	void Move();
};