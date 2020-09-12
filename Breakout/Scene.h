#pragma once
#include "GameObject.h"
#include "SoundManager.h"

class Scene
{
	static Scene m_activeScene;

	std::vector<GameObject*> m_gameObjects;
	std::string m_music;
	int m_musicId;
	bool m_gameObjectsAltered;
public:
	static Scene& GetActiveScene();
	static void LoadScene(Scene& scene);

	Scene();
	std::vector<GameObject*>& GetObjects();
	void Add(GameObject* gameObject);
	GameObject* GetByName(std::string name);
	void Destroy(GameObject* gameObject);
	void PlaceFront(GameObject* gameobject);

	void LoadMusic(std::string name, std::string link);
	void PlayMusic();
	void StopMusic();

	inline const bool InteruptIteration() const { return m_gameObjectsAltered; }

	void ProcessDestroyed();
	void Clear();
	void Process();
};