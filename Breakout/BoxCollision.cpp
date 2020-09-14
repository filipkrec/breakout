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
	m_rect.x = static_cast<int>(m_parent->GetPosition().x);
	m_rect.y = static_cast<int>(m_parent->GetPosition().y);
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


bool BoxCollision::CheckPointCollision(const Vector2& point)
{
	const SDL_Rect& rect = GetCollisionRect().SDLRect();
	if (point.x >= rect.x && point.x <= rect.x + rect.w && point.y >= rect.y && point.y <= rect.y + rect.h)
		return true;

	return false;
}

void BoxCollision::SetSize(Vector2 size)
{
	m_rect.w = static_cast<int>(size.x);
	m_rect.h = static_cast<int>(size.y);
}


BoxCollision::Side BoxCollision::GetCollidingSide(Component& circleComp)
{
	Rect rect = GetCollisionRect();

	CircleCollision* circle = dynamic_cast<CircleCollision*>(&circleComp);

	Vector2 circleCenter(circle->GetPosition().x + circle->GetRadius(), circle->GetPosition().y + circle->GetRadius());
	Vector2 rectCenter = Vector2(rect.x + rect.w / 2, rect.y + rect.h / 2);

	Physics* phys = dynamic_cast<Physics*>(circle->GetPhysics());

	if (phys) //calc tunneling prevention
	{
		Vector2 backtrackVec = Vector2::AngleToVec(phys->GetAngle()) * static_cast<float>(-phys->GetSpeed());
		float radius = static_cast<float>(circle->GetRadius());
		float circleDistanceX = abs((circleCenter.x + radius) - (rect.x + rect.w / 2));
		float circleDistanceY = abs((circleCenter.y + radius) - (rect.y + rect.h / 2));
		while (circleDistanceX < radius + rect.w/2 && circleDistanceY < radius + rect.h/2)
		{
			circleCenter = circleCenter + backtrackVec / 10;
			circleDistanceX = abs((circleCenter.x + radius) - (rect.x + rect.w / 2));
			circleDistanceY = abs((circleCenter.y + radius) - (rect.y + rect.h / 2));
		}
	}

	float angle = Vector2::VecToAngle(Vector2(circleCenter.x - rectCenter.x, circleCenter.y - rectCenter.y));

	float rectAngleA = Vector2::VecToAngle(Vector2(rect.x - rectCenter.x, rect.y - rectCenter.y));
	float rectAngleB = Vector2::VecToAngle(Vector2(rect.x + rect.w - rectCenter.x, rect.y - rectCenter.y));
	float rectAngleC = Vector2::VecToAngle(Vector2(rect.x + rect.w - rectCenter.x, rect.y + rect.h - rectCenter.y));
	float rectAngleD = Vector2::VecToAngle(Vector2(rect.x - rectCenter.x, rect.y + rect.h - rectCenter.y));

#ifdef _DEBUG
		std::cout << GetName() << std::endl;
		std::cout << "angle " << angle << std::endl;
		std::cout << "A " << rectAngleA << std::endl;
		std::cout << "B " << rectAngleB << std::endl;
		std::cout << "C " << rectAngleC << std::endl;
		std::cout << "D " << rectAngleD << std::endl;
#endif


	if (angle > rectAngleA && angle < rectAngleB)
		return Side::BOTTOM;
	else if
		(angle > rectAngleC && angle < rectAngleD)
		return Side::TOP;
	else if
		(angle > rectAngleD && angle < rectAngleA)
		return Side::LEFT;
	else
		return Side::RIGHT;
}

