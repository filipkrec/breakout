#include "SDL.h"
#include "Window.h"
#include "Paddle.h"

int main(int arc, char* argv[])
{
    Window* winMain = new Window(Vector2(1280, 720), false);
    Scene scene;

    TextureManager::LoadTexture("Doggie", "image.bmp");
    TextureManager::LoadText("TestTxt", "This is a test text!");

    Sprite bg(TextureManager::GetTexture("Doggie"), Vector2(1280, 720));
    Sprite txt(TextureManager::GetTexture("TestTxt"), Vector2(100, 100));

    GameObject background(Vector2(0, 0));
    background.Add(&bg);

    GameObject text(Vector2(0,0));
    text.Add(&txt);

    Paddle paddle;

    scene.Add(&text);
    scene.Add(&background);
    scene.Add(&paddle);

    winMain->LoadScene(scene);
    winMain->GameLoop();

    SDL_Quit();
    return 0;
}

