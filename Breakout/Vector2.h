#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

struct Vector2
{
	float x;
	float y;

	Vector2() { x = 0; y = 0; }
	Vector2(float X, float Y) { x = X; y = Y; }

	static Vector2 Zero() { return Vector2(0, 0); }

	static float DistanceSqr(Vector2 A, Vector2 B) { return pow(A.x - B.x, 2) + pow(A.y - B.y, 2); }
	static Vector2 minDistance(Vector2 Origin, Vector2 A, Vector2 B) { return DistanceSqr(Origin, A) < DistanceSqr(Origin, B) ? A : B; }

	static float toRadians(int degrees)
	{
		return degrees * (M_PI / 180.0f);
	}

	static float toDegrees(float radians)
	{
		return radians * (180.0f / M_PI);
	}

	static float Length(Vector2 vec)
	{
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	static float VecToAngle(const Vector2& vectorDistanceToOther)
	{
		float rads = std::atan2(vectorDistanceToOther.y , vectorDistanceToOther.x);
		float deg = toDegrees(rads);
		if (deg < 0)
			deg = 360.0f + deg;

		return deg;
	}

	static Vector2 AngleToVec(int angle)
	{
		float rads = toRadians(angle);
		Vector2 result;
		float x = cos(rads);
		float y = sin(rads);
		result.x = x;
		result.y = y;

		return result;
	}

	Vector2& Multiply(float X) 
	{
		x *= X;
		y *= X;
		return *this;
	}

	Vector2 operator+(const Vector2& other) const
	{
		return Vector2(other.x + x, other.y + y);
	}

	Vector2 operator*(const Vector2& other) const
	{
		return Vector2(other.x * x, other.y * y);
	}

	Vector2 operator*(const float other) const
	{
		return Vector2(other * x, other * y);
	}

	Vector2 operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	const Vector2 operator/(const Vector2& other) const
	{
		return Vector2(x / other.x, y / other.y);
	}

	const Vector2 operator/(float other) const
	{
		return Vector2(x / other, y / other);
	}

	bool operator==(const Vector2& other) const
	{
		return other.x == x && other.y == y;
	}

	bool operator!=(const Vector2& other) const
	{
		return other.x != x || other.y != y;
	}
};