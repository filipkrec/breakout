#include "Level.h"

void Level::Load(std::string xmlFile)
{
	using namespace tinyxml2;
	XMLDocument doc;
	if (doc.LoadFile(xmlFile.c_str()) != XML_SUCCESS)
	{
		std::cout << "ERROR: load failed - " << xmlFile << std::endl;
		return;
	}

	XMLNode* root = doc.FirstChildElement("Hello");

	if (root == nullptr)
	{
		std::cout << "ERROR: root failed - " << xmlFile << std::endl;
		return;
	}

	XMLElement* element = root->ToElement();
	if (element == nullptr)
	{
		std::cout << "ERROR: element failed - " << "Hello" << std::endl;
		return;
	}

	std::cout << "SUCCESS!! : " << element->Value() << std::endl;
}