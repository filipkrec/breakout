#include "Component.h"

void Component::SetParent(Component* parent) {
    this->parent_ = parent;
}
Component* Component::GetParent() const {
    return this->parent_;
}
void Component::Add(Component* component) {}

void Component::Remove(Component* component) {}

bool Component::IsComposite() const {
    return false;
}
