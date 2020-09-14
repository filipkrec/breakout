#include "Input.h"
#include "Vector2.h"

SDL_Event Input::m_event;
std::map<Uint32, bool> Input::m_pressed;
std::map<Uint32, bool> Input::m_clicked;
bool Input::m_leftMouseClicked = false;

bool Input::m_running = true;
bool Input::m_paused = false;

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
                m_windowEventValues.x = static_cast<float>(m_event.window.data1);
                m_windowEventValues.y = static_cast<float>(m_event.window.data2);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (m_event.button.button == SDL_BUTTON_LEFT)
                m_leftMouseClicked = true;
            break;
        case SDL_KEYDOWN:
            PressKey(m_event.key.keysym.sym);
            ClickKey(m_event.key.keysym.sym);
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
        m_pressed.insert({ key, true });
}

void Input::ClickKey(Uint32 key)
{
    auto search = m_clicked.find(key);

    if (search != m_clicked.end())
        search->second = true;
    else
        m_clicked.insert({ key, true });
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

bool Input::Clicked(Uint32 key)
{
    auto search = m_clicked.find(key);

    if (search != m_clicked.end() && search->second)
        return true;

    return false;
}

bool Input::Running()
{
    return m_running;
}


void Input::Clear()
{
    m_leftMouseClicked = false;

    for (auto& x : m_clicked)
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


bool Input::Paused()
{
    return m_paused;
}


void Input::TogglePause()
{
    m_paused = !m_paused;
}

bool Input::LMBClicked()
{
    return m_leftMouseClicked;
}


void Input::Exit()
{
    m_running = false;
}