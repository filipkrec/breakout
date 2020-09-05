#include "Physics.h"
#include <iostream>

Physics::Physics() 
	:m_speed(0),m_angle(0),m_collisionResolved(false)
{}

void Physics::Operation()
{
	ResolveCollision();

	Move();
}

void Physics::SetSpeed(int units)
{
	m_speed = units;
}

void Physics::SetAngle(int degrees)
{
	m_angle = degrees;
}

bool Physics::CollidingLineHorizontal(Vector2 position, BoxCollision& collision)
{
	Rect rect = collision.GetCollisionRect();

	if (position.x < rect.x || position.x >(rect.x + rect.w))
		return false;

	return true;
}

void Physics::ResolveCollision()
{
	const int maxSpeed = 25;
	const int bonusSpeedDivider = 10;

	Component* collision = m_parent->GetCollision();

	CircleCollision* circleCollision = dynamic_cast<CircleCollision*>(collision);

	if (!circleCollision)
		return;

	std::vector<BoxCollision*>& rects = circleCollision->GetColliding();


	if (!rects.empty())
	{
		if (!m_collisionResolved)
		{
			m_collisionResolved = true;
			for (BoxCollision* collidingBox : rects)
			{

				Vector2 circleCenter;
				circleCenter.x = (circleCollision->GetPosition().x + circleCollision->GetRadius());
				circleCenter.y = (circleCollision->GetPosition().y + circleCollision->GetRadius());
				CollidingLineHorizontal(circleCenter, *collidingBox);

				Vector2 otherVec;

				Physics* otherPhys = (Physics*)collidingBox->GetParent()->GetPhysics();
				if (otherPhys != nullptr)
				{
					otherVec = Vector2::AngleToVec(otherPhys->m_angle);
					otherVec.Multiply((otherPhys->m_speed / bonusSpeedDivider));
				}

				Vector2 newVec = Vector2::AngleToVec(m_angle);
				newVec.Multiply(m_speed);

				if (CollidingLineHorizontal(circleCenter, *collidingBox))
				{
					newVec.y = -newVec.y;
					newVec.x += otherVec.x;
				}
				else //vertical
				{
					newVec.x = -newVec.x;
					newVec.x += otherVec.x;
				}

				m_speed = Vector2::Length(newVec) > maxSpeed ? maxSpeed : Vector2::Length(newVec);
				m_angle = Vector2::VecToAngle(newVec);
			}
		}
	}
	else
		m_collisionResolved = false;
}

void Physics::Move()
{
	Vector2 moveVector = Vector2::AngleToVec(m_angle);
	moveVector.Multiply(m_speed);

	m_parent->Translate(moveVector);
}

