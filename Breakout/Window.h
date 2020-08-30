#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Vector2.h"
#include "TextureManager.h"
#include "Scene.h"
#include <string>

class Window
{
private:
	const Uint32 fpsLimit = 60;
	bool m_gameOver;
	SDL_Window* m_window;
	SDL_Event m_event;
	Scene m_scene;
public:
	Window(Vector2 size, bool fullscreeen);
	void GameLoop();
	void Input();
	void LoadScene(Scene& scene);
};