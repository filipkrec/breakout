#include "BoxCollision.h"
#include "Scene.h"

BoxCollision::BoxCollision(Vector2 size)
	:m_rect(Rect(Vector2::Zero(),size))
{
}

BoxCollision::BoxCollision(BoxCollision& other)
	:m_rect(other.m_rect)
{

}

const Rect& BoxCollision::GetCollisionRect()
{
	m_rect.x = m_parent->GetPosition().x;
	m_rect.y = m_parent->GetPosition().y;
	return m_rect;
}

const Rect& BoxCollision::GetCollidedRect() const
{
	return m_collidedRect;
}


bool BoxCollision::Collided()
{
	for (Component* go : Scene::GetActiveScene().GetObjects())
	{
		if (go == m_parent)
			continue;

		BoxCollision* bc = dynamic_cast<BoxCollision*>(go->GetBoxCollision());

		if (bc && CheckCollision(bc->GetCollisionRect()))
		{
			m_collidedRect = bc->GetCollisionRect();
			return true;
		}
	}
	return false;
}


bool BoxCollision::CheckCollision(const Rect& rect)
{
	if(GetPosition().x < rect.x + rect.w &&
		GetPosition().x + m_rect.w> rect.x &&
		GetPosition().y < rect.y + rect.h &&
		GetPosition().y + m_rect.w > rect.y)
		return true;
	
	return false;
}

