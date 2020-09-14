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
		if (Scene::GetActiveScene().InteruptIteration()) return; //if scene altered while iterating

		if(!go->Active()) continue;

		BoxCollision* bc = dynamic_cast<BoxCollision*>(go->GetBoxCollision());
		BoxCollision* collidedExists = nullptr;

		for (BoxCollision* x: m_collided)
		{
			if (x == bc)
			{
				collidedExists = x;
				break;
			}
		}

		if (bc && CheckCollision(bc->GetCollisionRect()))
		{

			CheckCollision(bc->GetCollisionRect());
			if (!collidedExists)
			{
				if (m_collided.size() == 2)
				{
					int test = static_cast<int>(m_collided.size());
				}

				static_cast<GameObject*>(this->GetParent())->AllowCollisionProcess();
				OnCollisionEnter(bc);
				static_cast<GameObject*>(bc->GetParent())->AllowCollisionProcess();
				bc->OnCollisionEnter(this);

				if (!static_cast<GameObject*>(bc->GetParent())->ToDestroy())
					m_collided.push_back(bc);
			}
		}
		else if (collidedExists)
		{
			OnCollisionExit(bc);
			bc->OnCollisionExit(this);
			m_collided.erase(
				std::remove_if(m_collided.begin(), m_collided.end(),
					[&](const BoxCollision* x) {
						return x == collidedExists;
					}),
				m_collided.end());
		}
	}
}

bool CircleCollision::CheckCollision(const Rect& rect)
{
	const float circleCenterX = (GetPosition().x + m_radius);
	const float circleCenterY = (GetPosition().y + m_radius);

	float circleDistanceX = abs(circleCenterX - (rect.x + rect.w / 2));
	float circleDistanceY = abs(circleCenterY - (rect.y + rect.h / 2));

	if (circleDistanceX > (rect.w / 2 + m_radius)) { return false; }
	if (circleDistanceY > (rect.h / 2 + m_radius)) { return false; }

	if (circleDistanceX <= (rect.w / 2)) { return true; }
	if (circleDistanceY <= (rect.h / 2)) { return true; }

	float closestX = (circleCenterX < rect.x ? rect.x : (circleCenterX > (rect.x + rect.w) ? (rect.x + rect.w) : circleCenterX));
	float closestY = (circleCenterY > (rect.y + rect.h) ? (rect.y + rect.h) : (circleCenterY < rect.y ? rect.y : circleCenterY));

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