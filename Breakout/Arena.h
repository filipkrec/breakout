#pragma once
#include "Scene.h"
#include "Brick.h"

class Arena
{
private: 
	GameObject* m_walls[4];
	GameObject* m_background;
	std::vector<Brick*> m_bricks;

	int m_centerX;
	Vector2 m_brickOrigin;
	int m_columnCount;

	int m_rowSpacing;
	int m_columnSpacing;
	int m_brickWidth;
	int m_brickHeight;

	int m_brickCount;


public:
	~Arena();
	Arena(int columnCount, int rowCount, int rowSpacing, int columnSpacing, SDL_Texture* wallTexture, SDL_Texture* backgroundTexture = nullptr, int brickWidth = 40, int brickHeight = 25, int screenWidth = 1600, int screenHeight = 900);
	void AddToScene(Scene& scene);
	void LoadBricks(std::string layout, const std::vector<Brick*>& brickTypes);

	inline const int GetCenter() const { return m_centerX; }
};