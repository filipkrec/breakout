#pragma once
#include "GameObject.h"

class Ball : public GameObject
{
public:
	const static int m_maxSpeed = 15;
	const float m_startingAngle = 270;
	const int m_startingSpeed = 6;
	const int m_radius = 25;
public:
	~Ball() override {};
	Ball();

	void SetSpeed(int speed);
	void SetAngle(float angle);
private:
	void Update() override;
};