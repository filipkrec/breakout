#include "CircleCollision.h"
#include "Scene.h"

CircleCollision::CircleCollision(int radius)
	:m_radius(radius), m_colliding()
{
}

void CircleCollision::Operation()
{
	Collide();
}

void CircleCollision::Collide()
{
	m_colliding.clear();

	for (Component* go : Scene::GetActiveScene().GetObjects())
	{
		BoxCollision* bc = dynamic_cast<BoxCollision*>(go->GetBoxCollision());

		if (bc && CheckCollision(bc->GetCollisionRect()))
		{
			m_colliding.push_back(bc);
		}
	}
}


bool CircleCollision::CheckCollision(const Rect& rect)
{
	int circleDistanceX = abs((GetPosition().x + m_radius) - (rect.x + rect.w / 2));
	int circleDistanceY = abs((GetPosition().y + m_radius) - (rect.y + rect.h / 2));

	if (circleDistanceX > (rect.w / 2 + m_radius)) { return false; }
	if (circleDistanceY > (rect.h / 2 + m_radius)) { return false; }

	return true;
}


int CircleCollision::GetRadius()
{
	return m_radius;
}

Vector2 CircleCollision::GetPosition()
{
	return ((GameObject*)m_parent)->GetPosition();
}


std::vector<BoxCollision*>& CircleCollision::GetColliding()
{
	return m_colliding;
}