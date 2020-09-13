#include "SceneLoader.h"
#include "Button.h"
#include "LevelManager.h"
#include "SaveManager.h"


void SceneLoader::LoadMenu()
{
    const float screenX = Rect::GetResolutionRatio().x;
    const float screenY = Rect::GetResolutionRatio().y;
    const Vector2 screenCenter = Rect::GetScreenCenter();
    const Vector2 buttonSize(400, 100);
    const Vector2 buttonPadding(0, screenY / 5);

    Scene* menu = new Scene();
    TextureManager::GetManager()->LoadTexture("MenuBackground", "Textures/Backgrounds/MenuBackground.dds");
    TextureManager::GetManager()->LoadTexture("Button", "Textures/Buttons/Button.dds");
    menu->LoadMusic("MenuMusic", "Sounds/Music/MenuMusic.wav");

    Button* newGame = new Button(TextureManager::GetManager()->GetTexture("Button"), "New Game", screenCenter - buttonSize / 2 + buttonPadding, buttonSize,
        LoadGame);

    Button* highScores = new Button(TextureManager::GetManager()->GetTexture("Button"), "Highscores", screenCenter - buttonSize / 2, buttonSize,
        LoadHighScores);

    Button* Options = new Button(TextureManager::GetManager()->GetTexture("Button"), "Options", screenCenter - buttonSize / 2 - buttonPadding * 3, buttonSize,
        LoadGame);

    GameObject* menuBackground = new GameObject();
    menuBackground->Add(new Sprite(TextureManager::GetManager()->GetTexture("MenuBackground"), Vector2(screenX, screenY)));
    menu->Add(menuBackground);
    menu->Add(newGame);
    menu->Add(highScores);
    menu->Add(Options);
    Scene::LoadScene(menu);
}

void SceneLoader::ReloadMenu()
{
    const float screenX = Rect::GetResolutionRatio().x;
    const float screenY = Rect::GetResolutionRatio().y;
    const Vector2 screenCenter = Rect::GetScreenCenter();
    const Vector2 buttonSize(400, 100);
    const Vector2 buttonPadding(0, screenY / 5);

    Scene* menu = new Scene();
    Button* newGame = new Button(TextureManager::GetManager()->GetTexture("Button"), "New Game", screenCenter - buttonSize / 2 + buttonPadding, buttonSize,
        LoadGame);

    Button* highScores = new Button(TextureManager::GetManager()->GetTexture("Button"), "Highscores", screenCenter - buttonSize / 2, buttonSize,
        LoadHighScores);

    Button* Options = new Button(TextureManager::GetManager()->GetTexture("Button"), "Options", screenCenter - buttonSize / 2 - buttonPadding, buttonSize,
        LoadOptions);

    GameObject* menuBackground = new GameObject();
    menuBackground->Add(new Sprite(TextureManager::GetManager()->GetTexture("MenuBackground"), Vector2(screenX, screenY)));
    menu->Add(menuBackground);
    menu->Add(newGame);
    menu->Add(highScores);
    menu->Add(Options);
    Scene::LoadScene(menu, false);
}

void SceneLoader::LoadHighScores()
{
    const float screenX = Rect::GetResolutionRatio().x;
    const float screenY = Rect::GetResolutionRatio().y;
    const Vector2 screenCenter = Rect::GetScreenCenter();
    const Vector2 buttonSize(150, 50);
    const Vector2 buttonPadding(0, screenY / 5);
    const Vector2 scorePadding(0, screenY / 15 );
    const Vector2 highScoreSize(300, 80);

    Scene* highscoreScreen = new Scene();
    Button* back = new Button(TextureManager::GetManager()->GetTexture("Button"), "Back", screenCenter - buttonSize / 2 - buttonPadding * 2, buttonSize,
        ReloadMenu);

    std::vector<std::string> highscores = SaveManager::get_scores();
    const SDL_Color black = { 0,0,0 };

    GameObject* highScoresGo = new GameObject();

    for (int i = 0; i < highscores.size();++i)
    {
        GameObject* highScoreTextGo = new GameObject();
        Text* highScoreText = new Text(std::to_string(i + 1) + highscores[i], highScoreSize, black);
        highScoreTextGo->Add(highScoreText);
        highScoreTextGo->SetPosition(Vector2(screenCenter.x - highScoreSize.x / 2, screenY - scorePadding.y * (i + 3)));
        highScoresGo->Add(highScoreTextGo);
    }


    GameObject* menuBackground = new GameObject();
    menuBackground->Add(new Sprite(TextureManager::GetManager()->GetTexture("ScoreBoardBackground"), Vector2(screenX, screenY)));
    highscoreScreen->Add(menuBackground);
    highscoreScreen->Add(highScoresGo);
    highscoreScreen->Add(back);
    Scene::LoadScene(highscoreScreen,false);
}

void SceneLoader::LoadOptions()
{
    const float screenX = Rect::GetResolutionRatio().x;
    const float screenY = Rect::GetResolutionRatio().y;
    const Vector2 screenCenter = Rect::GetScreenCenter();
    const Vector2 buttonSize(400, 100);
    const Vector2 buttonPadding(0, screenY / 5);

    Scene* options = new Scene();
    Button* back = new Button(TextureManager::GetManager()->GetTexture("Button"), "Back", screenCenter - buttonSize / 2 - buttonPadding * 2, buttonSize,
        ReloadMenu);

    GameObject* menuBackground = new GameObject();
    menuBackground->Add(new Sprite(TextureManager::GetManager()->GetTexture("MenuBackground"), Vector2(screenX, screenY)));
    options->Add(menuBackground);
    options->Add(back);
    Scene::LoadScene(options , false);
}

