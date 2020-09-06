#pragma once
#include "SDL.h"
#include "Vector2.h"
#include <map>

class Input
{
	static SDL_Event m_event;
	static std::map<Uint32, bool> m_pressed;
	static std::map<Uint32, bool> m_clicked;
	static bool m_leftMouseClicked;

	static bool m_running;
	static bool m_paused;

	static bool m_windowEvent;
	static Vector2 m_windowEventValues;
public :
	static void ProcessInput();
	static void PressKey(Uint32 key);
	static void ClickKey(Uint32 key);
	static void ClearKey(Uint32 key);

	static bool Pressed(Uint32 key);
	static bool Clicked(Uint32 key);
	static bool LMBClicked();

	static void TogglePause();

	static bool WindowEvent();
	static Vector2 GetWindowEventValues();

	static bool Running();
	static bool Paused();
	static void Clear();


};