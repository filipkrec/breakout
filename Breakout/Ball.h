#pragma once
#include "GameObject.h"

class Ball : public GameObject
{
public:
	Ball();

	void SetSpeed(int speed);
	void SetAngle(int angle);
private:
	void Update() override;
};