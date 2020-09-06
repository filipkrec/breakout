#include "SDL.h"
#include "Window.h"
#include "Paddle.h"
#include "Ball.h"
#include "Arena.h"
#include "Brick.h"
#include "Button.h"

void LoadGame();

int main(int arc, char* argv[])
{
    
    Window* winMain = new Window(Vector2(1600, 900), false);
    Scene menu;
    TextureManager::LoadTexture("Button", "Button.png");
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
    TextureManager::LoadTexture("BGTexture", "BackgroundTexture.jpg");

    const int textureSize = 400;
    for (int x = 0; x < unitsX; x += textureSize)
        for (int y = 0; y < unitsY; y += textureSize)
        {
            Sprite* img = new Sprite(TextureManager::GetTexture("BGTexture"), Vector2(textureSize, textureSize));
            GameObject* temp = new GameObject(Vector2(x, y));
            temp->Add(img);
            scene->Add(temp);
        }


    TextureManager::LoadTexture("Doggie", "image.bmp");
    Sprite* bg = new Sprite(TextureManager::GetTexture("Doggie"), Vector2(1050, 800));
    GameObject* background = new GameObject(Vector2(250, 25));
    background->Add(bg);

    TextureManager::LoadText("TestTxt", "This is a test text!");
    Sprite* txt = new Sprite(TextureManager::GetTexture("TestTxt"), Vector2(100, 100));
    GameObject* text = new GameObject(Vector2(0, 0));
    text->Add(txt);

    Paddle* paddle = new Paddle();
    Ball* ball = new Ball();
    Arena* arena = new Arena(30, 20, 3, 2, TextureManager::GetTexture("Paddle"), TextureManager::GetTexture("Doggie"));

    scene->Add(background);
    arena->AddToScene(*scene);
    scene->Add(text);
    scene->Add(paddle);
    scene->Add(ball);

    Scene::LoadScene(*scene);
}