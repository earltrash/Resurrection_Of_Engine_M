#pragma once
#include "Window.h"
#include "Device.h" 
#include "Modules.h" //Engine Module

#include "Camera.h"
#include "Asimpper.h"

using namespace std;

class Core : public Window
{
public:
	Core() = default;
	virtual ~Core() = default;

	void Sets();
	bool WinSet();
	bool DX_Set();
	bool ModuleInit();


	void GameLoop();
	void MessagePump();

	void FixedUpdate(float dTimme);
	void Update(float dTime);
	void Render(float dTime =0);

	bool MsgProcess(MSG& msg);
	bool EditorMode();

	void End();
	void Release();
	void CameraUpdate(float dTime);

	void Set_Width(float val) { w_width = val;} //초기화 단계에서는 이를 사용 안함 // DX와의 응용을 생각.
	void Set_Height(float val) { w_height = val;}

	void ModelParssing();




private:
	shared_ptr<DX_Device> DX = nullptr;
	
	unique_ptr<GameTimer> m_timer = nullptr;
	unique_ptr<Camera> g_camera = nullptr;
	unique_ptr<Asimpper> m_Asimmper = nullptr;


	unique_ptr<Object> m_obj = nullptr;

	//리소스 매니저
	//사운드 매니저
	//Input Manaager
	//
};

