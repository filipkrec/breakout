#pragma once
#include "GameObject.h"
#include "Input.h"

class Button : public GameObject
{
	void (*m_onClick)();

public:
	Button(SDL_Texture* background, std::string text, Vector2 position, Vector2 size, void(*onClick)(), bool textIn = true);
	void SetTextColor(SDL_Color color);

private:
	void Update() override;

};