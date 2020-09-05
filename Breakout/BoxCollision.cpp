#include "BoxCollision.h"

BoxCollision::BoxCollision(Vector2 size)
	:m_rect(Rect(Vector2::Zero(),size))
{
}

const Rect& BoxCollision::GetCollisionRect()
{
	m_rect.x = m_parent->GetPosition().x;
	m_rect.y = m_parent->GetPosition().y;
	return m_rect;
}