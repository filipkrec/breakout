#include "Ball.h"

Ball::Ball()
	:GameObject(Vector2(775, 425))
{
    const int rad = 25;

    TextureManager::LoadTexture("Ball", "Textures/Balls/Ball1.dds");
    Add(new Sprite(TextureManager::GetTexture("Ball"), Vector2(rad * 2, rad * 2)));
    Add(new Physics());
    Add(new CircleCollision(rad));

    SetSpeed(4);
    SetAngle(270);
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
        (static_cast<Physics*>(GetComponent<Physics>()))->SetAngle(270);
    }
}