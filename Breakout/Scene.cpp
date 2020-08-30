#include "Scene.h"

void Scene::Add(GameObject* gameObject)
{
	m_gameObjects.push_back(gameObject);
}

void Scene::Destroy(GameObject* gameObject)
{
	m_gameObjects.erase(
		std::remove_if(m_gameObjects.begin(), m_gameObjects.end(),
			[&](GameObject* x) {return x == gameObject; }),
		m_gameObjects.end());
}

void Scene::Process()
{
	for (GameObject* obj : m_gameObjects)
	{
		obj->Operation();
	}
}