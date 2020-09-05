#pragma once
#include "Arena.h"

Arena::Arena()
{
    wallT.SetPosition(Vector2(400, 100));
    wallT.Add(new Sprite(TextureManager::GetTexture("Green"), Vector2(700, 50)));

    wallB.SetPosition(Vector2(1150, 100));
    wallB.Add(new Sprite(TextureManager::GetTexture("Green"), Vector2(700, 50)));

    wallL.SetPosition(Vector2(400, 100));
    wallL.Add(new Sprite(TextureManager::GetTexture("Green"), Vector2(50, 700)));

    wallR.SetPosition(Vector2(400, 850));
    wallR.Add(new Sprite(TextureManager::GetTexture("Green"), Vector2(50, 700)));

    Scene::GetActiveScene().Add(&wallT);
    Scene::GetActiveScene().Add(&wallB);
    Scene::GetActiveScene().Add(&wallL);
    Scene::GetActiveScene().Add(&wallR);
}