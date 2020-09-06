#include "Window.h"
#include <iostream>

Window::Window(Vector2 size, bool fullscreeen) 
    : m_gameOver(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    ilInit();
	//window 

	Uint32 flag = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | (fullscreeen ? SDL_WINDOW_FULLSCREEN : 0);

	m_window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, size.x, size.y, flag);

    m_resolution = size;
    Rect::SetRatio(size);

	//renderer
	TextureManager::SetRenderer(SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED));

	SDL_SetRenderDrawColor(TextureManager::GetRenderer(),0,0,0,255); //black BG
}

void Window::GameLoop()
{
    Uint32 frameEnd = 0;
    Uint32 frameStart = 0;

    while (Input::Running())
    {
        Input::Clear();
        SDL_RenderClear(TextureManager::GetRenderer());

        frameStart = SDL_GetTicks();

        if (Input::WindowEvent())
            ResizeWindow();

        Input::ProcessInput();

        Scene::GetActiveScene().Process();

        SDL_RenderPresent(TextureManager::GetRenderer());

        Scene::GetActiveScene().ProcessDestroyed();

        frameEnd = SDL_GetTicks() - frameStart;
        if (1000 / fpsLimit > frameEnd)
            SDL_Delay(1000 / fpsLimit - frameEnd);

    }
}


void Window::ResizeWindow()
{
    Rect::SetRatio(Vector2(Input::GetWindowEventValues().x, Input::GetWindowEventValues().y));
}