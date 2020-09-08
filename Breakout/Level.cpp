#include "Level.h"

Level::~Level()
{
	delete m_arena;

	m_brickTypes.erase(
		std::remove_if(m_brickTypes.begin(), m_brickTypes.end(),
			[&](Brick* x) {return true; }),
		m_brickTypes.end());
}

Level::Level()
{

}

Level::Level(std::string xmlFile)
{
	Load(xmlFile);
}

void Level::Load(std::string xmlFile)
{
	TextureManager::LoadTexture("Wall","Textures/Walls/Wall.dds");
	m_wallTexture = TextureManager::GetTexture("Wall");

	using namespace tinyxml2;
	XMLDocument doc;
	if (doc.LoadFile(xmlFile.c_str()) != XML_SUCCESS)
	{
#ifdef _DEBUG
		std::cout << "ERROR: load failed - " << xmlFile << std::endl;
#endif
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

				m_brickTypes.push_back(new Brick(id, 0, 0, hp, breakScore, texture, destructible));
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
#ifdef _DEBUG
		std::cout << "ERROR: no" << attribute << " attribute!" << std::endl;
#endif
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
#ifdef _DEBUG
		std::cout << "ERROR: no" << attribute << " attribute!" << std::endl;
#endif
		return 0;
	}
}


void Level::Initialise(Paddle* paddle,Ball* ball, Scene* scene)
{
	const int ballStartSpeed = 4;
	const int downAngle = 90;

	m_arena = new Arena(m_columnCount,m_rowCount,m_rowSpacing,m_columnSpacing,m_wallTexture,m_board,60,40);
	m_arena->LoadBricks(m_layout, m_brickTypes);
	m_arena->AddToScene(*scene);
	ball->SetPosition(Vector2(m_arena->GetCenter(), paddle->GetPosition().y + 300));
	ball->SetSpeed(ballStartSpeed);
	ball->SetAngle(downAngle);
	paddle->SetPosition(Vector2(m_arena->GetCenter(), paddle->GetPosition().y));
}

void Level::ClearFromScene()
{
	delete m_arena;
}