#pragma once
#include "SDL.h"
#include <map>

class Input
{
	static SDL_Event m_event;
	static std::map<Uint32, bool> m_pressed;
	static bool m_running;
public :
	static void ProcessInput();
	static void PressKey(Uint32 key);
	static void ClearKey(Uint32 key);
	static bool Pressed(Uint32 key);
	static bool GameOver();

	static void Clear();


};