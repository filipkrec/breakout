#pragma once
#include "SDL.h";
#include "Vector2.h"
#include "TextureManager.h"
#include "Component.h"

class Sprite : public Component
{
	SDL_Texture* m_texture;
	SDL_Rect m_rect;

public:
	Sprite(SDL_Texture* texture, Vector2 size, Vector2 position);

	void Render();

	void Operation() override;
};