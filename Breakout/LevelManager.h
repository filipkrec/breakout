#pragma once
#include "Level.h"

class LevelManager
{
	static std::vector<Level*>::iterator m_currentLevel;
	static std::vector<Level*> m_levels;

	static int m_currentScore;
	static int m_brickCount;

	static Paddle* m_activePaddle;
	static Ball* m_activeBall;

public:
	static void LoadLevel(std::string level);
	static void AddFirst();
	static void AddNext();
	static Level* GetCurrent();
	static void SetPaddle(Paddle* paddle);
	static void SetBall(Ball* ball);
	static void BrickDestroyed(int score);

	static void Clear();
};