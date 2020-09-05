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

    //Arena
    const int levelHeight = 750;
    const int levelWidth = 1300;
    const int wallThickness = 50;
    const int padding = 25;
    const int leftoverWidth = unitsX - levelWidth - wallThickness * 2;
    const int originLeft = leftoverWidth / 2;
    const int originRight = leftoverWidth / 2 + levelWidth + wallThickness;
    const int horOriginBot = padding;
    const int vertOriginBot = padding + wallThickness;
    const int horWallWidth = levelWidth + wallThickness * 2;
    const int vertWallHeight = levelHeight;
    const int originTop = vertOriginBot + levelHeight;

    GameObject wallB(Vector2(originLeft, horOriginBot));
    wallB.Add(new Sprite(TextureManager::GetTexture("Paddle"), Vector2(horWallWidth, wallThickness)));
    wallB.Add(new BoxCollision(Vector2(horWallWidth, wallThickness)));

    GameObject wallT(Vector2(originLeft, originTop));
    wallT.Add(new Sprite(TextureManager::GetTexture("Paddle"), Vector2(horWallWidth, wallThickness)));
    wallT.Add(new BoxCollision(Vector2(horWallWidth, wallThickness)));

    GameObject wallL(Vector2(originLeft, vertOriginBot));
    wallL.Add(new Sprite(TextureManager::GetTexture("Paddle"), Vector2(wallThickness, vertWallHeight)));
    wallL.Add(new BoxCollision(Vector2(wallThickness, vertWallHeight)));

    GameObject wallR(Vector2(originRight, vertOriginBot));
    wallR.Add(new Sprite(TextureManager::GetTexture("Paddle"), Vector2(wallThickness, vertWallHeight)));
    wallR.Add(new BoxCollision(Vector2(wallThickness, vertWallHeight)));

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

