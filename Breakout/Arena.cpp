#pragma once
#include "Arena.h"
#include "WallBottom.h"

int Arena::m_minHeight;

Arena::~Arena()
{
    m_background->Destroy();

    for (int i = 0; i < 4; ++i)
    {
        m_walls[i]->Destroy();
    }

    m_bricks.erase(
        std::remove_if(m_bricks.begin(), m_bricks.end(),
            [&](Brick* x) {
                delete x;
                return true; 
            }),
        m_bricks.end());
}

Arena::Arena(int columnCount, int rowCount, int rowSpacing, int columnSpacing, SDL_Texture* wallTexture, SDL_Texture* backgroundTexture, int brickWidth, int brickHeight)
    :GameObject("Arena"),m_background(nullptr), m_rowSpacing(rowSpacing), m_columnSpacing(columnSpacing)
    , m_columnCount(columnCount), m_brickCount(0), m_brickWidth(brickWidth), m_brickHeight(brickHeight)
{
    const int screenX = static_cast<int>(Rect::GetResolutionRatio().x);
    const int screenY = static_cast<int>(Rect::GetResolutionRatio().y);

    m_minHeight = screenY / 3;

    const int padding = 25;
    const int wallThickness = 50;

    const int arenaHeight = 900;
    const int levelHeight = arenaHeight - (padding + wallThickness) * 2;

    if (levelHeight < m_minHeight)
    {
#ifdef _DEBUG
        std::cout << "ERROR: level too small, reduce padding or wall thickness - " << "Padding: " << padding << ", Wall Thickness:" << wallThickness << std::endl;
#endif
    }

    int levelWidth = columnSpacing + (brickWidth + columnSpacing) * columnCount;

    if (levelWidth > screenX)
    {
        levelWidth = screenX - (padding + wallThickness) * 2;
        m_brickWidth = (levelWidth - columnSpacing * 2) / (columnCount + columnSpacing);
        levelWidth = columnSpacing + columnCount * (m_brickWidth + columnSpacing);
    }

    const int leftoverWidth = screenX - levelWidth - wallThickness * 2;
    const int originLeft = leftoverWidth / 2;
    const int originRight = leftoverWidth / 2 + levelWidth + wallThickness;
    const int horOriginBot = padding + (screenY - arenaHeight) / 2;
    const int vertOriginBot = horOriginBot + wallThickness - 1;
    const int horWallWidth = levelWidth + wallThickness * 2;
    const int vertWallHeight = levelHeight;
    const int originTop = vertOriginBot + levelHeight;

    //point on which to spawn the first brick
    m_brickOrigin = Vector2(originLeft + wallThickness + columnSpacing, (originTop - (brickHeight + rowSpacing)));

    //BotHorizontal wall
    m_walls[0] = new GameObject("WallBot",Vector2(originLeft, horOriginBot));
    m_walls[0]->Add(new Sprite(wallTexture, Vector2(horWallWidth, wallThickness)));
    m_walls[0]->Add(new BoxCollision(Vector2(horWallWidth, wallThickness)));
    m_walls[0]->Add(new WallBottom());

    //TopHorizontal wall
    m_walls[1] = new GameObject("WallTop", Vector2(originLeft, originTop));
    m_walls[1]->Add(new Sprite(wallTexture, Vector2(horWallWidth, wallThickness)));
    m_walls[1]->Add(new BoxCollision(Vector2(horWallWidth, wallThickness)));
    
    //Left vertical wall
    m_walls[2] = new GameObject("WallLeft", Vector2(originLeft, vertOriginBot));
    m_walls[2]->Add(new Sprite(wallTexture, Vector2(wallThickness, vertWallHeight)));
    m_walls[2]->Add(new BoxCollision(Vector2(wallThickness, vertWallHeight)));
    
    //Right vertical wall
    m_walls[3] = new GameObject("WallRight", Vector2(originRight, vertOriginBot));
    m_walls[3]->Add(new Sprite(wallTexture, Vector2(wallThickness, vertWallHeight)));
    m_walls[3]->Add(new BoxCollision(Vector2(wallThickness, vertWallHeight)));

    if (backgroundTexture != nullptr)
    {
        m_background = new GameObject(Vector2(originLeft + wallThickness - 1, vertOriginBot));
        m_background->Add(new Sprite(backgroundTexture, Vector2(levelWidth + 1, levelHeight)));
    }

    m_paddleSpawn = Vector2(screenX / 2, horOriginBot + wallThickness + 25);
}


void Arena::AddToScene(Scene& scene)
{
    scene.Add(this);

    Component* comp = nullptr;
    if(m_background)
        comp = m_background->GetSprite();

    if (comp != nullptr)
        scene.Add(m_background);

    for (int i = 0; i < 4; ++i)
    {
        scene.Add(m_walls[i]);
    }

    for (Brick* brick : m_bricks)
    {
#ifdef _DEBUG
        scene.Add(brick->Clone(brick->GetName()));
#else 
        scene.Add(brick->Clone());
#endif 
    }
}

void Arena::LoadBricks(std::string layout,const std::vector<Brick*>& brickTypes)
{
    int currentRow = 1;
    int currentColumn = 1;

    Brick* currentBrick = nullptr; 
    bool typeMatch = false;

    for (int i = 0; i < layout.size();)
    {
        currentBrick = nullptr;
        typeMatch = false;

        char c = layout.c_str()[i];

        for (Brick* brickType : brickTypes)
        {
            if (layout[i] == brickType->GetId()[0])
            {
                if (layout.substr(i, brickType->GetId().size()) == brickType->GetId())
                {
                    typeMatch = true;
                }
            }

            if (typeMatch)
            {
#ifdef _DEBUG
                std::string name = "Brick - " +std::to_string(currentColumn) + "," + std::to_string(currentRow);
                currentBrick = brickType->Clone(name);
#else 
                currentBrick = brickType->Clone();
#endif 

                break;
            }
        }

        if (layout[i] == '_')
        {
            currentColumn++;
        }
        else if (layout[i] == '\n')
        {
            if (currentColumn != 1)
            {
                currentColumn = 1;
                currentRow++;
            }
        }

        if (currentBrick != nullptr)
        {
            if (currentBrick->IsDestructible())
                m_brickCount++;

            Vector2 pos;
            pos.x = m_brickOrigin.x + (currentColumn - 1) * (m_brickWidth + m_columnSpacing);
            pos.y = m_brickOrigin.y - (currentRow - 1) * (m_brickHeight + m_rowSpacing);

            currentBrick->SetPosition(pos);
            currentBrick->setSize(Vector2(m_brickWidth, m_brickHeight));

            m_bricks.push_back(currentBrick);
       

            currentColumn++;
            i += static_cast<int>(currentBrick->GetId().size());
        }
        else
        {
            ++i;
        }
    }
}

int Arena::GetBrickCount()
{
    return m_brickCount;
}


const Vector2 Arena::GetPaddleStartingPoint(Paddle* paddle) const
{
    return Vector2(-paddle->m_width/2, 0) + m_paddleSpawn;
}

const  Vector2 Arena::GetBallStartingPoint(Ball* ball) const
{
    return Vector2(-ball->m_radius, m_minHeight) + m_paddleSpawn;
}