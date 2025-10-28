#pragma once
#include "Commons.h"
class Editor
{
private:

	Editor() = default;
	virtual ~Editor() = default;
public:


	static Editor& Get() { static Editor editor; return editor; } //friend�� �����ϴ� �͵� ���ڴ� ����..


	Editor(const Editor&) = delete;
	Editor(const Editor&&) = delete;

	Editor operator= (Editor&& other) = delete;
	Editor operator= (Editor& other) = delete;

	//key �Է� �ް�, editor ���� ���� �Լ��� ���߿� InputManager�� ���ؼ� Ȯ���غ����� ����. �ϴ� 
	
private:
};

//Camera Imgui���� ����(�����̶�� ���ٴ� wrapping�� �����)
//�ϴ� Camera ���� ��������.
