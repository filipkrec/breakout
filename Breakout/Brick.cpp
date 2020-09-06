#include "Brick.h"

Brick::Brick(std::string id, float height, float width, int HP, int score, std::string Texture, bool destructible)
	:m_HP(HP),m_score(score),m_destructible(destructible)
{
	TextureManager::LoadTexture(id, Texture);
	Add(new Sprite(TextureManager::GetTexture(id), Vector2(height * 10, width * 10)));
	Add(new BoxCollision(Vector2(height * 10, width * 10)));
}

Brick::Brick(Brick& other)
{
	Sprite* sprite = static_cast<Sprite*>(other.GetComponent<Sprite>());
	BoxCollision* bc = static_cast<BoxCollision*>(other.GetComponent<BoxCollision>());
	Add(new Sprite(*sprite));
	Add(new BoxCollision(*bc));
	m_HP = other.m_HP;
	m_score = other.m_score;
	m_destructible = other.m_destructible;
}

Brick* Brick::Clone(Brick& other)
{
	return new Brick(other);
}