#include "pch.h"
#include "Core.h"

void Core::Sets()
{
    HRESULT hr;
  hr = WinSet();
  assert(SUCCEEDED(hr));
  hr = DX_Set();
  assert(SUCCEEDED(hr));
  hr = ModuleInit();
  assert(SUCCEEDED(hr));
}
bool Core::WinSet()
{
	const wchar_t* className = L"지옥에서 돌아온 Engine_M";
	const wchar_t* windowName = L"Monster_World";

	HRESULT hr = __super::Create(className, windowName, 1920 ,1080);

    return hr;

}
bool Core::DX_Set()
{
    DX = make_shared< DX_Device>();
	HRESULT hr = DX->DX_SetUP(m_hWnd); //swap device context 모두 여기서 처리. 

    DX->SetViewPort(w_width, w_height);
	return hr;
}
bool Core::ModuleInit()
{
    m_timer = make_unique<GameTimer>();
    g_camera = make_unique<Camera>();
    g_camera->Initalize();

	return true;
}

void Core::GameLoop()
{
    float time = m_timer->DeltaTime();
    Update(time);
    Render(time);
}

//특정 키를 누르면 camera가 왔다갔다 하는 걸 만들고 싶

void Core::MessagePump()
{
    MSG msg = { 0 };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) //특정 메시지만 처리해야 함. 
        {
            //if (EditorMode()) continue; //시간의 흐름을 받지 않는 정지 상태긴 함. 추가적인 입력은 받지 않음.
            
            if (!MsgProcess(msg)) 
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {

            m_timer->Tick();
            GameLoop();
        }
    }
}

void Core::FixedUpdate(float dTimme)
{
}

void Core::Update(float dTime)
{
    DX->UpdateGrid(dTime);
    CameraUpdate(dTime);
}

void Core::Render(float dTime)
{
    DX->Clear();

    DX->DrawGridNAxis();
    DX->Flip();
}

bool Core::MsgProcess(MSG& msg)
{
    return InputManager::Get().MsgCheck(msg);
}

bool Core::EditorMode()
{
    return InputManager::Get().Cancled_Check();
}

void Core::End()
{
}

void Core::Release()
{
}

void Core::CameraUpdate(float dTime) //값 업데이트는 renderr랑 연동해야 하나 어지럽네
{
    g_camera->Update(dTime);

            if (g_camera->GetDirty())
            {
                XMVECTOR eye = g_camera->GetCameraMem().eye;
                XMVECTOR lookat = g_camera->GetCameraMem().lookat;
                XMVECTOR up = g_camera->GetCameraMem().up;

                // View 행렬 재계산
                XMMATRIX mView = XMMatrixLookAtLH(eye, lookat, up);

                // DX 시스템에 업데이트
                DX->GetGridFX()->GetFX()->SetView(&mView);
                DX->GetGridFX()->GetFX()->Update();

                g_camera->SetDirty(false);
            }
    
}

