#include "Scene.h"

Scene Scene::m_activeScene;

Scene::Scene()
	: m_gameObjectsAltered(false),m_musicId(0),m_music("")
{}

std::vector<GameObject*>& Scene::GetObjects()
{
	return m_gameObjects;
}

void Scene::Add(GameObject* gameObject)
{
	m_gameObjectsAltered = true;
	m_gameObjects.push_back(gameObject);
}

void Scene::Destroy(GameObject* gameObject)
{
	gameObject->Destroy();
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

void Scene::LoadMusic(std::string name, std::string link)
{
	SoundManager::GetManager()->AddSound(name, link);
	m_music = name;
}

void Scene::PlayMusic()
{
	if(!m_music.empty())
	m_musicId = SoundManager::GetManager()->PlaySound(m_music,true);
}

void Scene::StopMusic()
{
	SoundManager::GetManager()->StopSound(m_musicId);
}

void Scene::Process()
{
	m_gameObjectsAltered = false;
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
	m_activeScene.PlayMusic();
}

void Scene::Clear()
{
	StopMusic();
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