#include "Physics.h"
#include "Input.h"

Physics::Physics() 
	:m_speed(0),m_angle(0),m_collisionResolved(false)
{}

void Physics::Operation()
{
	if (!Input::Paused())
	{
		ResolveCollision();

		Move();
	}
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

	CircleCollision* circleCollision = dynamic_cast<CircleCollision*>(GetCircleCollision());

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

	//paddle collision with walls
	BoxCollision* bc = dynamic_cast<BoxCollision*>(GetBoxCollision());
	if(bc)
	{
		if(bc->Collided())
		{
			const Rect& rect = bc->GetCollisionRect();
			const Rect& collidedRect = bc->GetCollidedRect();
			if (m_angle == 0) //right collision
				m_parent->SetPosition(Vector2(collidedRect.x - rect.w - 1, rect.y));
			else
				m_parent->SetPosition(Vector2(collidedRect.x + collidedRect.w + 1, rect.y));
		}
	}
}

