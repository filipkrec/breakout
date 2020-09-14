#include "Window.h"
#include "Level.h"
#include <iostream>

Window::Window()
    : m_gameOver(false)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    ilInit();
    //window 

    Uint32 flag = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN;

    SDL_DisplayMode mode;

    SDL_GetCurrentDisplayMode(1, &mode);

    m_window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, mode.w, mode.h, flag);

    Rect::SetRatio(Vector2(mode.w, mode.h));
    Rect::SetResolutionRatio(Vector2(mode.w, mode.h));

    //renderer
    TextureManager::GetManager()->SetRenderer(SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED));

    SDL_SetRenderDrawColor(TextureManager::GetManager()->GetRenderer(), 0, 0, 0, 255); //black BG
}

Window::Window(Vector2 size) 
    : m_gameOver(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    ilInit();
	//window 

	Uint32 flag = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	m_window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, static_cast<int>(size.x), static_cast<int>(size.y), flag);

    Rect::SetRatio(size);
    Rect::SetResolutionRatio(size);

	//renderer
	TextureManager::GetManager()->SetRenderer(SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED));

	SDL_SetRenderDrawColor(TextureManager::GetManager()->GetRenderer(),0,0,0,255); //black BG
}

void Window::GameLoop()
{
    Uint32 frameEnd = 0;
    Uint32 frameStart = 0;

    while (Input::Running())
    {
        Input::Clear();
        SDL_RenderClear(TextureManager::GetManager()->GetRenderer());

        frameStart = SDL_GetTicks();

        if (Input::WindowEvent())
            ResizeWindow();

        Input::ProcessInput();

        Scene::GetActiveScene().Process();

        SDL_RenderPresent(TextureManager::GetManager()->GetRenderer());

        frameEnd = SDL_GetTicks() - frameStart;
        if (1000 / fpsLimit > frameEnd)
            SDL_Delay(1000 / fpsLimit - frameEnd);

    }
}


void Window::ResizeWindow()
{
    Rect::SetRatio(Vector2(Input::GetWindowEventValues().x,Input::GetWindowEventValues().y));
}