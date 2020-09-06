#pragma once
#include "GameObject.h"

class Ball : public GameObject
{
public:
	Ball();
private:
	void Update() override;
};