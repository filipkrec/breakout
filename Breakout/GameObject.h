#pragma once
#include "Component.h"
#include "Vector2.h"
#include <iostream>
#include <vector>

class Physics;
class Sprite;
class BoxCollision;
class CircleCollision;

class GameObject : public Component
{
protected:
    std::vector<Component*> m_children;
    Vector2 m_position;

public:
    GameObject(Vector2 position);

    template <class T> 
    T* GetComponent();

    void Add(Component* component) override;

    void Remove(Component* component) override;

    bool IsComposite() const override;

    void Operation() override;

    void Move(Vector2 movement);

    Vector2 GetPosition();
};