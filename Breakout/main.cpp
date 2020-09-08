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
void FillBackground(Scene* scene);

int main(int arc, char* argv[])
{   
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
    Scene* scene = new Scene();
    TextureManager::LoadTexture("BGTexture", "Textures/Backgrounds/Background1.dds");
    FillBackground(scene);

    Paddle* paddle = new Paddle();
    Ball* ball = new Ball();

    Level* level = new Level();
    level->Load("../Assets/Levels/Level.xml");
    level->InitialiseLevel(paddle,ball,scene);
    scene->Add(paddle);
    scene->Add(ball);
    Scene::LoadScene(*scene);
}

void FillBackground(Scene* scene)
{
    const int unitsX = 1600;
    const int unitsY = 900;

    const int textureSize = 400;
    for (int x = 0; x < unitsX; x += textureSize)
        for (int y = 0; y < unitsY; y += textureSize)
        {
            Sprite* img = new Sprite(TextureManager::GetTexture("BGTexture"), Vector2(textureSize, textureSize));
            GameObject* temp = new GameObject(Vector2(x, y));
            temp->Add(img);
            scene->Add(temp);
        }
}