#include "pch.h"
#include "Core.h"



//전역에서 관리되는 shader ?
// 
//Object가 렌더되기 위해서 가져야 하는 shader 객체 혹은 포인터도 결국 전역 정보와 오브젝트의 정보가 필요하긴 함. 
//Model은 그냥 Model이고 

void Core::Sets()
{
    HRESULT hr;
  hr = WinSet();
  assert(SUCCEEDED(hr));
  hr = DX_Set();
  assert(SUCCEEDED(hr));
  hr = ModuleInit();
  assert(SUCCEEDED(hr));

  ModelParssing();
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

    m_Asimmper = make_unique<Asimpper>();
    m_Asimmper->Initalize(DX->m_Device, DX->m_DXDC); //MODEL 생성 -> 버퍼 생성을 위한 DEVICE, CONTEXT 주입.
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
    

    for (const auto& models : m_Asimmper->m_Models)
    {
        models->Update(dTime);
    }


}

void Core::Render(float dTime)
{
    DX->Clear();

    DX->DrawGridNAxis();
    DX->Flip();

    //이건 유닛단위에서 실행하는 게 맞는듯, 일단 Object의 멤버로 두고, MeshComponent랑 animation Component로 분리 하자 (이건 발표 때 설명 

    for (const auto& models : m_Asimmper->m_Models)
    {
        models->Draw(dTime, PT_TRIANGLELIST,models->GetFlag());

        //set하고 여기서 shader에서 처리하던가 해야 할듯. mesh component는 model이랑 fx를 같이 들고 있어야 하는건가. 
    }


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





                //어찌보면 전역 카메라 오브젝트가 전역적인 view랑 proj를 관장하는 애긴 하지. 여기서 obj가 갖고 있는 shader의 행렬값을 받는 것도 괜찮아 보이긴 함. 
                
                // DX 시스템에 업데이트
                DX->GetGridFX()->GetFX()->SetView(&mView); //Line 그리는 애들 ㅇㅇ 그 fx 
                DX->GetGridFX()->GetFX()->Update();
                g_camera->SetDirty(false);
            }

            //카메라의 더티 플래그 말고도, 캐릭터 움직임을 카메라가 따라갈 때 행렬 업데이트 되는 게 더 맞으니깐. 저 상황은 쉐이더 및 카메라 디버깅으로 만든거니 일단 무시. 
    
}

void Core::ModelParssing()
{
    m_Asimmper->LoadModel("../Models/test.obj", DX->m_Device);
}

