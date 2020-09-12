#include "LevelManager.h"
#include "Button.h"

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
		m_livesTxt->SetText(std::to_string(m_currentLives));
		m_currentScore = 0;
		m_scoreTxt->SetText(std::to_string(m_currentScore));

		if (*m_currentLevel)
			(*m_currentLevel)->ClearFromScene();

		m_currentLevel = m_levels.begin();
		(*m_currentLevel)->Initialise(m_activePaddle, m_activeBall, &Scene::GetActiveScene());
		m_brickCount = (*m_currentLevel)->GetBrickCount();
	}
}

void LevelManager::AddNext()
{
	if (std::distance(m_levels.begin(), m_currentLevel) + 1 < (m_levels.size()))
	{
		if (*m_currentLevel)
			(*m_currentLevel)->ClearFromScene();

		m_currentLevel++;
		(*m_currentLevel)->Initialise(m_activePaddle, m_activeBall, &Scene::GetActiveScene());
		m_brickCount = (*m_currentLevel)->GetBrickCount();

		Scene::GetActiveScene().PlaceFront(m_activePaddle);
		Scene::GetActiveScene().PlaceFront(m_activeBall);

		m_currentLevelTxt->SetText(std::to_string(std::distance(m_levels.begin(), m_currentLevel) + 1));
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
	m_livesTxt = livesText;
}

void LevelManager::SetScoreText(Text* scoreText)
{
	m_scoreTxt = scoreText;
}

void LevelManager::SetCurrentLevelText(Text* currentLevelText)
{
	m_currentLevelTxt = currentLevelText;
}

void LevelManager::Clear()
{
	m_scoreTxt = nullptr;

	m_currentLevelTxt = nullptr;

	m_livesTxt = nullptr;

	m_activeBall = nullptr;

	m_activePaddle = nullptr;

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

	m_scoreTxt->SetText(std::to_string(m_currentScore));

	m_brickCount--;

	if (m_brickCount == 0)
	{
		LevelManager::AddNext();
	}
}

void LevelManager::LifeLost()
{
	m_currentLives--;

	m_livesTxt->SetText(std::to_string(m_currentLives));

	SoundManager::GetManager()->PlaySound("LifeLost");
	if (m_currentLives == 0)
	{
		Scene::GetActiveScene().StopMusic();
		SoundManager::GetManager()->PlaySound("GameOver");
		m_activePaddle->Destroy();
		m_activeBall->Destroy();

		GameObject* UI = Scene::GetActiveScene().GetByName("UI");
		if (UI)
		{
			Button* gameOver = dynamic_cast<Button*>(UI->GetChildGameObject("GameOver"));
			if (gameOver)
			{
				gameOver->Activate();
			}
		}
	}
	else 
	{
		m_activePaddle->SetPosition(GetCurrent()->GetArena()->GetPaddleStartingPoint(m_activePaddle));
		m_activeBall->SetPosition(GetCurrent()->GetArena()->GetBallStartingPoint(m_activeBall));
		m_activeBall->SetAngle(m_activeBall->m_startingAngle);
		m_activeBall->SetSpeed(m_activeBall->m_startingSpeed);
	}
}