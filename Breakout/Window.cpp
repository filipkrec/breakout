#include "Window.h"
#include "Sprite.h"
#include <iostream>

Window::Window(Vector2 size, bool fullscreeen) 
    : m_gameOver(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

	//window 

	Uint32 flag = SDL_WINDOW_OPENGL | (fullscreeen ? SDL_WINDOW_FULLSCREEN : 0);

	m_window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, size.x, size.y, flag);

	//renderer
	TextureManager::SetRenderer(SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED));

	SDL_SetRenderDrawColor(TextureManager::GetRenderer(),0,0,0,255); //black BG
}

void Window::GameLoop()
{
    Uint32 frameEnd = 0;
    Uint32 frameStart = 0;

    while (!Input::GameOver())
    {
        SDL_RenderClear(TextureManager::GetRenderer());

        frameStart = SDL_GetTicks();

        Input::ProcessInput();
        m_scene.Process();

        SDL_RenderPresent(TextureManager::GetRenderer());

        frameEnd = SDL_GetTicks() - frameStart;
        if (1000 / fpsLimit > frameEnd)
            SDL_Delay(1000 / fpsLimit - frameEnd);

    }
}

void Window::LoadScene(Scene& scene)
{
    m_scene = scene;
}


Scene& Window::GetActiveScene()
{
    return m_scene;
}