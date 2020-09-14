#include "SDL.h"
#include "Window.h"
#include "Button.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "SceneLoader.h"
#include <fstream>

int main(int arc, char* argv[])
{
    Window* winMain = new Window(Vector2(800,500));
    
    SceneLoader::LoadMenu();

    winMain->GameLoop();

    SDL_Quit();
    return 0;
}

