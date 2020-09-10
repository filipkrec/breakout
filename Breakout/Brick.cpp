#include "Brick.h"
#include "LevelManager.h"

Brick::Brick(std::string id, float width, float height,  int HP, int score, std::string Texture, bool destructible)
	:m_id(id),m_HP(HP),m_score(score),m_destructible(destructible)
{
	TextureManager::LoadTexture(id, Texture);
	Add(new Sprite(TextureManager::GetTexture(id), Vector2(width, height)));
	Add(new BoxCollision(Vector2(width, height)));
}

Brick::Brick(Brick& other)
{
	SetPosition(other.GetPosition());
	Sprite* sprite = static_cast<Sprite*>(other.GetComponent<Sprite>());
	BoxCollision* bc = static_cast<BoxCollision*>(other.GetComponent<BoxCollision>());
	Add(new Sprite(*sprite));
	Add(new BoxCollision(*bc));
	m_id = other.m_id;
	m_HP = other.m_HP;
	m_score = other.m_score;
	m_destructible = other.m_destructible;
}

Brick* Brick::Clone() const
{
	return new Brick(const_cast<Brick&>(*this));
}

void Brick::OnCollisionEnterGO(Component* other)
{
	SoundManager::GetManager()->PlaySound(m_id + "hit");
	if (m_destructible)
	{
		m_HP--;
		if (m_HP == 0)
		{
			Destroy();
			LevelManager::BrickDestroyed(m_score);
			SoundManager::GetManager()->PlaySound(m_id + "break");
		}
	}
}

void Brick::setSize(Vector2 size)
{
	Sprite* sprite = static_cast<Sprite*>(GetComponent<Sprite>());
	BoxCollision* bc = static_cast<BoxCollision*>(GetComponent<BoxCollision>());
	sprite->SetSize(size);
	bc->SetSize(size);
}