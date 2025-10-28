#pragma once
#include "Commons.h"
class Editor
{
private:

	Editor() = default;
	virtual ~Editor() = default;
public:


	static Editor& Get() { static Editor editor; return editor; } //friend로 생성하는 것도 좋겠다 싶음..


	Editor(const Editor&) = delete;
	Editor(const Editor&&) = delete;

	Editor operator= (Editor&& other) = delete;
	Editor operator= (Editor& other) = delete;

	//key 입력 받고, editor 모드로 들어가는 함수는 나중에 InputManager를 통해서 확인해보도록 하자. 일단 
	
private:
};

//Camera Imgui와의 연동(연동이라기 보다는 wrapping에 가까움)
//일단 Camera 부터 시작하자.
