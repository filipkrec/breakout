#pragma once
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
};