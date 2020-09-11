#pragma once
#include "Component.h"
#include "Input.h"
#include "Sprite.h"
#include "Text.h"
#include "Physics.h"
#include "BoxCollision.h"
#include "CircleCollision.h"
#include <iostream>
#include <vector>=

class GameObject : public Component
{
    bool m_collisionProcessed;

protected:
    std::string m_name;
    std::vector<Component*> m_children;
    Vector2 m_position;

    bool m_destroy;

public:
    virtual ~GameObject() override;

    GameObject(Vector2 position = Vector2::Zero());

    GameObject(std::string name, Vector2 position = Vector2::Zero());

    template <class T> 
    Component* GetComponent();

    void Add(Component* component) override;

    void Remove(Component* component) override;

    bool IsComposite() const override;

    void Operation() override;

    void Move(Vector2 movement);

    std::string& GetName() const override;

    Vector2 GetPosition() const override;
    Component* GetCircleCollision() override;
    Component* GetPhysics() override;
    Component* GetBoxCollision() override;
    Component* GetSprite() override;
    Component* GetText() override;

    void SetPosition(Vector2 newPosition) override;
    void Translate(Vector2 translationVector) override;

    void Destroy();
    bool ToDestroy();
    void Clear();

    void OnCollisionEnter(Component* collidedOther) override;
    void AllowCollisionProcess();

protected:
    virtual void OnCollisionEnterGO(Component* collidedOther);
    virtual void Update();
};