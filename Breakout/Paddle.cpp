#include "Paddle.h"
#include "Arena.h"

Paddle::Paddle()
    :GameObject("Paddle"), m_score(0), m_hitCounter(0)
{

    TextureManager::GetManager()->LoadTexture("Paddle", "Textures/Paddles/Paddle.dds");
    SoundManager::GetManager()->AddSound("Paddle", "Sounds/Paddle.wav");
    Add(new Sprite(TextureManager::GetManager()->GetTexture("Paddle"), Vector2(m_width, m_height)));
    Add(new Physics());
    Add(new BoxCollision(Vector2(m_width, m_height)));
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

    if (Input::Clicked(SDLK_p) || Input::Clicked(SDLK_ESCAPE))
    {
        Input::TogglePause();
        GameObject* UI = Scene::GetActiveScene().GetByName("UI");
        GameObject* pausedMenu = UI->GetChildGameObject("Paused");

        if(pausedMenu)
        if (!pausedMenu->Active())
            pausedMenu->Activate();
        else
            pausedMenu->Deactivate();
    }

}

void Paddle::AddScore(int score)
{
    m_score += score;
}


void Paddle::OnCollisionEnterGO(Component* collidedOther)
{
    std::cout << "EXTRACOL" << std::endl;
    SoundManager::GetManager()->PlaySound("Paddle");
    Physics* ballPhys = dynamic_cast<Physics*>(collidedOther->GetPhysics());
    CircleCollision* circleCol = dynamic_cast<CircleCollision*>(collidedOther->GetCircleCollision());
    if (ballPhys)
    {
        if (circleCol->GetCollidingCount() > 0)
        {
            BoxCollision* temp = circleCol->GetColliding().at(0);
            if (TunnelingCheck(temp)) 
                return; //dont override physics to prevent tunneling
        }

        m_hitCounter++;
        if (m_hitCounter > 5)
        {
            m_hitCounter = 0;
            if (ballPhys->GetSpeed() < Ball::m_maxSpeed);
            ballPhys->SetSpeed(ballPhys->GetSpeed() + 1);
        }
        Vector2 centerToBall =
            Vector2(
                static_cast<CircleCollision*>(collidedOther->GetCircleCollision())->GetCenter().x
                - (GetPosition().x + static_cast<BoxCollision*>(GetBoxCollision())->GetCollisionRect().w / 2),
                static_cast<CircleCollision*>(collidedOther->GetCircleCollision())->GetCenter().y
                - (GetPosition().y - 100)
            );
        ballPhys->SetAngle(Vector2::VecToAngle(centerToBall));
    }
}

bool Paddle::TunnelingCheck(BoxCollision* other)
{
    if (other->GetCollisionRect().h >= Arena::m_minHeight) //other = vertWall
        return true;
    else
        return false;
}