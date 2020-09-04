#include "Paddle.h"

Paddle::Paddle()
    :GameObject(Vector2(680, 600))
{
    const int width = 200;
    const int height = 50;

    TextureManager::LoadTexture("Paddle", "Green.png");
    Add(new Sprite(TextureManager::GetTexture("Paddle"), Vector2(width, height)));
    Add(new Physics());
    Add(new BoxCollision(Vector2(width, height)));
}

void Paddle::Update()
{
    if(GetComponent<Physics>())
    if (Input::Pressed(SDLK_LEFT))
    {
        ((Physics*)GetComponent<Physics>())->SetSpeed(35);
        ((Physics*)GetComponent<Physics>())->SetAngle(180);
    }
    else if (Input::Pressed(SDLK_RIGHT))
    {
        ((Physics*)GetComponent<Physics>())->SetSpeed(35);
        ((Physics*)GetComponent<Physics>())->SetAngle(0);
    }
    else
    {
        ((Physics*)GetComponent<Physics>())->SetSpeed(0);
        ((Physics*)GetComponent<Physics>())->SetAngle(0);
    }

}