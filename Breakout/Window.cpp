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
    const Uint32 second = 1000;
    Uint32 frameEnd = 0;
    Uint32 frameStart = 0;
    Uint32 fps = 0;
    Uint32 secondTime = 0;
    Uint32 secondTimeLast = 0;

    TextureManager::LoadTexture("Doggie", "image.bmp");
    TextureManager::LoadText("TestTxt", "This is a test text!");

    //Sprite msg()
    Sprite bg(TextureManager::GetTexture("Doggie"), Vector2(500, 500), Vector2(390, 110));
    Sprite txt(TextureManager::GetTexture("TestTxt"), Vector2(100, 100), Vector2(0, 0));

    while (!m_gameOver)
    {
        SDL_RenderClear(TextureManager::GetRenderer());
        frameStart = SDL_GetTicks();

        secondTime = SDL_GetTicks() - secondTimeLast;

        bg.Render();
        txt.Render();

        fps++;

        if (SDL_PollEvent(&m_event)) {
            switch (m_event.type) {
            case SDL_QUIT:
                m_gameOver = 1;
                break;

            case SDL_KEYDOWN:
                switch (m_event.key.keysym.sym) {
                case SDLK_ESCAPE:
                case SDLK_q:
                    m_gameOver = 1;
                    break;
                }
                break;
            }
        }

        if (secondTime >= 1000)
        {
            //SDL_DestroyTexture(msg);
            secondTimeLast = SDL_GetTicks();
            //msg = AddText(std::to_string(fps), Vector2(0, 0), 100);
            fps = 0;
        }

        SDL_RenderPresent(TextureManager::GetRenderer());
        frameEnd = SDL_GetTicks() - frameStart;

        if (1000 / 60 > frameEnd)
            SDL_Delay(1000 / 60 - frameEnd);

    }
}