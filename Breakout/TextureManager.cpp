#include "TextureManager.h"
#include "IL/il.h"
#include <algorithm>

TextureManager* TextureManager::m_instance;

TextureManager::TextureManager()
	:m_renderer(nullptr)
{
}

TextureManager* TextureManager::GetManager()
{
	if (!m_instance)
	{
		m_instance = new TextureManager();
	}
	return m_instance;
}

SDL_Renderer* TextureManager::GetRenderer()
{
	return m_renderer;
}

void TextureManager::SetRenderer(SDL_Renderer* rend)
{
	m_renderer = rend;
}

void TextureManager::LoadTexture(std::string name, std::string imgLink)
{
	if (!m_renderer)
	{
#ifdef _DEBUG
		std::cout << "ERROR: renderer null" << std::endl;
#endif
		return;
	}

	if (std::find_if(m_textures.begin(), m_textures.end(),
		[&name](const std::pair <std::string, SDL_Texture*>& x) { return x.first == name; })
		!= m_textures.end())
	{
#ifdef _DEBUG
		std::cout << "ERROR: texture already loaded -" << name << std::endl;
#endif
		return;
	}

	
	std::string path =  imgLink;
	path = "Assets/" + imgLink;

	SDL_Texture* tex;
	SDL_Surface* temp;
	if (path.substr(path.size() - 4) == ".dds")
	{
		ILboolean loaded = ilLoadImage(std::wstring(path.begin(), path.end()).c_str());

		if (!loaded)
		{
#ifdef _DEBUG
			std::cout << "ERROR: invalid link - " << path << std::endl;
#endif
			return;
		}

		temp = SDL_CreateRGBSurface(SDL_SWSURFACE, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_BITS_PER_PIXEL)
			, 0x000000ff,0x0000ff00, 0x00ff0000,0xff000000);
		SDL_LockSurface(temp);

		try
		{
			ilCopyPixels(0, 0, 0, temp->w, temp->h, 1, IL_RGBA, IL_UNSIGNED_BYTE, temp->pixels);
		}
		catch (int e)
		{
			static_cast<void>(e);
#ifdef _DEBUG
			std::cout << "ERROR: "<< e << "Unsupported image format" <<std::endl;
#endif
		}
		SDL_UnlockSurface(temp);
	}
	else
	{
		temp = IMG_Load(path.c_str());
	}

	tex = SDL_CreateTextureFromSurface(m_renderer, temp);
	SDL_FreeSurface(temp);

	if (tex)
		m_textures.push_back(std::make_pair(name, tex));
	else
	{
#ifdef _DEBUG
		std::cout << "ERROR: invalid link - " << path << std::endl;
#endif
	}

}

void TextureManager::LoadText(std::string name, std::string text, int size, const SDL_Color& color)
{
	if (std::find_if(m_textures.begin(), m_textures.end(),
		[&name, &color](const std::pair <std::string, SDL_Texture*>& x) 
		{ 
		return x.first == name + ColorToString(color);
		})
		!= m_textures.end())
	{
#ifdef _DEBUG
		std::cout << "ERROR: text already loaded - " << text << std::endl;
#endif
		return;
	}
	TTF_Font* font = TTF_OpenFont("Assets/Fonts/ariblk.ttf", size);

	if (!font)
	{
#ifdef _DEBUG
		std::cout << "ERROR: TTF_OpenFont - " << TTF_GetError() << std::endl;
#endif
		return;
	}

	//default color = white
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* msg = SDL_CreateTextureFromSurface(TextureManager::GetRenderer(), surfaceMessage);

	SDL_FreeSurface(surfaceMessage);

	if (msg)
		m_textures.push_back(std::make_pair(name + ColorToString(color), msg));
	else
	{
#ifdef _DEBUG 
		std::cout << "ERROR: message error - " << name << std::endl;
#endif
	}
}


SDL_Texture* TextureManager::GetTexture(std::string name)
{
	std::vector<std::pair <std::string, SDL_Texture*>>::iterator it = std::find_if(m_textures.begin(), m_textures.end(), 
		[&name](const std::pair <std::string, SDL_Texture*>& x) { return x.first == name; });
	
	if (it != m_textures.end())
		return (*it).second;
	else
	{
#ifdef _DEBUG
		std::cout << "ERROR: No Texture Found - " << name << std::endl;
#endif
		return nullptr;
	}
}

void TextureManager::DeleteTexture(std::string name)
{
	SDL_Texture* texture = nullptr;
	m_textures.erase(
		std::remove_if(m_textures.begin(), m_textures.end(),
			[&](const std::pair <std::string, SDL_Texture*> x) {
				if (x.first == name)
				{
					texture = x.second;
					return true;
				}
				return false;
			}),
		m_textures.end());

	SDL_DestroyTexture(texture);
}

void TextureManager::Clear()
{
	m_textures.erase(
		std::remove_if(m_textures.begin(), m_textures.end(),
			[&](const std::pair <std::string, SDL_Texture*> x) { 
				SDL_DestroyTexture(x.second);
				return true; }),
		m_textures.end());
}


std::string TextureManager::ColorToString(SDL_Color color)
{
	return std::to_string(color.r) + "," + std::to_string(color.g) + "," + std::to_string(color.b);
}