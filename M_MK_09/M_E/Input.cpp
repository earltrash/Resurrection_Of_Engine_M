#include "pch.h"
#include "Input.h"

std::unordered_map<int, GameAction> KeyToActionMap = {
    
  //  { 0x1B, GameAction::TOGGLE_MENU },        // VK_ESCAPE -> 메뉴 토글
  //  { 0x49, GameAction::TOGGLE_INVENTORY },   // 'I' (0x49) -> 인벤토리 토글
    //{ 0x53, GameAction::TOGGLE_STATS },       // 'S' (0x53) -> 스탯 창 토글

    // ----------------------------------
    // 플레이어 이동 액션 (WASD)
    // ----------------------------------
    { 0x57, GameAction::PLAYER_FORWARD },     // 'W' (0x57) -> 앞으로
    { 0x41, GameAction::PLAYER_LEFT },        // 'A' (0x41) -> 왼쪽
    { 0x53, GameAction::PLAYER_BACKWARD },    // 'S' (0x53) -> 뒤로
    { 0x44, GameAction::PLAYER_RIGHT },       // 'D' (0x44) -> 오른쪽

    // ----------------------------------
    // 기타 액션
    // ----------------------------------
    { 0x20, GameAction::PLAYER_JUMP },        // VK_SPACE (0x20) -> 점프
    { 0x70, GameAction::DEBUG_TOGGLE }        // VK_F1 (0x70) -> 디버그 토글
};



