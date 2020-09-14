#include "Rect.h"

float Rect::m_ratioX;
float Rect::m_ratioY;
Vector2 Rect::m_resolution;
Vector2 Rect::m_resolutionRatio;

Rect::Rect()
	:x(0),y(0),w(0),h(0)
{}

Rect::Rect(Vector2 position, Vector2 size)
{
	x = static_cast<int>(position.x);
	y = static_cast<int>(position.y);
	w = static_cast<int>(size.x);
	h = static_cast<int>(size.y);
}

const SDL_Rect Rect::SDLRect() const
{
	return SDL_Rect{
		(int)((float)x * m_ratioX),
		(int)((float)(m_resolutionRatio.y - y - h) * m_ratioY),
		(int)((float)w * m_ratioX),
		(int)((float)h * m_ratioY) };
}

void Rect::SetRatio(Vector2 resolution, bool setResolution)
{
	if(setResolution)
		m_resolution = resolution;

	m_ratioX = (float)resolution.x / m_resolutionRatio.x;
	m_ratioY = (float)resolution.y / m_resolutionRatio.y;
}

void Rect::SetResolutionRatio(Vector2 resolution, bool setResolution)
{
	int screenRatioInt = static_cast<int>(round(resolution.x / resolution.y * 100));

	if (screenRatioInt == 133)
	{
		m_resolutionRatio.x =  1200;
		m_resolutionRatio.y =  900;
	}
	else if (screenRatioInt == 160)
	{
		m_resolutionRatio.x =  1600;
		m_resolutionRatio.y =  1000;
	}
	else if (screenRatioInt == 185)
	{
		m_resolutionRatio.x =  1850;
		m_resolutionRatio.y =  1000;
	}
	else if (screenRatioInt == 210)
	{
		m_resolutionRatio.x =  2100;
		m_resolutionRatio.y =  1000;
	}
	else
	{
		m_resolutionRatio.x =  1600;
		m_resolutionRatio.y =  900;
	}

	SetRatio(m_resolution, setResolution);
}