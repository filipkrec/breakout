#include "Scene.h"

Scene Scene::m_activeScene;

Scene::Scene(){}

std::vector<GameObject*>& Scene::GetObjects()
{
	return m_gameObjects;
}

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

Scene& Scene::GetActiveScene()
{
	return m_activeScene;
}

void Scene::LoadScene(Scene& scene)
{
	m_activeScene.Clear();
	m_activeScene = scene;
}

void Scene::Clear()
{
	m_gameObjects.erase(
		std::remove_if(m_gameObjects.begin(), m_gameObjects.end(),
			[&](GameObject* x) {return true; }),
		m_gameObjects.end());
}