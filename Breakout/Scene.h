#pragma once
#include "GameObject.h"

class Scene
{
	std::vector<GameObject*> m_gameObjects;
public:
	void Add(GameObject* gameObject);
	void Destroy(GameObject* gameObject);
	void Process();
};