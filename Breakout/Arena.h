#pragma once
#include "Scene.h"

class Arena
{
private: 
	GameObject m_walls[4];
	GameObject background;
public:
	Arena(int columnCount, int rowCount, int rowSpacing, int columnSpacing, SDL_Texture* texture, SDL_Texture* backgroundTexture = nullptr, int brickWidth = 60, int brickHeight = 25, int screenWidth = 1600, int screenHeight = 900);
	void AddToScene(Scene& scene);
};