#include "Paddle.h"

Paddle::Paddle()
    :GameObject(Vector2(725, 100))
{
    const int width = 150;
    const int height = 20;

    TextureManager::LoadTexture("Paddle", "Textures/Paddles/Paddle.dds");
    Add(new Sprite(TextureManager::GetTexture("Paddle"), Vector2(width, height)));
    Add(new Physics());
    Add(new BoxCollision(Vector2(width, height)));
}

void Paddle::Update()
{
    if (GetComponent<Physics>())
    if (Input::Pressed(SDLK_LEFT) || Input::Pressed(SDLK_a))
    {
        ((Physics*)GetComponent<Physics>())->SetSpeed(35);
        ((Physics*)GetComponent<Physics>())->SetAngle(180);
    }
    else if (Input::Pressed(SDLK_RIGHT) || Input::Pressed(SDLK_d))
    {
        ((Physics*)GetComponent<Physics>())->SetSpeed(35);
        ((Physics*)GetComponent<Physics>())->SetAngle(0);
    }
    else
    {
        ((Physics*)GetComponent<Physics>())->SetSpeed(0);
        ((Physics*)GetComponent<Physics>())->SetAngle(0);
    }

    if (Input::Clicked(SDLK_p))
    {
        Input::TogglePause();
    }

}