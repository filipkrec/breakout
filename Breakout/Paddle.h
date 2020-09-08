#pragma once
#include "GameObject.h"

class Paddle : public GameObject 
{
	int m_score;

public:
	Paddle();
	void AddScore(int score);
	
private:
	void Update() override;

};