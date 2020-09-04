#include "Input.h"
#include "Vector2.h"

SDL_Event Input::m_event;
std::map<Uint32, bool> Input::m_pressed;
bool Input::m_running = false;
bool Input::m_windowEvent;
Vector2 Input::m_windowEventValues;

void Input::ProcessInput()
{
    if (SDL_PollEvent(&m_event)) {
        switch (m_event.type) {
        case SDL_QUIT:
            m_running = false;
            break;
        case SDL_WINDOWEVENT:
            if (m_event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                m_windowEvent = true;
                m_windowEventValues.x = m_event.window.data1;
                m_windowEventValues.y = m_event.window.data2;
            }
            break;
        case SDL_KEYDOWN:
            PressKey(m_event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            ClearKey(m_event.key.keysym.sym);
            break;
        }
    }
}

void Input::PressKey(Uint32 key)
{
    auto search = m_pressed.find(key);

    if (search != m_pressed.end())
        search->second = true;
    else
        m_pressed.insert({ key,false });
}

void Input::ClearKey(Uint32 key)
{
    auto search = m_pressed.find(key);

    if (search != m_pressed.end())
        search->second = false;
}

bool Input::Pressed(Uint32 key)
{
    auto search = m_pressed.find(key);

    if (search != m_pressed.end() && search->second)
        return true;

    return false;
}

bool Input::GameOver()
{
    return m_running;
}

void Input::Clear()
{
    for (auto& x : m_pressed)
    {
        x.second = false;
    }
}

bool Input::WindowEvent()
{
    if (m_windowEvent)
    {
        m_windowEvent = false;
        return true;
    }
    return m_windowEvent;
}

Vector2 Input::GetWindowEventValues()
{
    return m_windowEventValues;
}