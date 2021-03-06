#include "Component.h"

Component::Component()
    :m_active(true)
{
}

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

void Component::Process()
{
    if (m_active)
    {
        Operation();
    }
}

Vector2 Component::GetPosition() const { return m_parent->GetPosition(); }

void Component::SetName(std::string name) { m_parent->SetName(name); }
std::string& Component::GetName() const { return m_parent->GetName(); }

void Component::SetPosition(Vector2 newPosition) {}
void Component::Translate(Vector2 translationVector) {}

Component* Component::GetCircleCollision() { return m_parent -> GetCircleCollision(); }
Component* Component::GetPhysics() { return m_parent->GetPhysics(); }
Component* Component::GetBoxCollision() { return m_parent->GetBoxCollision(); }
Component* Component::GetSprite() { return m_parent->GetSprite(); }
Component* Component::GetText() { return m_parent->GetText(); }

void Component::OnCollisionEnter(Component* collidedOther)
{
    if (m_parent != nullptr)
    {
        m_parent->OnCollisionEnter(collidedOther);
    }
}

void Component::OnCollisionExit(Component* collidedOther)
{
    if (m_parent != nullptr)
    {
        m_parent->OnCollisionExit(collidedOther);
    }
}


void Component::Activate()
{
    m_active = true;
}

void Component::Deactivate()
{
    m_active = false;
}