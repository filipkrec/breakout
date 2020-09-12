#pragma once
#include "Level.h"

class LevelManager
{
	const int startingLives = 3;

	static LevelManager* m_instance;

	std::vector<Level*>::iterator m_currentLevel;
	std::vector<Level*> m_levels;

	int m_currentScore;
	Text* m_score;

	int m_currentLives;
	Text* m_lives;

	int m_brickCount;

	Paddle* m_activePaddle;
	Ball* m_activeBall;

public:
	static LevelManager* GetManager();

	LevelManager();
	void LoadLevel(std::string level);
	void AddFirst();
	void AddNext();
	Level* GetCurrent();
	void SetPaddle(Paddle* paddle);
	void SetBall(Ball* ball);
	void SetLivesText(Text* livesText);
	void SetScoreText(Text* scoreText);
	void BrickDestroyed(int score);
	void LifeLost();

	void Clear();
};