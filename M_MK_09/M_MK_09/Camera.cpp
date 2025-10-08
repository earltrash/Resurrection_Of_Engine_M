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



//저수준 msg -> 고수준 게임 이벤트로 변환화는 과정

//msg -> Inpurmanager 입력 제어 (UI - CHARACTER - ETC) Component를 갖고 있는 Obj만이 msg를 선택해서 받음. -> msg를 람다를 통해 처리함 

void Camera::CameraControl(InputEvent event)
{
  
    event.handled = true; // 액션 처리 완료
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


    // W (앞으로)
    if (input.IsKeyPressed({ Forward })) {
        currentMovAmount += MOVE_SPEED * dTime;
    }
    // S (뒤로)
    if (input.IsKeyPressed({ Back })) {
        currentMovAmount -= MOVE_SPEED * dTime;
    }

    // A (왼쪽 회전)
    if (input.IsKeyPressed({ Left })) {
        currentRotAmount -= ROT_SPEED * dTime;
    }
    // D (오른쪽 회전)
    if (input.IsKeyPressed({ Right })) {
        currentRotAmount += ROT_SPEED * dTime;
    }


    if (currentRotAmount != 0.0f)
    {
        XMMATRIX ROTMATRRIX = XMMatrixRotationY(currentRotAmount);

        XMVECTOR look_vec = Mem.lookat - Mem.eye; // 현재 시선 벡터

      
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


