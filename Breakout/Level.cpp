#include "Level.h"

Level::~Level()
{
	ClearFromScene();

	m_brickTypes.erase(
		std::remove_if(m_brickTypes.begin(), m_brickTypes.end(),
			[&](Brick* x) {
				delete x;
				return true; }),
		m_brickTypes.end());
}

Level::Level()
	: m_wallTexture(0),m_rowSpacing(0),m_rowCount(0),m_columnSpacing(0),m_columnCount(0),
	m_board(0),m_arena(0)
{
}

Level::Level(std::string xmlFile)
	: m_wallTexture(0), m_rowSpacing(0), m_rowCount(0), m_columnSpacing(0), m_columnCount(0),
	m_board(0), m_arena(0)
{
	Load(xmlFile);
}

void Level::Load(std::string xmlFile)
{
	TextureManager::GetManager()->LoadTexture("Wall","Textures/Walls/Wall.dds");
	m_wallTexture = TextureManager::GetManager()->GetTexture("Wall");

	using namespace tinyxml2;
	XMLDocument doc;
	if (doc.LoadFile(xmlFile.c_str()) != XMLError::XML_SUCCESS)
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
	
	std::string backgroundFile = LoadStringAttribute(element, "BackgroundTexture");

	std::string backgroundFileName = backgroundFile.substr(backgroundFile.find_last_of('/') + 1, backgroundFile.find_last_of('.') - backgroundFile.find_last_of('/') - 1);

	TextureManager::GetManager()->LoadTexture(backgroundFileName,backgroundFile);
	m_board = TextureManager::GetManager()->GetTexture(backgroundFileName);

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

				SoundManager::GetManager()->AddSound(id + "hit", hitSound);

				std::string breakSound = LoadStringAttribute(element, "BreakSound");

				SoundManager::GetManager()->AddSound(id + "break", breakSound);

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
	m_arena = new Arena(m_columnCount,m_rowCount,m_rowSpacing,m_columnSpacing,m_wallTexture,m_board,60,40);
	m_arena->LoadBricks(m_layout, m_brickTypes);
	m_arena->AddToScene(*scene);
	ball->SetPosition(m_arena->GetBallStartingPoint(ball));
	ball->SetSpeed(m_ballStartSpeed);
	ball->SetAngle(ball->m_startingAngle);
	paddle->SetPosition(m_arena->GetPaddleStartingPoint(paddle));
}

int Level::GetBrickCount()
{
	return m_arena->GetBrickCount();
}

void Level::ClearFromScene()
{
	if(m_arena)
		m_arena->Destroy();
}