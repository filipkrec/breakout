#include "SDL.h"
#include "Window.h"

int main(int arc, char* argv[])
{
    Window* winMain = new Window(Vector2(1280, 720), false);
    Scene scene;

    TextureManager::LoadTexture("Doggie", "image.bmp");
    TextureManager::LoadText("TestTxt", "This is a test text!");

    Sprite bg(TextureManager::GetTexture("Doggie"), Vector2(500, 500), Vector2(390, 110));
    Sprite txt(TextureManager::GetTexture("TestTxt"), Vector2(100, 100), Vector2(0, 0));

    GameObject background;
    background.Add(&bg);

    GameObject text;
    text.Add(&txt);

    scene.Add(&text);
    scene.Add(&background);

    winMain->LoadScene(scene);
    winMain->GameLoop();

    SDL_Quit();
    return 0;
}