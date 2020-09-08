#include "LevelManager.h"

std::vector<Level*>::iterator LevelManager::m_currentLevel;
std::vector<Level*> LevelManager::m_levels;

int LevelManager::m_currentScore;
int LevelManager::m_brickCount;

Paddle* LevelManager::m_activePaddle;
Ball* LevelManager::m_activeBall;


void LevelManager::LoadLevel(std::string level)
{
	m_levels.push_back(new Level(level));
	if (m_levels.size() > 0)
	{
		m_currentLevel = m_levels.begin();
		m_currentLevel;
	}
}

void LevelManager::AddFirst()
{
	if (m_levels.size() > 0)
	{
		m_currentScore = 0;
		if (*m_currentLevel)
			(*m_currentLevel)->ClearFromScene();

		m_currentLevel = m_levels.begin();
		(*m_currentLevel)->Initialise(m_activePaddle, m_activeBall, &Scene::GetActiveScene());
		m_brickCount = (*m_currentLevel)->GetBrickCount();
	}
}

void LevelManager::AddNext()
{
	if (std::distance(m_levels.begin(), m_currentLevel) < m_levels.size())
	{
		if (*m_currentLevel)
			(*m_currentLevel)->ClearFromScene();

		m_currentLevel++;
		(*m_currentLevel)->Initialise(m_activePaddle, m_activeBall, &Scene::GetActiveScene());
		m_brickCount = (*m_currentLevel)->GetBrickCount();

		Scene::GetActiveScene().PlaceFront(m_activePaddle);
		Scene::GetActiveScene().PlaceFront(m_activeBall);
	}
}

Level* LevelManager::GetCurrent()
{
	return *m_currentLevel;
}

void LevelManager::SetPaddle(Paddle* paddle)
{
	m_activePaddle = paddle;
}

void LevelManager::SetBall(Ball* ball)
{
	m_activeBall = ball;
}

void LevelManager::Clear()
{
	delete m_activeBall;
	delete m_activePaddle;

	m_levels.erase(
		std::remove_if(m_levels.begin(), m_levels.end(),
			[&](const Level* x) {return true; }),
		m_levels.end());
}

void LevelManager::BrickDestroyed(int score)
{
	m_currentScore += score;
	m_brickCount--;

	if (m_brickCount == 0)
	{
		LevelManager::AddNext();
	}
}