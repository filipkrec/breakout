#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "IL/il.h"
#include "Scene.h"
#include "Input.h"
#include <string>

class Window
{
private:
	const Uint32 fpsLimit = 60;
	bool m_gameOver;
	SDL_Window* m_window;
	Vector2 m_resolution;
public:
	Window();
	Window(Vector2 size);
	void ResizeWindow();
	void GameLoop();
};