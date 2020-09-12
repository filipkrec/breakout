#pragma once
#include "Vector2.h"
#include <string>

class Component {
protected:
    Component* m_parent;
    bool m_active;
public:
    Component();
    virtual ~Component() {}
    void SetParent(Component* parent);
    Component* GetParent() const;
    virtual void Add(Component* component);
    virtual void Remove(Component* component);
    virtual bool IsComposite() const;

    void Process();
    virtual void Operation() = 0;

    virtual Component* GetCircleCollision();
    virtual Component* GetPhysics();
    virtual Component* GetBoxCollision();
    virtual Component* GetSprite();
    virtual Component* GetText();
    virtual Vector2 GetPosition() const;

    virtual void SetName(std::string name);
    virtual std::string& GetName() const;
    virtual void SetPosition(Vector2 newPosition);
    virtual void Translate(Vector2 translationVector);

    virtual void OnCollisionEnter(Component* collidedOther);
    virtual void OnCollisionExit(Component* collidedOther);

    void Activate();
    void Deactivate();
    inline const bool Active() const { return m_active; }
};