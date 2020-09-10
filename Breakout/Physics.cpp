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

Physics::Side Physics::GetCollidingSide(CircleCollision& circle, BoxCollision& collision)
{
 	Rect rect = collision.GetCollisionRect();

	Vector2 circleCenter(circle.GetPosition().x + circle.GetRadius(), circle.GetPosition().y + circle.GetRadius());
	Vector2 rectCenter = Vector2(rect.x + rect.w / 2, rect.y + rect.h / 2);
	float angle = Vector2::VecToAngle(Vector2(circleCenter.x - rectCenter.x, circleCenter.y - rectCenter.y));
	
	float rectAngleA = Vector2::VecToAngle(Vector2(rect.x - rectCenter.x, rect.y - rectCenter.y));
	float rectAngleB = Vector2::VecToAngle(Vector2(rect.x + rect.w - rectCenter.x, rect.y - rectCenter.y));
	float rectAngleC = Vector2::VecToAngle(Vector2(rect.x + rect.w - rectCenter.x, rect.y + rect.h - rectCenter.y));
	float rectAngleD = Vector2::VecToAngle(Vector2(rect.x - rectCenter.x, rect.y + rect.h - rectCenter.y));
																									    
	if (angle >= rectAngleA && angle <= rectAngleB)
		return Side::BOTTOM;
	else if
		(angle >= rectAngleC && angle <= rectAngleD)
		return Side::TOP;
	else if
		(angle > rectAngleD && angle < rectAngleA)
		return Side::LEFT;
	else
		return Side::RIGHT;
}

void Physics::ResolveBallCollision(BoxCollision* collidedRect)
{
	CircleCollision* thisCircle = dynamic_cast<CircleCollision*>(GetCircleCollision());

	if (!thisCircle)
		return;

	const int maxSpeed = 25;
	const int bonusSpeed = 1;


	Vector2 newVec = Vector2::AngleToVec(m_angle);

	switch (GetCollidingSide(*thisCircle, *collidedRect))
	{
	case Side::TOP : 
		newVec.y = newVec.y > 0 ? newVec.y : -newVec.y;
		break;
	case Side::BOTTOM:
		newVec.y = newVec.y < 0 ? newVec.y : -newVec.y;
		break;
	case Side::RIGHT:
		newVec.x = newVec.x > 0 ? newVec.x : -newVec.x;
		break;
	case Side::LEFT:
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
