#pragma once
#include "Component.h"

class WallBottom :public Component
{
	void OnCollisionEnter(Component* other) override;

	void Operation() override {};

	~WallBottom() override {};
};