#include "GameObject.h"

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
    for (Component* c : m_children) {
        c->Operation();
    }
}