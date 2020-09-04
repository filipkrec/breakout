#include "Physics.h"

Physics::Physics() 
	:m_speed(0),m_angle(0)
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

Line Physics::GetCollidingLine(Vector2 position, BoxCollision& collision)
{
	SDL_Rect rect = collision.GetCollisionRect();
	Vector2 A = Vector2(rect.x, rect.y);
	Vector2 B = Vector2(rect.x + rect.w, rect.y);
	Vector2 C = Vector2(rect.x + rect.w, rect.y + rect.h);
	Vector2 D = Vector2(rect.x, rect.y + rect.h);

	if (position.x < A.x)
		return Line(D, A);
	else if (position.x > C.x)
		return Line(C, B);
	else if (position.y > C.y)
		return Line(D, C);
	else if (position.y < A.y)
		return Line(B, A);
}

void Physics::ResolveCollision()
{
	Component* collision = m_parent->GetCollision();

	if(typeid(collision) != typeid(CircleCollision*))
		return;

	CircleCollision* circleCollision = (CircleCollision*)collision;

	std::vector<BoxCollision*>& rects = circleCollision->GetColliding();

	if(!rects.empty())
	for (BoxCollision* collidingBox : rects)
	{
		Line collidingLine = GetCollidingLine(circleCollision->GetPosition(), *collidingBox);

		Vector2 otherVec;

		Physics* otherPhys = (Physics*)collidingBox->GetParent()->GetPhysics();
		if (otherPhys != nullptr)
		{
			otherVec = Vector2::AngleToVec(otherPhys->m_angle);
			otherVec.Multiply(otherPhys->m_speed);
		}

		Vector2 newVec = Vector2::AngleToVec(m_angle);
		newVec.Multiply(m_speed);

		if (collidingLine.a.x == collidingLine.b.x) //horizontal
		{
			newVec.y = -newVec.y;
			newVec.x += otherVec.x;
		}
		else //vertical
		{
			newVec.x = -newVec.x;
			newVec.x += otherVec.x;
		}

		m_speed = Vector2::Length(newVec);
		m_angle = Vector2::VecToAngle(newVec);
	}
}

void Physics::Move()
{
	Vector2 moveVector = Vector2::AngleToVec(m_angle);
	moveVector.Multiply(m_speed);

	m_parent->Translate(moveVector);
}

