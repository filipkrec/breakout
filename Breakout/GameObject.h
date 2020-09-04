#pragma once
#include "Component.h"
#include "Vector2.h"
#include "Input.h"
#include "Physics.h"
#include "BoxCollision.h"
#include "CircleCollision.h"
#include <iostream>
#include <vector>

class GameObject : public Component
{
protected:
    std::vector<Component*> m_children;
    Vector2 m_position;

public:
    GameObject(Vector2 position);

    template <class T> 
    Component* GetComponent();

    void Add(Component* component) override;

    void Remove(Component* component) override;

    bool IsComposite() const override;

    void Operation() override;

    virtual void Update();

    void Move(Vector2 movement);

    Vector2 GetPosition() const override;
    Component* GetCollision() override;
    Component* GetPhysics() override;

    void SetPosition(Vector2 newPosition) override;
    void Translate(Vector2 translationVector) override;
};