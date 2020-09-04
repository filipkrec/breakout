#include "GameObject.h"

GameObject::GameObject(Vector2 position)
{
    m_position = position;
}

template <class T>
Component* GameObject::GetComponent()
{
    for (Component* comp : m_children)
    {
        if (typeid(*comp) == typeid(T))
            return comp;
    }

    std::cout << "ERROR: no component found" << std::endl;
    return nullptr;
}

void GameObject::Add(Component* component) {
    this->m_children.push_back(component);
    component->SetParent(this);
}

void GameObject::Remove(Component* component) {
    std::remove_if(m_children.begin(), m_children.end(),
        [&](Component* x) {return x == component; }),

        component->SetParent(nullptr);
}

bool GameObject::IsComposite() const {
    return true;
}

void GameObject::Operation() {
    Update();

    for (Component* c : m_children) {
        c->Operation();
    }
}

void GameObject::Update()
{
}

void GameObject::Move(Vector2 movement)
{
    m_position.x += movement.x;
    m_position.y += movement.y;
}

Vector2 GameObject::GetPosition() const
{
    return m_position;
}


Component* GameObject::GetCollision()
{
    if (GetComponent<BoxCollision>())
        return GetComponent<BoxCollision>();
    else if (GetComponent<CircleCollision>())
        return GetComponent<CircleCollision>();
    else
        return nullptr;

    std::cout << "ERROR: no collision found" << std::endl;
}

Component* GameObject::GetPhysics()
{
    return GetComponent<Physics>();
}



void GameObject::SetPosition(Vector2 newPosition)
{
    m_position = newPosition;
}

void GameObject::Translate(Vector2 translationVector)
{
    m_position.x += translationVector.x;
    m_position.y += translationVector.y;
}