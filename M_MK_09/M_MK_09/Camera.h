#pragma once
#include "pch.h"
#include "Object.h"
#include "KeyListenerComponent.h"
#include "MouseListenerComponent.h"

struct Cam_M
{
	XMVECTOR eye{ 0.0f, 5.0f, -30.0f };		
	XMVECTOR lookat{ 0.0f, 5.0f, 0.0f };		
	XMVECTOR up{ 0.0f, 1.0f, 0.0f };			


	float	g_fFov = XMConvertToRadians(45);	//기본 FOV 앵글. Field of View (Y) 
	float	g_fAspect = 1.6f;					//가로:세로 비율. 960:600 = 1.6:1 (16:10) 800:600 = 1.33:1 (4:3) 
	float	g_fZnear = 1.0f;					//시야 최소 거리 (1.0m) 
	float	g_fZfar = 300.0f;					//시야 최대 거리 (300m) 
};

class Camera : public Object
{
public:
	Camera() = default;
	~Camera() = default;  
	

	void Initalize();

	Cam_M Mem;

	void CameraControl(InputEvent event);


public:

	void Update(float dTime);
	bool m_dirty = false;

	float Rot = 0;
	float Mov = 0;


public:
	Cam_M GetCameraMem();
	void SetEye (XMVECTOR newEYE);
	void SetLookAt (XMVECTOR newLookat);
	void Setup (XMVECTOR newUP); //얘는 거의 없지 않을까

	void SetFov(float newFov);
	void SetAspect(float newAspect);
	void SetZNear(float newNear); //얘는 거의 없지 않을까
	void SetZFar(float newFar); //얘는 거의 없지 않을까

	void SetDirty(bool val) {  m_dirty =false; }
	bool GetDirty() { return m_dirty; }
	
	void MouseMove(InputEvent event);
	void MouseWheel(InputEvent event);


};

