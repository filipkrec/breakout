#include "GameObject.h"

GameObject::~GameObject()
{
    if (m_name == "Arena")
    {
        std::cout << "Arena!";
    }
    Clear();
}


GameObject::GameObject(Vector2 position)
    : m_destroy(false), m_collisionProcessed(false), m_position(position)
{
}

GameObject::GameObject(std::string name, Vector2 position)
    : m_destroy(false), m_collisionProcessed(false), m_position(position), m_name(name)
{
}

template <class T>
Component* GameObject::GetComponent()
{
    for (Component* comp : m_children)
    {
        if (typeid(*comp) == typeid(T))
            return comp;
    }

    // std::cout << "ERROR: no component found" << typeid(T).name() << std::endl;
    return nullptr;
}

GameObject* GameObject::GetChildGameObject(std::string name)
{
    GameObject* current;
    for (Component* comp : m_children)
    {
        current = dynamic_cast<GameObject*>(comp);

        if (current)
            if (current->GetName() == name)
                return current;
    }
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
        c->Process();
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

void GameObject::SetName(std::string name)
{
    m_name = name;
}

std::string& GameObject::GetName() const
{
    return const_cast<std::string&>(m_name);
}

Vector2 GameObject::GetPosition() const
{
    return m_position;
}


Component* GameObject::GetBoxCollision()
{
    return GetComponent<BoxCollision>();
}

Component* GameObject::GetCircleCollision()
{
    return GetComponent<CircleCollision>();
}

Component* GameObject::GetSprite()
{
    return (GetComponent<Sprite>());
}

Component* GameObject::GetPhysics()
{
    return GetComponent<Physics>();
}

Component* GameObject::GetText()
{
    return GetComponent<Text>();
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


void GameObject::Destroy()
{
    m_destroy = true;
}

void GameObject::Clear()
{
    std::string name = GetName();

    m_children.erase(
        std::remove_if(m_children.begin(), m_children.end(),
            [&](Component* x) {
                delete x;
                return true; }),
        m_children.end());
}

bool GameObject::ToDestroy()
{
    return m_destroy;
}


void GameObject::OnCollisionEnter(Component* collidedOther)
{
    if (!m_collisionProcessed)
    {
        m_collisionProcessed = true;
        for (Component* child : m_children)
        {
            child->OnCollisionEnter(collidedOther);
        }
        OnCollisionEnterGO(collidedOther);
    }
}

void GameObject::AllowCollisionProcess()
{
    m_collisionProcessed = false;
}

void GameObject::OnCollisionEnterGO(Component* collidedOther)
{
}