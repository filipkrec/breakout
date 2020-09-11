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

public:
	~Physics() override {}
	Physics();
	void Operation() override;

	inline const int GetSpeed() const { return m_speed; }
	inline const float GetAngle() const { return m_angle; }
	void SetSpeed(int units);
	void SetAngle(float degrees);

	void OnCollisionEnter(Component* collidedOther) override;

private:
	void ResolveBallCollision(BoxCollision* collidedRect);
	void Move();
};