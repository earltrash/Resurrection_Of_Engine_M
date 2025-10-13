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

struct InputEvent  //I/O를 통한 최초 UNION 관리 구조체 
{
    EventType type;
    union //Uninon을 통한 통합 관리, 메모리 
    {
        Key key;
        MousePos Pos;
    };
   
    //flag 
    bool handled = false;
};

enum class GameAction {
    // UI 액션
    TOGGLE_INVENTORY,
    TOGGLE_MENU,
    TOGGLE_STATS,

    // 플레이어 이동 액션
    PLAYER_FORWARD,
    PLAYER_BACKWARD,
    PLAYER_LEFT,
    PLAYER_RIGHT,
    PLAYER_JUMP,

    // 기타 액션
    DEBUG_TOGGLE,
    ACTION_UNBOUND // 미할당
};




extern std::unordered_map<int, GameAction> KeyToActionMap;
    