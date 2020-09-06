#include "SDL.h"
#include "Window.h"
#include "Paddle.h"
#include "Ball.h"
#include "Arena.h"
#include "Brick.h"

int main(int arc, char* argv[])
{
    int unitsX = 1600;
    int unitsY = 900;
    Scene menu;



    Window* winMain = new Window(Vector2(1600, 900), false);
     

    Scene scene;

    TextureManager::LoadTexture("BGTexture", "BackgroundTexture.jpg");

    const int textureSize = 400;
    for(int x = 0; x < unitsX; x += textureSize)
        for (int y = 0; y < unitsY; y += textureSize)
        {
            Sprite* img = new Sprite(TextureManager::GetTexture("BGTexture"), Vector2(textureSize, textureSize));
            GameObject* temp = new GameObject(Vector2(x, y));
            temp->Add(img);
            scene.Add(temp);
        }


    TextureManager::LoadTexture("Doggie", "image.bmp");
    Sprite bg(TextureManager::GetTexture("Doggie"), Vector2(1050, 800));
    GameObject background(Vector2(250, 25));
    background.Add(&bg);

    TextureManager::LoadText("TestTxt", "This is a test text!");
    Sprite txt(TextureManager::GetTexture("TestTxt"), Vector2(100, 100));
    GameObject text(Vector2(0, 0));
    text.Add(&txt);

    Paddle paddle;
    Ball ball;
    Arena arena(30, 20, 3, 2, TextureManager::GetTexture("Paddle"), TextureManager::GetTexture("Doggie"));

    scene.Add(&background);
    arena.AddToScene(scene);
    scene.Add(&text);
    scene.Add(&paddle);
    scene.Add(&ball);

    Scene::LoadScene(scene);

    winMain->GameLoop();

    SDL_Quit();
    return 0;
}

