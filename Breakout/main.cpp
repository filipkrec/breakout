#include "SDL.h"
#include "Window.h"
#include "Button.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include <fstream>

void LoadGame();
void LoadUI();
void FillBackground(Scene* scene);

const int unitsX = 1600;
const int unitsY = 900;

int main(int arc, char* argv[])
{

    Window* winMain = new Window(Vector2(1600, 900), false);
    Scene menu;
    TextureManager::GetManager()->LoadTexture("MenuBackground", "Textures/Backgrounds/MenuBackground.dds");
    TextureManager::GetManager()->LoadTexture("Button", "Textures/Buttons/Button.dds");
    menu.LoadMusic("MenuMusic", "Sounds/Music/MenuMusic.wav");
    Button button(TextureManager::GetManager()->GetTexture("Button"),"New Game" , Vector2(600, 700), Vector2(400, 100),
        LoadGame);
    GameObject menuBackground;
    menuBackground.Add(new Sprite(TextureManager::GetManager()->GetTexture("MenuBackground"), Vector2(unitsX, unitsY)));
    menu.Add(&menuBackground);
    menu.Add(&button);
    Scene::LoadScene(menu);

    winMain->GameLoop();

    SDL_Quit();
    return 0;
}

void LoadGame()
{
    Scene* scene = new Scene();

    TextureManager::GetManager()->LoadTexture("BGTexture", "Textures/Backgrounds/Background1.dds");
    FillBackground(scene);

    scene->LoadMusic("PlayMusic", "Sounds/Music/PlayMusic.wav");

    Ball* ball = new Ball();
    Paddle* paddle = new Paddle();

    LevelManager::GetManager()->LoadLevel("../Assets/Levels/Level.xml");
    LevelManager::GetManager()->LoadLevel("../Assets/Levels/Level2.xml");
    LevelManager::GetManager()->SetBall(ball);
    LevelManager::GetManager()->SetPaddle(paddle);

    Scene::LoadScene(*scene);
    LevelManager::GetManager()->AddFirst();
    LoadUI();
    Scene::GetActiveScene().Add(paddle);
    Scene::GetActiveScene().Add(ball);
}


void FillBackground(Scene* scene)
{
    const int textureSize = 400;
    for (int x = 0; x < unitsX; x += textureSize)
        for (int y = 0; y < unitsY; y += textureSize)
        {
            Sprite* img = new Sprite(TextureManager::GetManager()->GetTexture("BGTexture"), Vector2(textureSize, textureSize));
            GameObject* temp = new GameObject(Vector2(x, y));
            temp->Add(img);
            scene->Add(temp);
        }
}


void LoadUI()
{
    GameObject* UI = new GameObject();
    UI->SetName("UI");
    TextureManager::GetManager()->LoadTexture("ScoreBoard", "Textures/UI/ScoreBoard.dds");
    TextureManager::GetManager()->LoadTexture("GameOver", "Textures/UI/GameOver.dds");

    Button* score = new Button(TextureManager::GetManager()->GetTexture("ScoreBoard"), std::to_string(0),
        Vector2(unitsX - 150, unitsY - 75), Vector2(100, 50), [] {});
    score->SetName("Score");
    UI->Add(score);

    Button* lives = new Button(TextureManager::GetManager()->GetTexture("ScoreBoard"), std::to_string(0),
        Vector2(50, unitsY - 75), Vector2(100, 50), [] {});
    lives->SetName("Lives");
    UI->Add(lives);

    Button* gameOver = new Button(TextureManager::GetManager()->GetTexture("GameOver"), "", Vector2(unitsX / 2 - 250, unitsY / 2 - 250), Vector2(500, 500), [] {});//TODO Switch scene
    gameOver->SetName("GameOver");
    UI->Add(gameOver);
    gameOver->Deactivate();

    GameObject* paused = new GameObject();
    paused->SetName("Paused");
    UI->Add(paused);
    paused->Deactivate();

    Button* pauseContinue = new Button(nullptr, "Continue", Vector2(unitsX / 2 - 160, unitsY - 300), Vector2(320, 100),
        []()
        { 
            Input::TogglePause();       
            GameObject* UI = Scene::GetActiveScene().GetByName("UI");
            GameObject* pausedMenu = UI->GetChildGameObject("Paused");
            if (pausedMenu)
                    pausedMenu->Deactivate();
        }
       );
    SDL_Color yellow = { 255, 255, 0 };
    pauseContinue->SetTextColor(yellow);
    paused->Add(pauseContinue);

    Button* quitGame = new Button(nullptr, "Quit", Vector2(unitsX / 2 - 80, unitsY - 450), Vector2(160, 100), [] {});//TODO Switch scene
    quitGame->SetTextColor(yellow);
    paused->Add(quitGame);
    
    Button* exitGame = new Button(nullptr, "Exit", Vector2(unitsX / 2 - 80, unitsY - 600), Vector2(160, 100), Input::Exit);
    exitGame->SetTextColor(yellow);
    paused->Add(exitGame);

    Scene::GetActiveScene().Add(UI);
}