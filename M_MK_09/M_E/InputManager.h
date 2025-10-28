#pragma once
#include "Input.h"
#include "Dispatcher.h"
class InputManager
{
public:
    static InputManager& Get();
    bool MsgCheck(MSG& msg); //InputManager���� �ٷ�� �Է��� �ƴ� ���� ���ν����� �ѱ�. 
    void Clean();

    void Update();

    // ���콺 ����
    MousePos GetMousePosition() const { return m_mousePosition; }
    bool IsMouseClicked(InputEvent button) const;
    bool IsMousePressed(InputEvent button) const;
    bool IsMouseReleased(InputEvent button) const;
    bool IsDoubleClicked() const { return m_isDoubleClicked; }

    // Ű���� ����
    bool IsKeyPressed(Key key) const;
    bool IsKeyUp(Key key) const;
    bool Cancled_Check() { return InputCancled; };
    void TogglelCancled() {  InputCancled = !InputCancled; };
    // �̷��� msgcheck�� ���� �ʰ� �Է�ó���� editor���� ó���� �� �ְ� �Ѵ�? //c�� ���� ��Ÿ�Ϸ�  

    std::unique_ptr<EventDispatcher> m_broadcaster = nullptr;

    // �ӽ�
    void SetWindowHandle(HWND hWnd) { m_hWnd = hWnd; }
private:
    HWND m_hWnd;    // �ӽ�
    InputManager();
    ~InputManager();

    // ���� ������.
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    MousePos m_mousePosition = { 0, 0 };

    bool m_mouseButtons[3] = { false }; // Left, Right, Middle
    bool m_previousMouseButtons[3] = { false };
    bool m_isDoubleClicked = false;


    //�ΰ����̱� �ѵ�, ĳ���� ��ŷ������ ���ɵ� ��.
    
    // Ű���� ����  
    bool m_keys[256] = { false };
    bool m_previousKeys[256] = { false };

    // ����Ŭ�� Ÿ�̸�
    float m_doubleClickTimer = 0.0f;
    const float DOUBLE_CLICK_TIME = 0.3f;
    bool InputCancled = false;
};