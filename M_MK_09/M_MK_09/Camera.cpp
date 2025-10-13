#include "pch.h"
#include "Camera.h"

void Camera::Initalize()
{
    this->AddComponent<KeyListenerComponent>(
        [this](const InputEvent& event) {
            this->CameraControl(event);
        }
    );

    this->AddComponent<MouseListenerComponent>(
        [this](const InputEvent& event) {
            this->CameraControl(event);
        }
    );

}



//������ msg -> ����� ���� �̺�Ʈ�� ��ȯȭ�� ����

//msg -> Inpurmanager �Է� ���� (UI - CHARACTER - ETC) Component�� ���� �ִ� Obj���� msg�� �����ؼ� ����. -> msg�� ���ٸ� ���� ó���� 

void Camera::CameraControl(InputEvent event) //ȣ�� �Ǳ� ���ٵ�. UI�� EVENT ������ �����ϴ� ������ �� ������.
{
    if(event.type == EventType::MouseMove)
    {
        MouseMove(event);
    }
    else if (event.type == EventType::MouseWheel)
    {
        MouseWheel(event);
    }
}

Cam_M Camera::GetCameraMem()
{
	return Mem;
}

#define Forward 0x57 //W
#define Left 0x41 //A
#define Back 0x53 //S
#define Right 0x44 //D 

//camera mouse, key �� �� �ް� �ϸ� ���� �ϰڴ�. 

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

    //// A (���� ȸ��)
    //if (input.IsKeyPressed({ Left })) {
    //    currentRotAmount -= ROT_SPEED * dTime;
    //}
    //// D (������ ȸ��)
    //if (input.IsKeyPressed({ Right })) {
    //    currentRotAmount += ROT_SPEED * dTime;
    //}


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

//�ʱⰪ�̴ϱ�.
static float lastX = 980;
static float lastY = 540;

float Yaw;   // Y�� ȸ�� ����
float Pitch; // X�� ȸ�� ����

void Camera::MouseMove(InputEvent event)
{
    float sensitivity = 0.005f;
    float deltaX = event.Pos.x - lastX;
    float deltaY = event.Pos.y - lastY;

    lastX = event.Pos.x;
    lastY = event.Pos.y;

    // 1. ���Ϸ� �� ������Ʈ
    Yaw += deltaX * sensitivity;
    Pitch += deltaY * sensitivity; // ���콺 Y �������� Pitch�� ��ȭ

    //  Pitch ���� ���� (��89��) 
    // XMConvertToRadians(89.0f) ��� XM_PIDIV2 (PI/2) ��ó �� ���
    Pitch = max(-XMConvertToRadians(89.0f), Pitch);
    Pitch = min(XMConvertToRadians(89.0f), Pitch);

    // 3. ȸ�� ��� ���� (Yaw -> Pitch ���� ����)
    XMMATRIX rotation = XMMatrixRotationRollPitchYaw(Pitch, Yaw, 0); // Roll�� 0

    // 4. ���ο� Look ���� ���
    // �⺻ Look ����(0, 0, 1)�� ȸ������ �� Look ������ ����
    XMVECTOR defaultLook = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    XMVECTOR look_vec = XMVector3TransformNormal(defaultLook, rotation);
    look_vec = XMVector3Normalize(look_vec);

    // 5. ī�޶� ��ġ ����
    Mem.lookat = Mem.eye + look_vec;
    //  ���������� Up ���͵� �Բ� ������Ʈ ����: 
    // XMVECTOR worldUp = XMVectorSet(0, 1, 0, 0);
    // Mem.up = XMVector3TransformNormal(worldUp, rotation);
}

void Camera::MouseWheel(InputEvent event)
{
}


