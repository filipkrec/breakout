#pragma once
#include "GameObject.h"

class Paddle : public GameObject 
{
public:
	Paddle();
private:
	void Update() override;

};