#include "BoxCollision.h"

BoxCollision::BoxCollision(Vector2 size)
	:m_rect(SDL_Rect{0,0,size.x,size.y})
{
}

const SDL_Rect& BoxCollision::GetCollisionRect()
{
	m_rect.x = m_parent->GetPosition().x;
	m_rect.y = m_parent->GetPosition().y;
	return m_rect;
}