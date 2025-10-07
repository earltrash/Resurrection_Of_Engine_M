#include "pch.h"
#include "Input.h"

std::unordered_map<int, GameAction> KeyToActionMap = {
    
  //  { 0x1B, GameAction::TOGGLE_MENU },        // VK_ESCAPE -> �޴� ���
  //  { 0x49, GameAction::TOGGLE_INVENTORY },   // 'I' (0x49) -> �κ��丮 ���
    //{ 0x53, GameAction::TOGGLE_STATS },       // 'S' (0x53) -> ���� â ���

    // ----------------------------------
    // �÷��̾� �̵� �׼� (WASD)
    // ----------------------------------
    { 0x57, GameAction::PLAYER_FORWARD },     // 'W' (0x57) -> ������
    { 0x41, GameAction::PLAYER_LEFT },        // 'A' (0x41) -> ����
    { 0x53, GameAction::PLAYER_BACKWARD },    // 'S' (0x53) -> �ڷ�
    { 0x44, GameAction::PLAYER_RIGHT },       // 'D' (0x44) -> ������

    // ----------------------------------
    // ��Ÿ �׼�
    // ----------------------------------
    { 0x20, GameAction::PLAYER_JUMP },        // VK_SPACE (0x20) -> ����
    { 0x70, GameAction::DEBUG_TOGGLE }        // VK_F1 (0x70) -> ����� ���
};



