#pragma once
#include "GameObject.h"

class Scene
{
	static Scene m_activeScene;

	std::vector<GameObject*> m_gameObjects;
public:
	static Scene& GetActiveScene();
	static void LoadScene(Scene& scene);

	Scene();
	std::vector<GameObject*>& GetObjects();
	void Add(GameObject* gameObject);
	void Destroy(GameObject* gameObject);
	void Process();
};