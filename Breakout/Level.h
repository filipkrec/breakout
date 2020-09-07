#pragma once
#include "SDL.h"
#include "Brick.h"
#include "Arena.h"
#include "tinyxml.h"

class Level
{
	int m_ordinal;
	int m_rowCount;
	int m_columnCount;
	int m_rowSpacing;
	int m_columnSpacing;
	SDL_Texture* m_board;
	std::vector<Brick*> m_brickTypes;
	Arena* m_arena;
	std::string m_layout;

public:
	void Load(std::string xmlFile);
	std::string LoadStringAttribute(tinyxml2::XMLElement* element,std::string attribute);
	int LoadIntAttribute(tinyxml2::XMLElement* element, std::string attribute);

};