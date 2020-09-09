#include "SDL.h"
#include "Window.h"
#include "Button.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include <fstream>

void LoadGame();
void FillBackground(Scene* scene);

int main(int arc, char* argv[])
{   
    Window* winMain = new Window(Vector2(1600, 900), false);
    Scene menu;
    TextureManager::LoadTexture("Button", "Textures/Buttons/Button.dds");
    TextureManager::LoadText("NewGame", "New Game!");
    menu.LoadMusic("MenuMusic", "Sounds/Music/MenuMusic.wav");
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

    scene->LoadMusic("PlayMusic", "Sounds/Music/PlayMusic.wav");

    Ball* ball = new Ball();
    Paddle* paddle = new Paddle();

    LevelManager::LoadLevel("../Assets/Levels/Level.xml");
    LevelManager::LoadLevel("../Assets/Levels/Level2.xml");
    LevelManager::SetBall(ball);
    LevelManager::SetPaddle(paddle);

    Scene::LoadScene(*scene);
    LevelManager::AddFirst();
    Scene::GetActiveScene().Add(paddle);
    Scene::GetActiveScene().Add(ball);
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