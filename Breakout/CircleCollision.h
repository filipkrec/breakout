#pragma once
#include "BoxCollision.h"
#include "Vector2.h"
#include "Line.h"
#include <cmath>
#include <vector>

class CircleCollision : public Component
{
	int m_radius;
	std::vector<BoxCollision*> m_colliding;

public:
	CircleCollision(int radius);

	void Collide();

	bool CheckCollision(const SDL_Rect& rect);

	int GetRadius();

	Vector2 GetPosition();

	std::vector<BoxCollision*>& GetColliding();

	void Operation() override {}
};