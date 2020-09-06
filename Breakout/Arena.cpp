#pragma once
#include "Arena.h"

Arena::Arena(int columnCount, int rowCount, int rowSpacing, int columnSpacing, SDL_Texture* texture, SDL_Texture* backgroundTexture, int brickWidth, int brickHeight, int screenWidth, int screenHeight)
{

    const int padding = 25;
    const int wallThickness = 50;

    const int levelHeight = screenHeight - (padding + wallThickness) * 2;
    int levelWidth = (columnCount + columnSpacing) * brickWidth - (padding + wallThickness) * 2;

    if (levelWidth > screenWidth)
    {
        brickWidth = (screenWidth - (padding + wallThickness) * 2) / (columnCount + columnSpacing);
        levelWidth = screenWidth - (padding + wallThickness) * 2;
    }

    const int leftoverWidth = screenWidth - levelWidth - wallThickness * 2;
    const int originLeft = leftoverWidth / 2;
    const int originRight = leftoverWidth / 2 + levelWidth + wallThickness;
    const int horOriginBot = padding;
    const int vertOriginBot = padding + wallThickness;
    const int horWallWidth = levelWidth + wallThickness * 2;
    const int vertWallHeight = levelHeight;
    const int originTop = vertOriginBot + levelHeight;

    //BotHorizontal wall
    m_walls[0] = GameObject(Vector2(originLeft, horOriginBot));
    m_walls[0].Add(new Sprite(texture, Vector2(horWallWidth, wallThickness)));
    m_walls[0].Add(new BoxCollision(Vector2(horWallWidth, wallThickness)));

    //TopHorizontal wall
    m_walls[1] = GameObject(Vector2(originLeft, originTop));
    m_walls[1].Add(new Sprite(texture, Vector2(horWallWidth, wallThickness)));
    m_walls[1].Add(new BoxCollision(Vector2(horWallWidth, wallThickness)));
    
    //Left vertical wall
    m_walls[2] = GameObject(Vector2(originLeft, vertOriginBot));
    m_walls[2].Add(new Sprite(texture, Vector2(wallThickness, vertWallHeight)));
    m_walls[2].Add(new BoxCollision(Vector2(wallThickness, vertWallHeight)));
    
    //Right vertical wall
    m_walls[3] = GameObject(Vector2(originRight, vertOriginBot));
    m_walls[3].Add(new Sprite(texture, Vector2(wallThickness, vertWallHeight)));
    m_walls[3].Add(new BoxCollision(Vector2(wallThickness, vertWallHeight)));

    if (backgroundTexture != nullptr)
    {
        background = GameObject(Vector2(originLeft + wallThickness - 1, vertOriginBot));
        background.Add(new Sprite(backgroundTexture, Vector2(levelWidth + 1, levelHeight)));
    }
}


void Arena::AddToScene(Scene& scene)
{
    Component* comp = background.GetSprite();
    if (comp != nullptr)
        scene.Add(&background);

    for (int i = 0; i < 4; ++i)
    {
        scene.Add(&m_walls[i]);
    }
}

/*
//Arena
const int levelHeight = 750;
const int levelWidth = 1000;
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

*/