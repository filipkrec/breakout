#pragma once
#include "Scene.h"
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"

class Arena : public GameObject
{
public:
	static int m_minHeight;

private:

	GameObject* m_walls[4];
	GameObject* m_background;
	std::vector<Brick*> m_bricks;

	Vector2 m_paddleSpawn;
	Vector2 m_brickOrigin;
	int m_columnCount;

	int m_rowSpacing;
	int m_columnSpacing;
	int m_brickWidth;
	int m_brickHeight;

	int m_brickCount;


public:
	~Arena() override;
	Arena(int columnCount, int rowCount, int rowSpacing, int columnSpacing, SDL_Texture* wallTexture, SDL_Texture* backgroundTexture = nullptr, int brickWidth = 40, int brickHeight = 25);
	void AddToScene(Scene& scene);
	void LoadBricks(std::string layout, const std::vector<Brick*>& brickTypes);
	int GetBrickCount();

	const Vector2 GetPaddleStartingPoint(Paddle* paddle) const;
	const Vector2 GetBallStartingPoint(Ball* ball) const;
};