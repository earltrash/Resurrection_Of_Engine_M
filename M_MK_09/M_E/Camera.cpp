#include "pch.h"
#include "Camera.h"

void Camera::Initalize()
{
    this->AddComponent<KeyListenerComponent>(
        [this](const InputEvent& event) {
            this->CameraControl(event);
        }
    );
}



//������ msg -> ����� ���� �̺�Ʈ�� ��ȯȭ�� ����

//msg -> Inpurmanager �Է� ���� (UI - CHARACTER - ETC) Component�� ���� �ִ� Obj���� msg�� �����ؼ� ����. -> msg�� ���ٸ� ���� ó���� 

void Camera::CameraControl(InputEvent event)
{
  
    event.handled = true; // �׼� ó�� �Ϸ�
    m_dirty = true;
}

Cam_M Camera::GetCameraMem()
{
	return Mem;
}


#define Forward 0x57 //W
#define Left 0x41 //A
#define Back 0x53 //S
#define Right 0x44 //D 


void Camera::Update(float dTime)
{
    
   
    const float MOVE_SPEED = 20.0f;
    const float ROT_SPEED = 1.5f;  

    float currentMovAmount = 0.0f;
    float currentRotAmount = 0.0f;

    InputManager& input = InputManager::Get();


    // W (������)
    if (input.IsKeyPressed({ Forward })) {
        currentMovAmount += MOVE_SPEED * dTime;
    }
    // S (�ڷ�)
    if (input.IsKeyPressed({ Back })) {
        currentMovAmount -= MOVE_SPEED * dTime;
    }

    // A (���� ȸ��)
    if (input.IsKeyPressed({ Left })) {
        currentRotAmount -= ROT_SPEED * dTime;
    }
    // D (������ ȸ��)
    if (input.IsKeyPressed({ Right })) {
        currentRotAmount += ROT_SPEED * dTime;
    }


    if (currentRotAmount != 0.0f)
    {
        XMMATRIX ROTMATRRIX = XMMatrixRotationY(currentRotAmount);

        XMVECTOR look_vec = Mem.lookat - Mem.eye; // ���� �ü� ����

      
        XMVECTOR rotated_look_vec = XMVector3TransformNormal(look_vec, ROTMATRRIX);

      
        Mem.lookat = Mem.eye + rotated_look_vec;
    }

    if (currentMovAmount != 0.0f)
    {
      
        XMVECTOR look_dir = XMVector3Normalize(Mem.lookat - Mem.eye);

       
        XMVECTOR move_vec = look_dir * currentMovAmount;

       
        Mem.eye = XMVectorAdd(Mem.eye, move_vec);
        Mem.lookat = XMVectorAdd(Mem.lookat, move_vec);

       
    }

    m_dirty = (currentMovAmount != 0.0f || currentRotAmount != 0.0f);

}

void Camera::SetEye(XMVECTOR newEYE)
{
	Mem.eye = newEYE;

}
void Camera::SetLookAt(XMVECTOR newLookat)
{
	Mem.lookat = newLookat;

}
void Camera::Setup(XMVECTOR newUP)
{
	Mem.up = newUP;

}
void Camera::SetFov(float newFov)
{
	Mem.g_fFov = newFov;

}
void Camera::SetAspect(float newAspect)
{
	Mem.g_fAspect = newAspect;

}
void Camera::SetZNear(float newNear)
{
	Mem.g_fZnear = newNear;

}
void Camera::SetZFar(float newFar)
{
	Mem.g_fZfar = newFar;

}


