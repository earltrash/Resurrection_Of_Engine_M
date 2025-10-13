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



//저수준 msg -> 고수준 게임 이벤트로 변환화는 과정

//msg -> Inpurmanager 입력 제어 (UI - CHARACTER - ETC) Component를 갖고 있는 Obj만이 msg를 선택해서 받음. -> msg를 람다를 통해 처리함 

void Camera::CameraControl(InputEvent event) //호출 되긴 할텐데. UI랑 EVENT 가지고 경쟁하는 구도면 좀 어려울듯ㅅ.
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

//camera mouse, key 둘 다 받게 하면 좋긴 하겠다. 

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

    //// A (왼쪽 회전)
    //if (input.IsKeyPressed({ Left })) {
    //    currentRotAmount -= ROT_SPEED * dTime;
    //}
    //// D (오른쪽 회전)
    //if (input.IsKeyPressed({ Right })) {
    //    currentRotAmount += ROT_SPEED * dTime;
    //}


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

//초기값이니깐.
static float lastX = 980;
static float lastY = 540;

float Yaw;   // Y축 회전 각도
float Pitch; // X축 회전 각도

void Camera::MouseMove(InputEvent event)
{
    float sensitivity = 0.005f;
    float deltaX = event.Pos.x - lastX;
    float deltaY = event.Pos.y - lastY;

    lastX = event.Pos.x;
    lastY = event.Pos.y;

    // 1. 오일러 각 업데이트
    Yaw += deltaX * sensitivity;
    Pitch += deltaY * sensitivity; // 마우스 Y 움직임은 Pitch를 변화

    //  Pitch 각도 제한 (±89도) 
    // XMConvertToRadians(89.0f) 대신 XM_PIDIV2 (PI/2) 근처 값 사용
    Pitch = max(-XMConvertToRadians(89.0f), Pitch);
    Pitch = min(XMConvertToRadians(89.0f), Pitch);

    // 3. 회전 행렬 생성 (Yaw -> Pitch 순서 권장)
    XMMATRIX rotation = XMMatrixRotationRollPitchYaw(Pitch, Yaw, 0); // Roll은 0

    // 4. 새로운 Look 벡터 계산
    // 기본 Look 벡터(0, 0, 1)를 회전시켜 새 Look 방향을 얻음
    XMVECTOR defaultLook = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    XMVECTOR look_vec = XMVector3TransformNormal(defaultLook, rotation);
    look_vec = XMVector3Normalize(look_vec);

    // 5. 카메라 위치 갱신
    Mem.lookat = Mem.eye + look_vec;
    //  선택적으로 Up 벡터도 함께 업데이트 가능: 
    // XMVECTOR worldUp = XMVectorSet(0, 1, 0, 0);
    // Mem.up = XMVector3TransformNormal(worldUp, rotation);
}

void Camera::MouseWheel(InputEvent event)
{
}


