#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Physics.h"
#include "BoxCollision.h"
#include "TextureManager.h"

class Paddle : public GameObject 
{
public:
	Paddle();
private:
	void Update() override;

};