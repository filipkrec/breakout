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
