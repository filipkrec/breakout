#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture, Vector2 size)
	: m_texture(texture), m_rect(Rect( Vector2(0, 0), Vector2(size.x, size.y )))
{
}

Sprite::Sprite(Sprite& other)
	:m_texture(other.m_texture), m_rect(other.m_rect)
{
}

void Sprite::Render()
{
	m_rect.x = GetPosition().x;
	m_rect.y = GetPosition().y;
	SDL_RenderCopy(TextureManager::GetManager()->GetRenderer(), m_texture, NULL, &m_rect.SDLRect());
}

void Sprite::Operation()
{
	Render();
}

Vector2 Sprite::GetPosition()
{
	return m_parent->GetPosition();
}

void Sprite::SetSize(Vector2 size)
{
	m_rect.w = size.x;
	m_rect.h = size.y;
}