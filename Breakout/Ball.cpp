#include "Ball.h"

Ball::Ball()
	:GameObject("Ball")
{
    TextureManager::GetManager()->LoadTexture("Ball", "Textures/Balls/Ball1.dds");
    Add(new Sprite(TextureManager::GetManager()->GetTexture("Ball"), Vector2(m_radius * 2, m_radius * 2)));
    Add(new Physics());
    Add(new CircleCollision(m_radius));
}

void Ball::Update()
{

}


void Ball::SetSpeed(int speed)
{
    if (GetComponent<Physics>())
    {
        (static_cast<Physics*>(GetComponent<Physics>()))->SetSpeed(speed);
    }
}

void Ball::SetAngle(int angle)
{
    if (GetComponent<Physics>())
    {
        (static_cast<Physics*>(GetComponent<Physics>()))->SetAngle(angle);
    }
}