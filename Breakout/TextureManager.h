#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Vector2.h"
#include <vector>
#include <string>
#include <iostream>

class TextureManager
{
	static TextureManager* m_instance;
	std::vector<std::pair <std::string, SDL_Texture*>> m_textures;
	SDL_Renderer* m_renderer;
public:
	static TextureManager* GetManager();
	SDL_Renderer* GetRenderer();
	void SetRenderer(SDL_Renderer* rend);
	void LoadTexture(std::string name, std::string imgLink);
	void LoadText(std::string name, std::string text, int size = 24, const SDL_Color& color = { 255,255,255 });
	SDL_Texture* GetTexture(std::string name);
	void DeleteTexture(std::string name);
	void Clear();

	static std::string ColorToString(SDL_Color color);
};