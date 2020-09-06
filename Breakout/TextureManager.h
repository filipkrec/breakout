#pragma once
#include "SDL.h";
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Vector2.h"
#include <vector>
#include <string>
#include <iostream>

class TextureManager
{
	static std::vector<std::pair <std::string, SDL_Texture*>> m_textures;
	static SDL_Renderer* m_renderer;
public:
	static SDL_Renderer* GetRenderer();
	static void SetRenderer(SDL_Renderer* rend);
	static void LoadTexture(std::string name, std::string imgLink);
	static void LoadText(std::string name, std::string text, int size = 24, const SDL_Color& color = { 255,255,255 });
	static SDL_Texture* GetTexture(std::string name);
	static void DeleteTexture(std::string name);
};