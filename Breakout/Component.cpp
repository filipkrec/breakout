#include "Component.h"

void Component::SetParent(Component* parent) {
    if (parent->IsComposite())
        m_parent = parent;
}

Component* Component::GetParent() const {
    return m_parent;
}

void Component::Add(Component* component) {}

void Component::Remove(Component* component) {}

bool Component::IsComposite() const {
    return false;
}

Vector2 Component::GetPosition() const { return Vector2::Zero(); }

void Component::SetPosition(Vector2 newPosition) {}
void Component::Translate(Vector2 translationVector) {}

Component* Component::GetCollision() { return nullptr; }
Component* Component::GetPhysics() { return nullptr; }