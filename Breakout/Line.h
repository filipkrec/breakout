#pragma once
#include "Vector2.h"

struct Line
{
	Vector2 a;
	Vector2 b;
	
	Line() { a = Vector2::Zero(); b = Vector2::Zero(); }
	Line(Vector2 A, Vector2 B) { a = A; b = B; }
};