#include "Vector2.h"
#define _USE_MATH_DEFINES
#include <cmath>

Vector2::Vector2() { x = 0; y = 0; }
Vector2::Vector2(float X, float Y) { x = X; y = Y; }
Vector2::Vector2(int X, int Y) { x = static_cast<float>(X); y = static_cast<float>(Y); }

Vector2 Vector2::Zero() { return Vector2(0, 0); }

float Vector2::DistanceSqr(Vector2 A, Vector2 B) { return pow(A.x - B.x, 2) + pow(A.y - B.y, 2); }
Vector2 Vector2::minDistance(Vector2 Origin, Vector2 A, Vector2 B) { return DistanceSqr(Origin, A) < DistanceSqr(Origin, B) ? A : B; }

float Vector2::toRadians(float degrees)
{
	const double pi = M_PI;
	return degrees * (static_cast<float>(pi) / 180.0f);
}

float Vector2::toDegrees(float radians)
{
	const double pi = M_PI;
	return radians * (180.0f / static_cast<float>(pi));
}

float Vector2::Length(Vector2 vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float Vector2::VecToAngle(const Vector2& vectorDistanceToOther)
{
	float rads = std::atan2(vectorDistanceToOther.y, vectorDistanceToOther.x);
	float deg = toDegrees(rads);
	if (deg < 0)
		deg = 360.0f + deg;

	return deg;
}

Vector2 Vector2::AngleToVec(float angle)
{
	float rads = toRadians(angle);
	Vector2 result;
	float x = cos(rads);
	float y = sin(rads);
	result.x = x;
	result.y = y;

	return result;
}

Vector2& Vector2::Multiply(float X)
{
	x *= X;
	y *= X;
	return *this;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(other.x + x, other.y + y);
}

Vector2 Vector2::operator*(const Vector2& other) const
{
	return Vector2(other.x * x, other.y * y);
}

Vector2 Vector2::operator*(const float other) const
{
	return Vector2(other * x, other * y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

const Vector2 Vector2::operator/(const Vector2& other) const
{
	return Vector2(x / other.x, y / other.y);
}

const Vector2 Vector2::operator/(float other) const
{
	return Vector2(x / other, y / other);
}

bool Vector2::operator==(const Vector2& other) const
{
	return other.x == x && other.y == y;
}

bool Vector2::operator!=(const Vector2& other) const
{
	return other.x != x || other.y != y;
}