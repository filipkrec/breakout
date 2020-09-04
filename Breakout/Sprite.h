#pragma once
#include "SDL.h";
#include "Vector2.h"
#include "TextureManager.h"
#include "Rect.h"
#include "Component.h"

class Sprite : public Component
{
	SDL_Texture* m_texture;
	Rect m_rect;

public:
	Sprite(SDL_Texture* texture, Vector2 size);

	void Render();

	Vector2 GetPosition();

	void Operation() override;
};