void SceneLoader::LoadGame()
{
    Scene* scene = new Scene();

    TextureManager::GetManager()->LoadTexture("BGTexture", "Textures/Backgrounds/Background1.dds");
    FillBackground(scene);

    scene->LoadMusic("PlayMusic", "Sounds/Music/PlayMusic.wav");

    Ball* ball = new Ball();
    Paddle* paddle = new Paddle();

    LevelManager::GetManager()->Clear();
    LevelManager::GetManager()->LoadLevel("../Assets/Levels/Level.xml");
    LevelManager::GetManager()->LoadLevel("../Assets/Levels/Level2.xml");
    LevelManager::GetManager()->LoadLevel("../Assets/Levels/Level3.xml");
    LevelManager::GetManager()->SetBall(ball);
    LevelManager::GetManager()->SetPaddle(paddle);

    Scene::LoadScene(scene);
    LoadUI();
    LevelManager::GetManager()->AddFirst();
    Scene::GetActiveScene().Add(paddle);
    Scene::GetActiveScene().Add(ball);
    Scene::GetActiveScene().PlaceFront(Scene::GetActiveScene().GetByName("UI"));
}


void SceneLoader::FillBackground(Scene* scene)
{
    const float screenX = Rect::GetResolutionRatio().x;
    const float screenY = Rect::GetResolutionRatio().y;

    const int textureSize = 400;
    for (int x = 0; x < screenX; x += textureSize)
        for (int y = 0; y < screenY; y += textureSize)
        {
            Sprite* img = new Sprite(TextureManager::GetManager()->GetTexture("BGTexture"), Vector2(textureSize, textureSize));
            GameObject* temp = new GameObject(Vector2(x, y));
            temp->Add(img);
            scene->Add(temp);
        }
}


void SceneLoader::LoadUI()
{
    const float screenX = Rect::GetResolutionRatio().x;
    const float screenY = Rect::GetResolutionRatio().y;

    GameObject* UI = new GameObject();
    UI->SetName("UI");
    TextureManager::GetManager()->LoadTexture("ScoreBoard", "Textures/UI/ScoreBoard.dds");
    TextureManager::GetManager()->LoadTexture("GameOver", "Textures/UI/GameOver.dds");
    TextureManager::GetManager()->LoadTexture("Victory", "Textures/UI/Victory.dds");

    Button* score = new Button(TextureManager::GetManager()->GetTexture("ScoreBoard"), std::to_string(0),
        Vector2(screenX - 150, screenY - 75), Vector2(100, 50), [] {});
    score->SetName("Score");
    UI->Add(score);
    Text* txt = dynamic_cast<Text*>(score->GetText());
    if (txt)
        LevelManager::GetManager()->SetScoreText(txt);

    Button* currentLevel = new Button(TextureManager::GetManager()->GetTexture("ScoreBoard"), std::to_string(1),
        Vector2(screenX - 150, screenY - 150), Vector2(100, 50), [] {});
    currentLevel->SetName("CurrentLevel");
    UI->Add(currentLevel);

    txt = dynamic_cast<Text*>(currentLevel->GetText());
    if (txt)
        LevelManager::GetManager()->SetCurrentLevelText(txt);

    Button* lives = new Button(TextureManager::GetManager()->GetTexture("ScoreBoard"), std::to_string(0),
        Vector2(50, screenY - 75), Vector2(100, 50), [] {});
    lives->SetName("Lives");
    UI->Add(lives);

    txt = dynamic_cast<Text*>(lives->GetText());
    if(txt)
        LevelManager::GetManager()->SetLivesText(txt);

    Button* gameOver = new Button(TextureManager::GetManager()->GetTexture("GameOver"), "", Vector2(screenX / 2 - 250, screenY / 2 - 250), Vector2(500, 500), LoadMenu);
    gameOver->SetName("GameOver");
    UI->Add(gameOver);
    gameOver->Deactivate();

    Button* victory = new Button(TextureManager::GetManager()->GetTexture("Victory"), "", Vector2(screenX / 2 - 250, screenY / 2 - 250), Vector2(500, 500), LoadMenu);
    victory->SetName("Victory");
    UI->Add(victory);
    victory->Deactivate();

    GameObject* paused = new GameObject();
    paused->SetName("Paused");
    UI->Add(paused);
    paused->Deactivate();

    Button* pauseContinue = new Button(nullptr, "Continue", Vector2(screenX / 2 - 160, screenY - 300), Vector2(320, 100),
        []()
        {
            Input::TogglePause();
            GameObject* UI = Scene::GetActiveScene().GetByName("UI");
            GameObject* pausedMenu = UI->GetChildGameObject("Paused");
            if (pausedMenu)
                pausedMenu->Deactivate();
        }
    );
    const SDL_Color yellow = { 255, 255, 0 };
    pauseContinue->SetTextColor(yellow);
    paused->Add(pauseContinue);

    Button* quitGame = new Button(nullptr, "Quit", Vector2(screenX / 2 - 80, screenY - 450), Vector2(160, 100), 
        []
        {
            if (Input::Paused())
                Input::TogglePause();
            LoadMenu();
        }
    );
    quitGame->SetTextColor(yellow);
    paused->Add(quitGame);

    Button* exitGame = new Button(nullptr, "Exit", Vector2(screenX / 2 - 80, screenY - 600), Vector2(160, 100), Input::Exit);
    exitGame->SetTextColor(yellow);
    paused->Add(exitGame);

    Scene::GetActiveScene().Add(UI);
}