#pragma once
#include "Input.h"
#include "Dispatcher.h"
class InputManager
{
public:
    static InputManager& Get();
    bool MsgCheck(MSG& msg); //InputManager에서 다루는 입력이 아닌 경우는 프로시저로 넘김. 
    void Clean();

    void Update();

    // 마우스 관련
    MousePos GetMousePosition() const { return m_mousePosition; }
    bool IsMouseClicked(InputEvent button) const;
    bool IsMousePressed(InputEvent button) const;
    bool IsMouseReleased(InputEvent button) const;
    bool IsDoubleClicked() const { return m_isDoubleClicked; }

    // 키보드 관련
    bool IsKeyPressed(Key key) const;
    bool IsKeyUp(Key key) const;
    bool Cancled_Check() { return InputCancled; };
    void TogglelCancled() {  InputCancled = !InputCancled; };
    // 이러면 msgcheck가 들어가지 않고 입력처리를 editor에서 처리할 수 있게 한다? //c의 전역 스타일로  

    std::unique_ptr<EventDispatcher> m_broadcaster = nullptr;

    // 임시
    void SetWindowHandle(HWND hWnd) { m_hWnd = hWnd; }
private:
    HWND m_hWnd;    // 임시
    InputManager();
    ~InputManager();

    // 복사 방지용.
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    MousePos m_mousePosition = { 0, 0 };

    bool m_mouseButtons[3] = { false }; // Left, Right, Middle
    bool m_previousMouseButtons[3] = { false };
    bool m_isDoubleClicked = false;


    //부가적이긴 한데, 캐릭터 마킹용으로 사용될듯 함.
    
    // 키보드 상태  
    bool m_keys[256] = { false };
    bool m_previousKeys[256] = { false };

    // 더블클릭 타이머
    float m_doubleClickTimer = 0.0f;
    const float DOUBLE_CLICK_TIME = 0.3f;
    bool InputCancled = false;
};