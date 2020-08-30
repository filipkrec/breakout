#pragma once
#include "Sprite.h"

class GameObject : public Component
{
protected:
    std::vector<Component*> m_children;

public:
    void Add(Component* component) override;

    void Remove(Component* component) override;

    bool IsComposite() const override;

    void Operation() override;
};