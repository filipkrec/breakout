#pragma once
#include "SDL_mixer.h"
#include <vector>
#include <string>
#include <iostream>

class SoundManager
{
	std::vector<std::pair <std::string, Mix_Chunk*>> m_sounds;
	static SoundManager* m_instance;

public:
	static SoundManager* GetManager();
	void AddSound(std::string name, std::string file);
	void ChangeVolume(std::string name, int volumePercentage = 100);
	int PlaySound(std::string name, bool loop = false);
	void StopSound(int soundId);
	void PauseSound(int soundId);
	void ResumeSound(int soundId);
	void Clear();
private:
	SoundManager();
	Mix_Chunk* GetSound(std::string name);
};