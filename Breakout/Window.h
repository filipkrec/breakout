#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Vector2.h"
#include "TextureManager.h"
#include "Scene.h"
#include "Sprite.h"
#include "Input.h"
#include <string>

class Window
{
private:
	const Uint32 fpsLimit = 60;
	bool m_gameOver;
	SDL_Window* m_window;
	Scene m_scene;
public:
	Window(Vector2 size, bool fullscreeen);
	void GameLoop();
	void LoadScene(Scene& scene);
	Scene& GetActiveScene();
};