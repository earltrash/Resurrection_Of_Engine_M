#pragma once

#include <Windows.h>
#include <unordered_map>

enum class EventType {
    KeyDown,
    KeyUp,
    MouseMove,

    LButtonDown,
    LButtonUp,

    RButtonDown,
    RButtonUp,

    MouseWheel,
    
};



struct MousePos
{
    float x, y;
};

struct Key
{
    int virtualKeyCode;
};

struct InputEvent  //I/O�� ���� ���� UNION ���� ����ü 
{
    EventType type;
    union //Uninon�� ���� ���� ����, �޸� 
    {
        Key key;
        MousePos Pos;
    };
   
    //flag 
    bool handled = false;
};

enum class GameAction {
    // UI �׼�
    TOGGLE_INVENTORY,
    TOGGLE_MENU,
    TOGGLE_STATS,

    // �÷��̾� �̵� �׼�
    PLAYER_FORWARD,
    PLAYER_BACKWARD,
    PLAYER_LEFT,
    PLAYER_RIGHT,
    PLAYER_JUMP,

    // ��Ÿ �׼�
    DEBUG_TOGGLE,
    ACTION_UNBOUND // ���Ҵ�
};




extern std::unordered_map<int, GameAction> KeyToActionMap;
    