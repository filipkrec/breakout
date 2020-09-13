#pragma once
#include "SDL.h"
#include "Vector2.h"

class Rect
{
	static float m_ratioX;
	static float m_ratioY;
	static Vector2 m_resolutionRatio;
	static Vector2 m_resolution;


public:
	int x;
	int y;
	int w;
	int h;

	Rect();
	Rect(Vector2 position, Vector2 size);
	const SDL_Rect SDLRect() const;
	static void SetRatio(Vector2 resolution, bool setResolution = true);
	static void SetResolutionRatio(Vector2 resolution, bool setResolution = true);
	static const Vector2 GetScreenCenter() { return Vector2(m_resolutionRatio.x / 2, m_resolutionRatio.y / 2); }

	static const Vector2 GetResolutionRatio() { return m_resolutionRatio; }
};