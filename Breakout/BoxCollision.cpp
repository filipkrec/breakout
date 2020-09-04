#include "BoxCollision.h"

BoxCollision::BoxCollision(Vector2 size, Vector2 position)
	:m_rect(SDL_Rect{position.x,position.y,size.x,size.y})
{
}

const SDL_Rect& BoxCollision::GetCollisionRect() const
{
	return m_rect;
}