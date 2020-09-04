#include "Physics.h"

void Physics::Operation()
{
	ResolveCollision();
	Move();
}

Line Physics::GetCollidingLine(Vector2 position, const BoxCollision& collision)
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
	CircleCollision* collision = ((GameObject*)m_parent)->GetComponent<CircleCollision>();

	if (collision == nullptr) return;

	std::vector<BoxCollision*>& rects = collision->GetColliding();

	for (BoxCollision* collidingBox : rects)
	{
		Line collidingLine = GetCollidingLine(collision->GetPosition(), *collidingBox);

		Vector2 otherVec;

		Physics* otherPhys = ((GameObject*)collidingBox->GetParent())->GetComponent<Physics>();
		if (otherPhys != nullptr)
		{
			otherVec = Vector2::AngleToVec(otherPhys->angle);
			otherVec.Multiply(otherPhys->speed);
		}

		Vector2 newVec = Vector2::AngleToVec(angle);
		newVec.Multiply(speed);

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

		speed = Vector2::Length(newVec);
		angle = Vector2::VecToAngle(newVec);
	}
}

void Physics::Move()
{
	Vector2 moveVector = Vector2::AngleToVec(angle);
	moveVector.Multiply(speed);

	((GameObject*)m_parent)->Move(moveVector);
}


template <class T>
T* GameObject::GetComponent()
{
	return nullptr;
}

