#include "SDL.h"
#include "Window.h"
#include "Paddle.h"
#include "Ball.h"
#include "Arena.h"
#include "Brick.h"
#include "Button.h"
#include "Level.h"
#include <fstream>

void LoadGame();

int main(int arc, char* argv[])
{   

    Level lvl;
    lvl.Load("test.xml");


    Window* winMain = new Window(Vector2(1600, 900), false);
    Scene menu;
    TextureManager::LoadTexture("Button", "Textures/Buttons/Button.dds");
    TextureManager::LoadText("NewGame", "New Game!");
    Button button(TextureManager::GetTexture("Button"), TextureManager::GetTexture("NewGame"), Vector2(600, 700), Vector2(400, 100), 
        LoadGame);
    menu.Add(&button);
    Scene::LoadScene(menu);

    winMain->GameLoop();

    SDL_Quit();
    return 0;
}

void LoadGame()
{
    int unitsX = 1600;
    int unitsY = 900;

    Scene* scene = new Scene();
    TextureManager::LoadTexture("BGTexture", "Textures/Backgrounds/Background1.dds");
    TextureManager::LoadTexture("Board", "Textures/Boards/Board_01.dds");

    const int textureSize = 400;
    for (int x = 0; x < unitsX; x += textureSize)
        for (int y = 0; y < unitsY; y += textureSize)
        {
            Sprite* img = new Sprite(TextureManager::GetTexture("BGTexture"), Vector2(textureSize, textureSize));
            GameObject* temp = new GameObject(Vector2(x, y));
            temp->Add(img);
            scene->Add(temp);
        }

    TextureManager::LoadText("TestTxt", "This is a test text!");
    Sprite* txt = new Sprite(TextureManager::GetTexture("TestTxt"), Vector2(100, 100));
    GameObject* text = new GameObject(Vector2(0, 0));
    text->Add(txt);

    Paddle* paddle = new Paddle();
    Ball* ball = new Ball();
    TextureManager::LoadTexture("Wall", "Textures/Walls/Wall.dds");
    Arena* arena = new Arena(30, 20, 3, 2, TextureManager::GetTexture("Wall"), TextureManager::GetTexture("Board"));

    Brick* brick = new Brick("M", 9, 3, 1, 50, "Textures/Bricks/Brick.dds");
    brick->SetPosition(Vector2(500, 600));

    arena->AddToScene(*scene);
    scene->Add(text);
    scene->Add(paddle);
    scene->Add(ball);
    scene->Add(brick);

    Scene::LoadScene(*scene);
}