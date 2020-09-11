#pragma once
#include "SDL.h"
#include "Brick.h"
#include "Arena.h"
#include "Paddle.h"
#include "Ball.h"
#include "tinyxml.h"

class Level
{
	const int m_ballStartSpeed = 6;

	int m_ordinal;
	int m_rowCount;
	int m_columnCount;
	int m_rowSpacing;
	int m_columnSpacing;

	SDL_Texture* m_board;
	SDL_Texture* m_wallTexture;

	std::vector<Brick*> m_brickTypes;
	Arena* m_arena;
	std::string m_layout;

public:
	~Level();
	Level();
	Level(std::string xmlFile);
	void Load(std::string xmlFile);
	std::string LoadStringAttribute(tinyxml2::XMLElement* element,std::string attribute);
	int LoadIntAttribute(tinyxml2::XMLElement* element, std::string attribute);

	void Initialise(Paddle* paddle,Ball* ball, Scene* scene);
	int GetBrickCount();
	void ClearFromScene();
};