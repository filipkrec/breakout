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
	gameObject->Clear();
	m_gameObjects.erase(
		std::remove_if(m_gameObjects.begin(), m_gameObjects.end(),
			[&](GameObject* x) {return x == gameObject; }),
		m_gameObjects.end());
}


void Scene::PlaceFront(GameObject* gameobject)
{
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
		if (*it == gameobject) {
			GameObject* x = *it; // or std::move(*it)
			m_gameObjects.erase(it);
			m_gameObjects.push_back(x);
			break;
		}
	}
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

void Scene::ProcessDestroyed()
{
	m_gameObjects.erase(
		std::remove_if(m_gameObjects.begin(), m_gameObjects.end(),
			[&](GameObject* x) {return x->ToDestroy(); }),
		m_gameObjects.end());
}