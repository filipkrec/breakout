#pragma once
#include "BoxCollision.h"
#include "Vector2.h"
#include "Line.h"
#include <cmath>
#include <vector>

class CircleCollision : public Component
{
	int m_radius;
	std::vector<BoxCollision*> m_collided;

public:
	~CircleCollision() override {}
	CircleCollision(int radius);

	void Collide();

	bool CheckCollision(const Rect& rect);

	int GetRadius();

	inline Vector2 GetPosition() const override { return m_parent->GetPosition(); }

	inline const Vector2 GetCenter() const { return Vector2(GetPosition().x + m_radius / 2, GetPosition().y + m_radius); }

	std::vector<BoxCollision*>& GetColliding();

	void Operation() override;
};