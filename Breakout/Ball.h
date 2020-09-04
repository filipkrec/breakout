#pragma once
#include "GameObject.h"

class Ball : public GameObject
{
	Ball();
private:
	void Update() override;
};