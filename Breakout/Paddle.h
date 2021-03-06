#pragma once
#include "GameObject.h"

class Paddle : public GameObject 
{
	int m_score;
	int m_hitCounter;

public:
	const int m_width = 200;
	const int m_height = 20;
public:
	Paddle();
	void AddScore(int score);
	
private:
	void Update() override;
	virtual void OnCollisionEnterGO(Component* collidedOther) override;
	bool TunnelingCheck(BoxCollision* other);
};