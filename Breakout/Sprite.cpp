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
	m_rect.x = static_cast<int>(GetPosition().x);
	m_rect.y = static_cast<int>(GetPosition().y);
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
	m_rect.w = static_cast<int>(size.x);
	m_rect.h = static_cast<int>(size.y);
}