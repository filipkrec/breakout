#include "Level.h"

void Level::Load(std::string xmlFile)
{
	const int brickWidth = 90;
	const int brickHeight = 30;

	using namespace tinyxml2;
	XMLDocument doc;
	if (doc.LoadFile(xmlFile.c_str()) != XML_SUCCESS)
	{
		std::cout << "ERROR: load failed - " << xmlFile << std::endl;
		return;
	}

	//LEVEL
	XMLNode* root = doc.FirstChildElement("Level");
	XMLElement* element = root->ToElement();
	m_rowCount = LoadIntAttribute(element, "RowCount");
	m_columnCount = LoadIntAttribute(element, "ColumnCount");
	m_rowSpacing = LoadIntAttribute(element, "RowSpacing");
	m_columnSpacing = LoadIntAttribute(element, "ColumnSpacing"); 
	
	TextureManager::LoadTexture(std::to_string(m_ordinal), 
		LoadStringAttribute(element, "BackgroundTexture"));
	m_board = TextureManager::GetTexture(std::to_string(m_ordinal));

	//BrickTypes
	element = root->FirstChildElement("BrickTypes");

	if(element)
		if (element->FirstChildElement())
		{
			element = element->FirstChildElement()->ToElement();
			for (element; element; element = element->NextSiblingElement())
			{
				std::string id = LoadStringAttribute(element, "Id");
				std::string texture = LoadStringAttribute(element, "Texture");
				int hp = LoadIntAttribute(element, "HitPoints");
				bool destructible = true;

				if (LoadStringAttribute(element, "HitPoints") == "Infinite")
					destructible = false;

				std::string hitSound = LoadStringAttribute(element, "HitSound");
				std::string breakSound = LoadStringAttribute(element, "BreakSound");
				int breakScore = LoadIntAttribute(element, "BreakScore");

				m_brickTypes.push_back(new Brick(id, brickWidth, brickHeight, hp, breakScore, texture, destructible));
			}
		}

	//brick layout
	element = root->FirstChildElement("Bricks");

	if(element)
	m_layout = element->GetText();
}


std::string Level::LoadStringAttribute(tinyxml2::XMLElement* element, std::string attribute)
{
	using namespace tinyxml2;

	std::string currentElement;

	if (element->Attribute(attribute.c_str()))
	{
		currentElement = element->Attribute(attribute.c_str());
		return currentElement;
	}
	else
	{
		std::cout << "ERROR: no" << attribute << " attribute!" << std::endl;
		return "Error";
	}
}


int Level::LoadIntAttribute(tinyxml2::XMLElement* element, std::string attribute)
{
	using namespace tinyxml2;

	std::string currentElement;

	if (element->Attribute(attribute.c_str()))
	{
		currentElement = element->Attribute(attribute.c_str());
		return std::atoi(currentElement.c_str());
	}
	else
	{
		std::cout << "ERROR: no" << attribute << " attribute!" << std::endl;
		return 0;
	}
}
