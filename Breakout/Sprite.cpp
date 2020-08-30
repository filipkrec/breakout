#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture, Vector2 size, Vector2 position)
	: m_texture(texture), m_rect(SDL_Rect{ position.x, position.y, size.x, size.y })
{}

void Sprite::Render()
{
	SDL_RenderCopy(TextureManager::GetRenderer(), m_texture, NULL, &m_rect);
}

void Sprite::Operation()
{
	Render();
}