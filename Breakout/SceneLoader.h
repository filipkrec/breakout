#pragma once
#include "Scene.h"

class SceneLoader
{
	static const int unitsX = 1600;
	static const int unitsY = 900;

public:
	static void LoadMenu();
	static void LoadGame();
	static void LoadUI();
	static void FillBackground(Scene* scene);
};