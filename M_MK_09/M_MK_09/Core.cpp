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
	const wchar_t* className = L"�������� ���ƿ� Engine_M";
	const wchar_t* windowName = L"Monster_World";

	HRESULT hr = __super::Create(className, windowName, 1920 ,1080);

    return hr;

}
bool Core::DX_Set()
{
    DX = make_shared< DX_Device>();
	HRESULT hr = DX->DX_SetUP(m_hWnd); //swap device context ��� ���⼭ ó��. 

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

//Ư�� Ű�� ������ camera�� �Դٰ��� �ϴ� �� ����� ��

void Core::MessagePump()
{
    MSG msg = { 0 };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) //Ư�� �޽����� ó���ؾ� ��. 
        {
            //if (EditorMode()) continue; //�ð��� �帧�� ���� �ʴ� ���� ���±� ��. �߰����� �Է��� ���� ����.
            
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

void Core::CameraUpdate(float dTime) //�� ������Ʈ�� renderr�� �����ؾ� �ϳ� ��������
{
    g_camera->Update(dTime);

            if (g_camera->GetDirty())
            {
                XMVECTOR eye = g_camera->GetCameraMem().eye;
                XMVECTOR lookat = g_camera->GetCameraMem().lookat;
                XMVECTOR up = g_camera->GetCameraMem().up;

                // View ��� ����
                XMMATRIX mView = XMMatrixLookAtLH(eye, lookat, up);

                // DX �ý��ۿ� ������Ʈ
                DX->GetGridFX()->GetFX()->SetView(&mView);
                DX->GetGridFX()->GetFX()->Update();

                g_camera->SetDirty(false);
            }
    
}

