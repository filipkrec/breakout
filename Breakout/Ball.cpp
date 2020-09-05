#include "Ball.h"

Ball::Ball()
	:GameObject(Vector2(775, 425))
{
    const int rad = 25;

    TextureManager::LoadTexture("Ball", "Ball.png");
    Add(new Sprite(TextureManager::GetTexture("Ball"), Vector2(rad * 2, rad * 2)));
    Add(new Physics());
    Add(new CircleCollision(rad));

    ((Physics*)GetComponent<Physics>())->SetSpeed(4);
    ((Physics*)GetComponent<Physics>())->SetAngle(270);
}

void Ball::Update()
{

}