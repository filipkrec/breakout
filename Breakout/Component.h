#pragma once
#include "Vector2.h"
#include <string>

class Component {
protected:
    Component* m_parent;
public:
    virtual ~Component() {}
    void SetParent(Component* parent);
    Component* GetParent() const;
    virtual void Add(Component* component);
    virtual void Remove(Component* component);
    virtual bool IsComposite() const;

    virtual void Operation() = 0;

    virtual Component* GetCollision();
    virtual Component* GetPhysics();
    virtual Vector2 GetPosition() const;
    virtual void SetPosition(Vector2 newPosition);
    virtual void Translate(Vector2 translationVector);
};