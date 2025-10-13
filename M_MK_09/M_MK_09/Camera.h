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


	float	g_fFov = XMConvertToRadians(45);	//�⺻ FOV �ޱ�. Field of View (Y) 
	float	g_fAspect = 1.6f;					//����:���� ����. 960:600 = 1.6:1 (16:10) 800:600 = 1.33:1 (4:3) 
	float	g_fZnear = 1.0f;					//�þ� �ּ� �Ÿ� (1.0m) 
	float	g_fZfar = 300.0f;					//�þ� �ִ� �Ÿ� (300m) 
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
	void Setup (XMVECTOR newUP); //��� ���� ���� ������

	void SetFov(float newFov);
	void SetAspect(float newAspect);
	void SetZNear(float newNear); //��� ���� ���� ������
	void SetZFar(float newFar); //��� ���� ���� ������

	void SetDirty(bool val) {  m_dirty =false; }
	bool GetDirty() { return m_dirty; }
	
	void MouseMove(InputEvent event);
	void MouseWheel(InputEvent event);


};

