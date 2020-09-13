#include "SoundManager.h"

SoundManager* SoundManager::m_instance;

SoundManager* SoundManager::GetManager()
{
	if (!m_instance)
	{
		m_instance = new SoundManager();
	}
	return m_instance;
}

SoundManager::SoundManager()
	:m_masterVolume(100)
{
	Mix_Init(MIX_INIT_FLAC);
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
#ifdef _DEBUG
		std::cout << "ERROR: OpenAudio!" << std::endl;
#endif
	}
}

void SoundManager::AddSound(std::string name, std::string file)
{
	std::vector<std::pair <std::string, Mix_Chunk*>>::iterator it = std::find_if(m_sounds.begin(), m_sounds.end(),
		[&name](const std::pair <std::string, Mix_Chunk*>& x) { return x.first == name; });

	if (it != m_sounds.end())
	{
#ifdef _DEBUG
		std::cout << "Sound already loaded - " << file  << std::endl;
#endif
		return;
	}

	std::string link = "../Assets/" + file;
	Mix_Chunk* sample = Mix_LoadWAV(link.c_str());

	if (!sample)
	{
#ifdef _DEBUG
		std::cout << "Error: Sample " << file << " failed to load! " << std::endl;
		return;
#endif
	}
	
	sample->volume = m_masterVolume;

	m_sounds.push_back(std::pair<std::string, Mix_Chunk*>(name, sample));
}

void SoundManager::ChangeMasterVolume(int volumePercentage)
{
	m_masterVolume = volumePercentage;
	for (std::pair<std::string, Mix_Chunk*>& sound : m_sounds)
	{
		sound.second->volume = MIX_MAX_VOLUME * volumePercentage / 100.0f;
	}
}

void SoundManager::VolumeOff()
{
	m_masterVolume = 0;
	for (std::pair<std::string, Mix_Chunk*>& sound : m_sounds)
	{
		sound.second->volume = 0;
	}
}

void SoundManager::VolumeOn()
{
	m_masterVolume = 100;
	for (std::pair<std::string, Mix_Chunk*>& sound : m_sounds)
	{
		sound.second->volume = MIX_MAX_VOLUME;
	}
}

void SoundManager::ChangeVolume(std::string name, int volumePercentage)
{
	GetSound(name)->volume = MIX_MAX_VOLUME * volumePercentage / 100.0f;
}

Mix_Chunk* SoundManager::GetSound(std::string name)
{
	std::vector<std::pair <std::string, Mix_Chunk*>>::iterator it = std::find_if(m_sounds.begin(), m_sounds.end(),
		[&name](const std::pair <std::string, Mix_Chunk*>& x) { return x.first == name; });

	if (it != m_sounds.end())
		return (*it).second;
	else
	{
#ifdef _DEBUG
		std::cout << "ERROR: No sound Found - " << name << std::endl;
#endif
		return nullptr;
	}
}

int SoundManager::PlaySound(std::string name, bool loop)
{
	return Mix_PlayChannel(-1, GetSound(name), loop ? -1 : 0);
}

void SoundManager::StopSound(int soundId)
{
	Mix_HaltChannel(soundId);
}

void SoundManager::PauseSound(int soundId)
{
	Mix_Pause(soundId);
}

void SoundManager::ResumeSound(int soundId)
{
	Mix_Resume(soundId);
}

void SoundManager::Clear()
{
	Mix_CloseAudio();

	m_sounds.erase(
		std::remove_if(m_sounds.begin(), m_sounds.end(),
			[&](const std::pair <std::string, Mix_Chunk*> x) { 
				delete x.second;
				return true; 
			}),
		m_sounds.end());

	Mix_Quit();
}