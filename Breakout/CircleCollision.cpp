#include "CircleCollision.h"
#include "Scene.h"
#include <math.h>

CircleCollision::CircleCollision(int radius)
	:m_radius(radius), m_collided()
{
}

void CircleCollision::Operation()
{
	Collide();
}

void CircleCollision::Collide()
{
	for (Component* go : Scene::GetActiveScene().GetObjects())
	{
		BoxCollision* bc = dynamic_cast<BoxCollision*>(go->GetBoxCollision());

		std::vector<BoxCollision*>::iterator it = std::find_if(m_collided.begin(), m_collided.end(),
			[&bc](BoxCollision* x)
			{
				return x == bc;
			}
		);

		if (bc && CheckCollision(bc->GetCollisionRect()))
		{ 
			CheckCollision(bc->GetCollisionRect());
			if (it == m_collided.end())
			{
				if (m_collided.size() == 2)
				{
					int test = m_collided.size();
				}

				static_cast<GameObject*>(this->GetParent())->AllowCollisionProcess();
				OnCollisionEnter(bc);
				static_cast<GameObject*>(bc->GetParent())->AllowCollisionProcess();
				bc->OnCollisionEnter(this);

				if (!static_cast<GameObject*>(bc->GetParent())->ToDestroy())
					m_collided.push_back(bc);
			}
		}
		else if (it != m_collided.end())
		{
			OnCollisionExit(bc);
			bc->OnCollisionExit(this);
			m_collided.erase(it);
		}
	}
}

bool CircleCollision::CheckCollision(const Rect& rect)
{
	float circleDistanceX = abs((GetPosition().x + m_radius) - (rect.x + rect.w / 2));
	float circleDistanceY = abs((GetPosition().y + m_radius) - (rect.y + rect.h / 2));

	if (circleDistanceX > (rect.w / 2 + m_radius)) { return false; }
	if (circleDistanceY > (rect.h / 2 + m_radius)) { return false; }

	if (circleDistanceX <= (rect.w / 2)) { return true; }
	if (circleDistanceY <= (rect.h / 2)) { return true; }

	float closestX = (GetPosition().x < rect.x ? rect.x : (GetPosition().x > (rect.x + rect.w) ? (rect.x + rect.w) : GetPosition().x));
	float closestY = (GetPosition().y < (rect.y + rect.h) ? (rect.y + rect.h) : (GetPosition().y > rect.y ? rect.y : GetPosition().y));

	float cornerDistance_sq = pow((circleDistanceX - closestX),2) +
		pow((circleDistanceY - closestY),2);

	return (cornerDistance_sq <= pow(m_radius,2));
	return true;
}


int CircleCollision::GetRadius()
{
	return m_radius;
}


std::vector<BoxCollision*>& CircleCollision::GetColliding()
{
	return m_collided;
}