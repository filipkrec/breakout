#include "Scene.h"

Scene* Scene::m_activeScene;

Scene::Scene() 
	: m_delete(false), m_gameObjectsAltered(false), m_musicId(0), m_music("")
{
	
}

std::vector<GameObject*>& Scene::GetObjects()
{
	return m_gameObjects;
}

void Scene::Add(GameObject* gameObject)
{
	m_gameObjectsAltered = true;
	m_gameObjects.push_back(gameObject);
}

GameObject* Scene::GetByName(std::string name)
{
	auto it = std::find_if(m_gameObjects.begin(), m_gameObjects.end(), [&name](GameObject* x) {
		return x->GetName() == name;
		});

	if (it != m_gameObjects.end())
		return *it;

	return nullptr;
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
			for (Component* c : x->GetChildren())
			{
				GameObject* child = dynamic_cast<GameObject*>(c);
				if (child)
					PlaceFront(child);
			}

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
	if (!m_gameObjectsAltered)
	{
		for (GameObject* obj : m_gameObjects)
		{
			obj->Process();
		}
	}
	m_gameObjectsAltered = false;
	ProcessDestroyed();
}

Scene& Scene::GetActiveScene()
{
	return *m_activeScene;
}

void Scene::LoadScene(Scene* scene, bool destroyMusic)
{
	if(m_activeScene)
	m_activeScene->Destroy(destroyMusic);

	m_activeScene = scene;

	if(destroyMusic)
		m_activeScene->PlayMusic();
}

void Scene::Destroy(bool destroyMusic)
{
	m_delete = true;

	if(destroyMusic)
		StopMusic();

	for (GameObject* x : m_gameObjects)
		x->Destroy();
}

void Scene::ProcessDestroyed()
{
	m_gameObjects.erase(
		std::remove_if(m_gameObjects.begin(), m_gameObjects.end(),
			[&](GameObject* x) {
				if (x->ToDestroy())
				{
					delete x;
					return true;
				}
				return false;
								}),
		m_gameObjects.end());

	if (m_delete)
		delete this;
}