#include "CircleCollision.h"
#include "Scene.h"

CircleCollision::CircleCollision(int radius)
	:m_radius(radius), m_colliding()
{
}

void CircleCollision::Collide()
{
	m_colliding.clear();

	for (Component* go : Scene::GetActiveScene().GetObjects())
	{
		Component* collision = go->GetCollision();

		BoxCollision* bc = nullptr;

		if (typeid(collision) == typeid(BoxCollision))
			bc == (BoxCollision*)collision;

		if (bc && CheckCollision(bc->GetCollisionRect()))
		{
			m_colliding.push_back(bc);
		}
	}
}


bool CircleCollision::CheckCollision(const SDL_Rect& rect)
{
	int circleDistanceX = abs(GetPosition().x - rect.x);
	int circleDistanceY = abs(GetPosition().y - rect.y);

	if (circleDistanceX > (rect.w / 2 + m_radius)) { return false; }
	if (circleDistanceY > (rect.h / 2 + m_radius)) { return false; }

	if (circleDistanceX <= (rect.w / 2)) { return true; }
	if (circleDistanceY <= (rect.h / 2)) { return true; }

	int cornerDistance = (int)pow((circleDistanceX - rect.w / 2), 2) +
		(int)pow((circleDistanceY - rect.h / 2),2);

	return (cornerDistance <= (m_radius ^ 2));
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