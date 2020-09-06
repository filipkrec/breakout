#include "TextureManager.h"
#include "IL/il.h"

std::vector<std::pair <std::string, SDL_Texture*>> TextureManager::m_textures;
SDL_Renderer* TextureManager::m_renderer;

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
		std::cout << "ERROR: renderer null" << std::endl;
		return;
	}
	
	std::string path =  imgLink;
	path = "../Assets/" + imgLink;

	SDL_Texture* tex;
	SDL_Surface* temp;
	if (path.substr(path.size() - 4) == ".dds")
	{
		ILboolean ballean = ilLoadImage(std::wstring(path.begin(), path.end()).c_str());

		temp = SDL_CreateRGBSurface(SDL_SWSURFACE, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_BITS_PER_PIXEL)
			, 0x000000ff,0x0000ff00, 0x00ff0000,0xff000000);
		SDL_LockSurface(temp);

		try
		{
			ilCopyPixels(0, 0, 0, temp->w, temp->h, 1, IL_RGBA, IL_UNSIGNED_BYTE, temp->pixels);
		}
		catch (int e)
		{
			std::cout << "Unsupported image format" <<std::endl;
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
		std::cout << "ERROR: invalid link - " << path << std::endl;

}

void TextureManager::LoadText(std::string name, std::string text, int size, const SDL_Color& color)
{
	TTF_Font* font = TTF_OpenFont("ariblk.ttf", 24);

	if (!font)
	{
		std::cout << "ERROR: TTF_OpenFont - " << TTF_GetError() << std::endl;
		return;
	}

	//default color = white
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* msg = SDL_CreateTextureFromSurface(TextureManager::GetRenderer(), surfaceMessage);

	SDL_FreeSurface(surfaceMessage);

	if (msg)
		m_textures.push_back(std::make_pair(name, msg));
	else
		std::cout << "ERROR: message error - " << name << std::endl;
}


SDL_Texture* TextureManager::GetTexture(std::string name)
{
	std::vector<std::pair <std::string, SDL_Texture*>>::iterator it = std::find_if(m_textures.begin(), m_textures.end(), 
		[&name](const std::pair <std::string, SDL_Texture*>& x) { return x.first == name; });
	
	if (it != m_textures.end())
		return (*it).second;
	else
	{
		std::cout << "ERROR: No Texture Found - " << name << std::endl;
		return nullptr;
	}
}

void TextureManager::DeleteTexture(std::string name)
{
	m_textures.erase(
		std::remove_if(m_textures.begin(), m_textures.end(),
			[&](const std::pair <std::string, SDL_Texture*> x) {return x.first == name; }),
		m_textures.end());
}
