#include "pch.h"
#include "InputManager.h"
#include <iostream>

#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp)) 

InputManager::InputManager()
{
    m_broadcaster = std::make_unique<EventDispatcher>();
}

InputManager::~InputManager()
{
}
bool InputManager::MsgCheck(MSG& msg)
{
    InputEvent event;

    switch (msg.message)
    {
    case WM_KEYDOWN:
        event.type = EventType::KeyDown;
        event.key.virtualKeyCode = (int)msg.wParam;
        InputManager::Get().m_broadcaster->Broadcast(event);
        InputManager::Get().m_keys[event.key.virtualKeyCode] = true;
        return true;
        break;
    case WM_KEYUP:

       ///* if (VK_F1 == msg.wParam)
       // {
       //     TogglelCancled();
       //     std::cout << "worked" << std::endl;
       //     return true;
       // }*/

        event.type = EventType::KeyUp;
        event.key.virtualKeyCode = (int)msg.wParam;
        InputManager::Get().m_broadcaster->Broadcast(event);
        InputManager::Get().m_keys[event.key.virtualKeyCode] = false;
        return true;
        break;
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:

        event.type = EventType::LButtonDown;
        event.Pos.x = (float)GET_X_LPARAM(msg.lParam);
        event.Pos.y = (float)GET_Y_LPARAM(msg.lParam);
        InputManager::Get().m_broadcaster->Broadcast(event);
        return true;
        break;
    case WM_LBUTTONUP:

        event.type = EventType::LButtonUp;
        event.Pos.x = (float)GET_X_LPARAM(msg.lParam);
        event.Pos.y = (float)GET_Y_LPARAM(msg.lParam);
        InputManager::Get().m_broadcaster->Broadcast(event);

        return true;
        break;
    case WM_RBUTTONDOWN:

        event.type = EventType::RButtonDown;
        event.Pos.x = (float)GET_X_LPARAM(msg.lParam);
        event.Pos.y = (float)GET_Y_LPARAM(msg.lParam);
        InputManager::Get().m_broadcaster->Broadcast(event);

        return true;
        break;
    case WM_RBUTTONUP:
        event.type = EventType::RButtonUp;
        event.Pos.x = (float)GET_X_LPARAM(msg.lParam);
        event.Pos.y = (float)GET_Y_LPARAM(msg.lParam);
        InputManager::Get().m_broadcaster->Broadcast(event);

        return true;
        break;

    default:
        return false; //나머지는 프로시저가 처리 -> system key로 나중에 viewport 수정하는 것도 넣자
        break;
    }
}

void InputManager::Clean()
{
    m_broadcaster->clean();

}



InputManager& InputManager::Get()
{
    static InputManager Instance;
    return Instance;
}


void InputManager::Update()
{
    
}

bool InputManager::IsMouseClicked(InputEvent button) const
{
    return false;
}



// 눌렸는지
bool InputManager::IsMousePressed(InputEvent button) const
{
    return false;
}



bool InputManager::IsKeyPressed(Key key) const
{
    if (key.virtualKeyCode >= 0 && key.virtualKeyCode < 256) {
        return m_keys[key.virtualKeyCode];
    }
    return false;
}



bool InputManager::IsKeyUp(Key key) const
{
    if (key.virtualKeyCode >= 0 && key.virtualKeyCode < 256) {
        return !m_keys[key.virtualKeyCode];
    }
    return false;
}
