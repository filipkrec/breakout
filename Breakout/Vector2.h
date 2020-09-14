#pragma once

struct Vector2
{
	float x;
	float y;

	Vector2();
	Vector2(float X, float Y);
	Vector2(int X, int Y);

	static Vector2 Zero();

	static float DistanceSqr(Vector2 A, Vector2 B);
	static Vector2 minDistance(Vector2 Origin, Vector2 A, Vector2 B);

	static float toRadians(float degrees);

	static float toDegrees(float radians);

	static float Length(Vector2 vec);

	static float VecToAngle(const Vector2& vectorDistanceToOther);

	static Vector2 AngleToVec(float angle);

	Vector2& Multiply(float X);

	Vector2 operator+(const Vector2& other) const;

	Vector2 operator*(const Vector2& other) const;

	Vector2 operator*(const float other) const;

	Vector2 operator-(const Vector2& other) const;

	const Vector2 operator/(const Vector2& other) const;

	const Vector2 operator/(float other) const;

	bool operator==(const Vector2& other) const;

	bool operator!=(const Vector2& other) const;
};