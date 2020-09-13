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

    Button* Options = new Button(TextureManager::GetManager()->GetTexture("Button"), "Options", screenCenter - buttonSize / 2 - buttonPadding, buttonSize,
        LoadOptions);

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
    TextureManager::GetManager()->LoadTexture("ScoreBG", "Textures/UI/ScoreBG.dds");
    const float screenX = Rect::GetResolutionRatio().x;
    const float screenY = Rect::GetResolutionRatio().y;
    const Vector2 screenCenter = Rect::GetScreenCenter();
    const Vector2 buttonSize(150, 50);
    const Vector2 padding(0, screenY / 5);
    const Vector2 highScoreSize(300, 80);

    Scene* highscoreScreen = new Scene();
    Button* back = new Button(TextureManager::GetManager()->GetTexture("Button"), "Back", 
        screenCenter - buttonSize / 2 - padding * 2, buttonSize,
        ReloadMenu);

    std::vector<std::string> highscores = SaveManager::get_scores();
    const SDL_Color black = { 0,0,0 };

    GameObject* highScoresGo = new GameObject();

    for (int i = 0; i < highscores.size();++i)
    {
        Button* highScoreTextGO = new Button(
            TextureManager::GetManager()->GetTexture("ScoreBG"),
            std::to_string(i + 1) + ". " + highscores[i],
            Vector2(screenCenter.x - highScoreSize.x / 2, screenY - padding.y - buttonSize.y * (i * 1.5f)),
            highScoreSize,
            nullptr);
        highScoresGo->Add(highScoreTextGO);
    }

    GameObject* menuBackground = new GameObject();
    menuBackground->Add(new Sprite(TextureManager::GetManager()->GetTexture("MenuBackground"), Vector2(screenX, screenY)));
    highscoreScreen->Add(menuBackground);
    highscoreScreen->Add(highScoresGo);
    highscoreScreen->Add(back);
    Scene::LoadScene(highscoreScreen,false);
}

void SceneLoader::LoadOptions()
{
    TextureManager::GetManager()->LoadTexture("ScoreBG", "Textures/UI/ScoreBG.dds");
    const float screenX = Rect::GetResolutionRatio().x;
    const float screenY = Rect::GetResolutionRatio().y;
    const Vector2 screenCenter = Rect::GetScreenCenter();
    const Vector2 backButtonSize(150, 50);
    const Vector2 buttonSize(200, 75);
    const Vector2 titleSize(400, 100);
    const Vector2 buttonPaddingHorizontal(50, 0);
    const Vector2 buttonPaddingVertical(0, 50);
    const Vector2 paddingHorizontal(screenX / 4, 0);
    const Vector2 paddingVertical(0, screenY / 5);

    Scene* options = new Scene();
    Button* back = new Button(TextureManager::GetManager()->GetTexture("Button"), "Back", 
        screenCenter - backButtonSize / 2 - paddingVertical * 2,
        backButtonSize,
        ReloadMenu);

    //VOLUME
    Button* volumeText = new Button(
        TextureManager::GetManager()->GetTexture("ScoreBG"),
        "   Sound   ",
        Vector2(screenCenter.x - titleSize.x / 2, screenY - paddingVertical.y),
        titleSize,
        nullptr);

    Button* volumeOff = new Button(
        TextureManager::GetManager()->GetTexture("ScoreBG"),
        "Off",
        Vector2(screenCenter.x - buttonSize.x - buttonSize.x / 2 - buttonPaddingHorizontal.x,
            volumeText->GetPosition().y - buttonPaddingVertical.y - buttonSize.y),
        buttonSize,
        [] {SoundManager::GetManager()->VolumeOff(); });

    Button* volumeOn = new Button(
        TextureManager::GetManager()->GetTexture("ScoreBG"),
        "On",
        Vector2(screenCenter.x + buttonSize.x / 2 + buttonPaddingHorizontal.x,
            volumeText->GetPosition().y - buttonPaddingVertical.y - buttonSize.y),
        buttonSize,
        [] {SoundManager::GetManager()->VolumeOn(); });

    //ASPECT RATIO
    Button* aspectText = new Button(
        TextureManager::GetManager()->GetTexture("ScoreBG"),
        "Aspect ratio",
        Vector2(screenCenter.x - titleSize.x / 2, 
            volumeOn->GetPosition().y - buttonPaddingVertical.y - titleSize.y),
        titleSize,
        nullptr);

    Button* aspect169 = new Button(
        TextureManager::GetManager()->GetTexture("ScoreBG"),
        "16:9",
        Vector2(screenCenter.x - buttonSize.x/2 - buttonPaddingHorizontal.x - buttonSize.x ,
            aspectText->GetPosition().y - buttonPaddingVertical.y - buttonSize.y),
        buttonSize,
        [] {Rect::SetResolutionRatio(Vector2(16, 9), false); 
    LoadOptions(); });

    Button* aspect1610 = new Button(
        TextureManager::GetManager()->GetTexture("ScoreBG"),
        "16:10",
        Vector2(screenCenter.x - buttonSize.x / 2,
            aspectText->GetPosition().y - buttonPaddingVertical.y - buttonSize.y),
        buttonSize,
        [] {Rect::SetResolutionRatio(Vector2(16, 10), false);
    LoadOptions(); });

    Button* aspect43 = new Button(
        TextureManager::GetManager()->GetTexture("ScoreBG"),
        "4:3",
        Vector2(screenCenter.x + buttonSize.x / 2 + buttonPaddingHorizontal.x,
            aspectText->GetPosition().y - buttonPaddingVertical.y - buttonSize.y),
        buttonSize,
        [] {Rect::SetResolutionRatio(Vector2(4, 3), false);
    LoadOptions(); });

    GameObject* menuBackground = new GameObject();
    menuBackground->Add(new Sprite(TextureManager::GetManager()->GetTexture("MenuBackground"), Vector2(screenX, screenY)));
    options->Add(menuBackground);
    options->Add(back);
    options->Add(volumeText);
    options->Add(volumeOn);
    options->Add(volumeOff);
    options->Add(aspectText);
    options->Add(aspect1610);
    options->Add(aspect169);
    options->Add(aspect43);
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