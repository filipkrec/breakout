#include "SDL.h"
#include "Window.h"

int main(int arc, char* argv[])
{
    Window* winMain = new Window(Vector2(1280, 720), false);

    winMain->GameLoop();

    SDL_Quit();
    return 0;
}