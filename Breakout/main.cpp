#include "SDL.h"
#include "Window.h"
#include "Paddle.h"
#include "Ball.h"
#include "Arena.h"

int main(int arc, char* argv[])
{
    const int unitsX = 1600;
    const int unitsY = 900;

    Window* winMain = new Window(Vector2(1200, 720), false);
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

    GameObject wallB(Vector2(250, 25));
    wallB.Add(new Sprite(TextureManager::GetTexture("Paddle"), Vector2(1100, 50)));
    wallB.Add(new BoxCollision(Vector2(1100, 50)));

    GameObject wallT(Vector2(250, 825));
    wallT.Add(new Sprite(TextureManager::GetTexture("Paddle"), Vector2(1100, 50)));
    wallT.Add(new BoxCollision(Vector2(1100, 50)));

    GameObject wallL(Vector2(250, 25));
    wallL.Add(new Sprite(TextureManager::GetTexture("Paddle"), Vector2(50, 850)));
    wallL.Add(new BoxCollision(Vector2(50, 850)));

    GameObject wallR(Vector2(1300, 25));
    wallR.Add(new Sprite(TextureManager::GetTexture("Paddle"), Vector2(50, 850)));
    wallR.Add(new BoxCollision(Vector2(50, 850)));

    scene.Add(&background);
    scene.Add(&text);
    scene.Add(&paddle);
    scene.Add(&ball);

    scene.Add(&wallT);
    scene.Add(&wallB);
    scene.Add(&wallL);
    scene.Add(&wallR);

    Scene::LoadScene(scene);

    Arena arena();
    winMain->GameLoop();

    SDL_Quit();
    return 0;
}

