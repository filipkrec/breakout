#include "Button.h"


Button::Button(SDL_Texture* background, std::string text, Vector2 position, Vector2 size, void(*onClick)(), bool textIn)
	: m_onClick(onClick)
{
	if (background != nullptr)
	Add(new Sprite(background, size));

	if(text != "")
	if (textIn)
	{
		Add(new Text(" " + text + " ", size / 1.5, SDL_Color{ 255,255,255 }, size / 6));
	}
	else
		Add(new Text(" " + text + " ", size, SDL_Color{ 255,255,255 }, size));

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


void Button::SetTextColor(SDL_Color color)
{
	Text* textObj = dynamic_cast<Text*>(GetText());

	if(textObj)
		textObj->SetColor(color);
}


void Button::SetText(std::string text)
{
	Text* textObj = dynamic_cast<Text*>(GetText());

	if (textObj)
		textObj->SetText(text);
}