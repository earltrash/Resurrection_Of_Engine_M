#include "pch.h"
#include "Core.h"
#include "ResourceManager.h"
#include "DX_Renderer.h"
#include "Render_Helper.h"
//#include "RenderComponent.h" //임시.
#include "StaticMeshComponent.h"


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
     DX_Renderer::Instance().DX_SetUP(m_hWnd, w_width, w_height);
    return 1;
}
bool Core::ModuleInit()
{
    m_timer = make_unique<GameTimer>();
    g_camera = make_shared<Camera>(); 
    g_camera->Initalize();	
    m_obj = make_unique<Object>();
    g_camera->SetDirty(true); 

    //Wrapping needed
    RM_Set set;
    set.Device = DX_Renderer::Instance().m_Device.Get();
    set.DeviceContext = DX_Renderer::Instance().m_DXDC.Get();
    ResourceManager::Instance().Set_Up(set);

    
   

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
   // DX->UpdateGrid(dTime);
    CameraUpdate(dTime);
    m_obj->Update(dTime); 

    //
    // 
    // 물리 컴포넌트 
    // 렌더 컴포넌트 
    //
    //
}


void Core::Render(float dTime) //현 상황 모두 DX 내에서 처리. Component를 갖고 있는 애들을 D3D Render에 보내는 형식으로 처리
{
    Model* model = m_obj->GetComponent<StaticMeshComponent>()->GetModel();
    XMMATRIX pos = XMMatrixIdentity(); 

    pair<Model*, XMMATRIX> val = { model, pos };

    DX_Renderer::Instance().GetRH()->Get_Model_Vec().push_back(val);
    DX_Renderer::Instance().Render();
}

bool Core::MsgProcess(MSG& msg)
{
    return InputManager::Get().MsgCheck(msg);
}


//ㅋㅋ 폐기 예정.
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


float	fFov = XMConvertToRadians(45);	//기본 FOV 앵글. Field of View (Y) 
float	fAspect = 1.6f;					//가로:세로 비율. 960:600 = 1.6:1 (16:10) 800:600 = 1.33:1 (4:3) 
float	fZnear = 1.0f;					//시야 최소 거리 (1.0m) 
float	fZfar = 300.0f;					//시야 최대 거리 (300m) 


void Core::CameraUpdate(float dTime) //값 업데이트는 renderr랑 연동해야 하나 어지럽네
{
    g_camera->Update(dTime);

           
                Vector4 eye = g_camera->GetCameraMem().eye;
                Vector4 lookat = g_camera->GetCameraMem().lookat;
                Vector4 up = g_camera->GetCameraMem().up;

                Matrix mView = XMMatrixLookAtRH(eye, lookat, up);
                Matrix mProj = XMMatrixPerspectiveFovRH(fFov, fAspect, fZnear, fZfar);


                ///
                DX_Renderer::Instance().GetRH()->GetCB<cbDEFAULT>()->SetView(mView);
                DX_Renderer::Instance().GetRH()->GetCB<cbDEFAULT>()->SetProj(mProj);
                DX_Renderer::Instance().GetRH()->GetCB<cbDEFAULT>()->Update((DX_Renderer::Instance().m_DXDC.Get()));
                

                //일단 하드코딩 
                XMMATRIX mWorld = XMMatrixIdentity();
                              
                g_camera->SetDirty(false);
            

            //카메라의 더티 플래그 말고도, 캐릭터 움직임을 카메라가 따라갈 때 행렬 업데이트 되는 게 더 맞으니깐. 저 상황은 쉐이더 및 카메라 디버깅으로 만든거니 일단 무시. 
    
}

#define ROOTL_PATH  "Resources\\"

void Core::ModelParssing()
{
   
    //std::string path = "Models\\Fire_Extinguisher.fbx";
    //ResourceManager::Instance().ModelLoad(path, ModelType::Static);

    //std::string FullPath = ROOTL_PATH + path;
    //m_obj->AddComponent<StaticMeshComponent>();
    //m_obj->GetComponent<StaticMeshComponent>()->SetModel(FullPath);

   
    //std::string path =  "Models\\elephant.fbx";
    std::string path = "Models\\sphere_sampleScene_1cm.fbx";
    //std::string path = "Models\\u2ntitled.fbx";


    //std::string path = "Models\\Fire_Extinguisher.fbx";
    std::string FullPath = ROOTL_PATH + path;

    ResourceManager::Instance().ModelLoad(FullPath, ModelType::Static);


    m_obj->AddComponent<StaticMeshComponent>();
    m_obj->GetComponent<StaticMeshComponent>()->SetModel(FullPath);

   /* std::string path = "Models\\Cam.fbx";
    ResourceManager::Instance().ModelLoad(path, ModelType::Static);

    path = "Cam.fbx";
    m_obj->AddComponent<StaticMeshComponent>();
    m_obj->GetComponent<StaticMeshComponent>()->SetModel(path);*/



}

