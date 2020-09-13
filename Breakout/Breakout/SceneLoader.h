#pragma once
#include "Scene.h"

class SceneLoader
{
public:
	static void LoadMenu();
	static void ReloadMenu();
	static void LoadHighScores();
	static void LoadOptions();
	static void LoadGame();
	static void LoadUI();
	static void FillBackground(Scene* scene);
};