#pragma once
#include "SDL.h";
#include "Vector2.h"
#include "TextureManager.h"
#include "Rect.h"
#include "Component.h"

class Text : public Component
{
	const int m_size = 144;

	std::string m_text;
	SDL_Color m_color;

	SDL_Texture* m_texture;
	Vector2 m_offset;
	Rect m_rect;

public:
	~Text() override {}

	Text(std::string text, Vector2 size, const SDL_Color& color = {255,255,255}, Vector2 offset = Vector2::Zero());

	void Render();

	Vector2 GetPosition();

	void SetSize(Vector2 size);

	void SetOffset(Vector2 offset);

	void SetText(std::string text);
	void SetColor(SDL_Color color);

	void Operation() override;
};