#include "Text.h"

Text::Text(std::string text, Vector2 size, const SDL_Color& color, Vector2 offset)
	: m_text(text),m_rect(Rect(Vector2(0, 0), Vector2(size.x, size.y))), m_offset(offset.x, offset.y),m_color(color)
{
	TextureManager::GetManager()->LoadText(text, text, m_size, color);
	m_texture = TextureManager::GetManager()->GetTexture(text + TextureManager::ColorToString(color));
}


void Text::Render()
{
	m_rect.x = static_cast<int>(GetPosition().x);
	m_rect.y = static_cast<int>(GetPosition().y);
	SDL_RenderCopy(TextureManager::GetManager()->GetRenderer(), m_texture, NULL, &m_rect.SDLRect());
}

void Text::Operation()
{
	Render();
}

Vector2 Text::GetPosition()
{
	return m_parent->GetPosition() + m_offset;
}


void Text::SetSize(Vector2 size)
{
	m_rect.w = static_cast<int>(size.x);
	m_rect.h = static_cast<int>(size.y);
}
void Text::SetOffset(Vector2 offset)
{
	m_offset.x = offset.x;
	m_offset.y = offset.y;
}

void Text::SetText(std::string text)
{
	m_text = text;
	TextureManager::GetManager()->DeleteTexture(m_text);
	TextureManager::GetManager()->LoadText(text, text, m_size, m_color);
	m_texture = TextureManager::GetManager()->GetTexture(text + TextureManager::ColorToString(m_color));
}

void Text::SetColor(SDL_Color color)
{
	m_color = color;
	TextureManager::GetManager()->DeleteTexture(m_text);
	TextureManager::GetManager()->LoadText(m_text, m_text, m_size, color);
	m_texture = TextureManager::GetManager()->GetTexture(m_text + TextureManager::ColorToString(color));
}