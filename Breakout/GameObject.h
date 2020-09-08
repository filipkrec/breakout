#pragma once
#include "Component.h"
#include "Input.h"
#include "Sprite.h"
#include "Physics.h"
#include "BoxCollision.h"
#include "CircleCollision.h"
#include <iostream>
#include <vector>=

class GameObject : public Component
{
protected:
    std::vector<Component*> m_children;
    Vector2 m_position;

    bool m_destroy;
public:
    ~GameObject() override;

    GameObject();

    GameObject(Vector2 position);

    template <class T> 
    Component* GetComponent();

    void Add(Component* component) override;

    void Remove(Component* component) override;

    bool IsComposite() const override;

    void Operation() override;

    void Move(Vector2 movement);

    Vector2 GetPosition() const override;
    Component* GetCircleCollision() override;
    Component* GetPhysics() override;
    Component* GetBoxCollision() override;
    Component* GetSprite() override;

    void SetPosition(Vector2 newPosition) override;
    void Translate(Vector2 translationVector) override;

    void Destroy();
    bool ToDestroy();
    void Clear();

protected:

    virtual void Update();
};