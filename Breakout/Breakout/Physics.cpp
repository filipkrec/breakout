#include "Physics.h"
#include "Input.h"

Physics::Physics() 
	:m_speed(0),m_angle(0),m_collisionResolved(false)
{}

void Physics::Operation()
{
	if (!Input::Paused())
	{
		Move();
	}
}

void Physics::SetSpeed(int units)
{
	m_speed = units;
}

void Physics::SetAngle(float degrees)
{
	m_angle = degrees;
}

void Physics::ResolveBallCollision(BoxCollision* collidedRect)
{
	CircleCollision* thisCircle = dynamic_cast<CircleCollision*>(GetCircleCollision());

	if (!thisCircle)
		return;

	Vector2 newVec = Vector2::AngleToVec(m_angle);

	switch (collidedRect->GetCollidingSide(*thisCircle))
	{
	case BoxCollision::Side::TOP : 
		newVec.y = newVec.y > 0 ? newVec.y : -newVec.y;
		break;
	case BoxCollision::Side::BOTTOM:
		newVec.y = newVec.y < 0 ? newVec.y : -newVec.y;
		break;
	case BoxCollision::Side::RIGHT:
		newVec.x = newVec.x > 0 ? newVec.x : -newVec.x;
		break;
	case BoxCollision::Side::LEFT:
		newVec.x = newVec.x < 0 ? newVec.x : -newVec.x;
		break;
	}

	m_angle = Vector2::VecToAngle(newVec);
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

void Physics::OnCollisionEnter(Component* collidedOther)
{
	CircleCollision* thisCircle = dynamic_cast<CircleCollision*>(GetCircleCollision());
	BoxCollision* otherBox = dynamic_cast<BoxCollision*>(collidedOther);

	if (thisCircle && otherBox)
	{
		ResolveBallCollision(otherBox);
	}
}