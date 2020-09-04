#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture, Vector2 size)
	: m_texture(texture), m_rect(SDL_Rect{ 0, 0, size.x, size.y })
{
}

void Sprite::Render()
{
	m_rect.x = GetPosition().x;
	m_rect.y = GetPosition().y;
	SDL_RenderCopy(TextureManager::GetRenderer(), m_texture, NULL, &m_rect);
}

void Sprite::Operation()
{
	Render();
}

Vector2 Sprite::GetPosition()
{
	return m_parent->GetPosition();
}