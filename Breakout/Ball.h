#pragma once
#include "GameObject.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "CircleCollision.h"
#include "Physics.h"

class Ball : public GameObject
{
public:
	Ball();
private:
	void Update() override;
};