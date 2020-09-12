#include "LevelManager.h"

LevelManager* LevelManager::m_instance;

LevelManager::LevelManager()
{
	SoundManager::GetManager()->AddSound("LifeLost", "Sounds/LifeLost.wav");
	SoundManager::GetManager()->AddSound("GameOver", "Sounds/GameOver.wav");
}

LevelManager* LevelManager::GetManager()
{
	if (!m_instance)
	{
		m_instance = new LevelManager();
	}
	return m_instance;
}

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
		m_currentLives = startingLives;
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
	if (std::distance(m_levels.begin(), m_currentLevel) < (m_levels.size() - 1))
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

void LevelManager::SetLivesText(Text* livesText)
{
	m_lives = livesText;
}

void LevelManager::SetScoreText(Text* scoreText)
{
	m_score = scoreText;
}

void LevelManager::Clear()
{
	delete m_activeBall;
	delete m_activePaddle;

	m_levels.erase(
		std::remove_if(m_levels.begin(), m_levels.end(),
			[&](const Level* x) {
				delete x;
				return true; }),
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

void LevelManager::LifeLost()
{
	m_currentLives--;
	SoundManager::GetManager()->PlaySound("LifeLost");
	if (m_currentLives == 0)
	{
		SoundManager::GetManager()->PlaySound("GameOver");
	}
}