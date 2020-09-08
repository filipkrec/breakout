#include "LevelManager.h"

std::vector<Level*>::iterator LevelManager::m_currentLevel;
std::vector<Level*> LevelManager::m_levels;

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
		if (*m_currentLevel)
			(*m_currentLevel)->ClearFromScene();

		m_currentLevel = m_levels.begin();
		(*m_currentLevel)->Initialise(m_activePaddle, m_activeBall, &Scene::GetActiveScene());
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