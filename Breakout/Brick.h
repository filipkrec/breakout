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
	Brick(std::string id, float width, float height, int HP, int score, std::string Texture, bool destructible = true);
	Brick(Brick& other);
	Brick* Clone() const;

	void setSize(Vector2 size);
	void OnCollision(Component* other) override;
	inline const std::string GetId() const { return m_id; }
	inline const bool IsDestructible() const { return m_destructible; }
};
