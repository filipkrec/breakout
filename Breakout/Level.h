#pragma once
#include "SDL.h"
#include "Brick.h"
#include "Arena.h"
#include "tinyxml.h"

class Level
{
	/*
	int m_rowCount;
	int m_columnCount;
	int m_rowSpacing;
	int m_columnSpacing;
	SDL_Texture* m_board;
	std::vector<Brick*> brickTypes;
	Arena* arena;
	std::string layout;
	*/

public:
	void Load(std::string xmlFile);
};