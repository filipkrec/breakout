#pragma once
#include "GameObject.h"
#include "SoundManager.h"

class Brick : public GameObject
{
	std::string m_id;
	bool m_destructible;
	int m_HP;
	int m_score;

	void Update() override {}

public:
	~Brick() override {};

	Brick(std::string id, float width, float height, int HP, int score, std::string Texture, bool destructible = true);
	Brick(Brick& other);
	Brick(std::string name, Brick& other);
	Brick* Clone() const;
	Brick* Clone(std::string name) const;

	void setSize(Vector2 size);
	void OnCollisionEnterGO(Component* other) override;
	inline const std::string GetId() const { return m_id; }
	inline const bool IsDestructible() const { return m_destructible; }
};
