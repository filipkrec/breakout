#include "Button.h"


Button::Button(SDL_Texture* background, std::string text, Vector2 position, Vector2 size, void(*onClick)())
	: m_onClick(onClick)
{
	Add(new Sprite(background, size));
	Add(new Text(text, size / 1.5, SDL_Color{255,255,255}, size/6));
	Add(new BoxCollision(size));
	SetPosition(position);
}

void Button::Update()
{
	if (Input::LMBClicked())
	{
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x,&y);

		std::cout << x << "," << y << std::endl;

		if (((BoxCollision*)GetBoxCollision())->CheckPointCollision(Vector2(x, y)))
			m_onClick();
	}
}