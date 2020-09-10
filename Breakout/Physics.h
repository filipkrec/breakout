#pragma once
#include "CircleCollision.h"
#include "BoxCollision.h"
#include <cmath>
#include <algorithm>
#include <typeinfo>
#include <iostream>

class Physics : public Component
{
	int m_speed;
	float m_angle;
	bool m_collisionResolved;

	enum class Side
	{
		TOP, BOTTOM, LEFT, RIGHT
	};

public:
	~Physics() override {}
	Physics();
	void Operation() override;

	inline const int GetSpeed() const { return m_speed; }
	void SetSpeed(int units);
	void SetAngle(float degrees);

	void OnCollisionEnter(Component* collidedOther) override;

private:
	Side GetCollidingSide(CircleCollision& position, BoxCollision& collision);
	void ResolveBallCollision(BoxCollision* collidedRect);
	void Move();
};