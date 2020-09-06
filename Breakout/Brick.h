#pragma once
#include "GameObject.h"

class Brick : public GameObject
{
	std::string m_id;
	bool m_destructible;
	int m_HP;
	int m_score;

	void Update() override {}

public:
	Brick(std::string id, float height, float width, int HP, int score, std::string Texture, bool destructible = true);
	Brick(Brick& other);
	Brick* Clone(Brick& other);
};
