#include "SDL.h"
#include "Window.h"
#include "Button.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "SceneLoader.h"
#include <fstream>

const int unitsX = 1600;
const int unitsY = 900;

int main(int arc, char* argv[])
{
    Window* winMain = new Window(Vector2(1600, 900), false);
    
    SceneLoader::LoadMenu();

    winMain->GameLoop();

    SDL_Quit();
    return 0;
}

