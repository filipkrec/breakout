#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

struct Vector2
{
	int x;
	int y;

	Vector2() { x = 0; y = 0; }
	Vector2(int X, int Y) { x = X; y = Y; }

	static Vector2 Zero() { return Vector2(0, 0); }

	static int DistanceSqr(Vector2 A, Vector2 B) { return pow(A.x - B.x, 2) + pow(A.y - B.y, 2); }
	static Vector2 minDistance(Vector2 Origin, Vector2 A, Vector2 B) { return DistanceSqr(Origin, A) < DistanceSqr(Origin, B) ? A : B; }

	static float toRadians(int degrees)
	{
		return degrees * (M_PI / 180.0f);
	}

	static int toDegrees(float radians)
	{
		return radians * (180.0f / M_PI);
	}

	static int Length(Vector2 vec)
	{
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	static int VecToAngle(const Vector2& vectorDistanceToOther)
	{
		float rads = std::atan2(vectorDistanceToOther.y , vectorDistanceToOther.x);
		return toDegrees(rads);
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

	Vector2& Multiply(int X)
	{
		x *= X;
		y *= X;
		return *this;
	}
};