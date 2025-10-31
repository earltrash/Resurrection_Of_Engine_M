#include "pch.h"
#include "Core.h"
#include "WICTextureLoader.h"


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
    DX = make_shared< DX_Renderer>(); 

     DX->DX_SetUP(m_hWnd, w_width, w_height); //Graphics & State 생성 

     DX->GridNAxis_SetUP(DX->m_Device.Get());

    return 1;
}
bool Core::ModuleInit()
{
    m_timer = make_unique<GameTimer>();

    g_camera = make_shared<Camera>(); 
    g_camera->Initalize();

    m_Asimmper = make_unique<Asimpper>();
    m_Asimmper->Initalize(DX->m_Device.Get(), DX->m_DXDC.Get()); //MODEL 생성 -> 버퍼 생성을 위한 DEVICE, CONTEXT 주입. //리소스 매너지로 통합될 예정 혹은 Mesh에 책임
	
    m_obj = make_unique<Object>();

    g_camera->SetDirty(true); 

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
   // DX->UpdateGrid(dTime);
    CameraUpdate(dTime);
    //
    // 
    // 물리 컴포넌트 
    // 렌더 컴포넌트 
    //
    //
}

void Core::Render(float dTime) //현 상황 모두 DX 내에서 처리. Component를 갖고 있는 애들을 D3D Render에 보내는 형식으로 처리
{
    DX->Clear();
     DX->StateSet_BeforeRender();
     DX->DrawGridNAxis();

   

    m_obj->Render();
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


float	fFov = XMConvertToRadians(45);	//기본 FOV 앵글. Field of View (Y) 
float	fAspect = 1.6f;					//가로:세로 비율. 960:600 = 1.6:1 (16:10) 800:600 = 1.33:1 (4:3) 
float	fZnear = 1.0f;					//시야 최소 거리 (1.0m) 
float	fZfar = 300.0f;					//시야 최대 거리 (300m) 

ID3D11ShaderResourceView* g_DinoTextureRv = nullptr;

void Core::CameraUpdate(float dTime) //값 업데이트는 renderr랑 연동해야 하나 어지럽네
{
    g_camera->Update(dTime);

           
                XMVECTOR eye = g_camera->GetCameraMem().eye;
                XMVECTOR lookat = g_camera->GetCameraMem().lookat;
                XMVECTOR up = g_camera->GetCameraMem().up;

                //// View 행렬 재계산
                XMMATRIX mView = XMMatrixLookAtLH(eye, lookat, up);
                XMMATRIX mProj = XMMatrixPerspectiveFovLH(fFov, fAspect, fZnear, fZfar);


                //일단 하드코딩 
                XMMATRIX mWorld = XMMatrixIdentity();
                m_obj->m_effect->SetWorld(mWorld);
                m_obj->m_effect->SetView(mView);
                m_obj->m_effect->SetProj(mProj);
                m_obj->m_effect->SetColor(COLOR{ 0.5,1,1,1 }); //이건 상관없긴 함.
                m_obj->m_effect->Update();

                //어찌보면 전역 카메라 오브젝트가 전역적인 view랑 proj를 관장하는 애긴 하지. 여기서 obj가 갖고 있는 shader의 행렬값을 받는 것도 괜찮아 보이긴 함. 
                
                DX->SetGridNAxis(mView); 
                g_camera->SetDirty(false);
            

            //카메라의 더티 플래그 말고도, 캐릭터 움직임을 카메라가 따라갈 때 행렬 업데이트 되는 게 더 맞으니깐. 저 상황은 쉐이더 및 카메라 디버깅으로 만든거니 일단 무시. 
    
}

void Core::ModelParssing()
{
   // m_Asimmper->LoadModel("Models/test.obj", DX->m_Device);
    m_Asimmper->LoadModel("Models/Cube_Coord.obj", DX->m_Device.Get());

    Model* model = m_Asimmper->m_Models.front();

#pragma region model
    //Vertex manualVertices[] =
    //{
    //    // V1 (Apex): (0.0f, 11.66025f, 0.0f) - 밝은 빨강
    // { {0.0f, 5.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f} },

    // // V3 (Right Base): (5.0f, 3.0f, 0.0f) - 밝은 파랑
    // { {10.0f, 3.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f} },

    // // V2 (Left Base): (-5.0f, 3.0f, 0.0f) - 밝은 초록
    // { {-10.0f, 3.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f} },
    //};

    //UINT size = sizeof(manualVertices);

    //Model* model = new Model();
    //model->Create(DX->m_Device, manualVertices, size, VertexFlag::VF_POSCOL);

#pragma endregion 
    
    m_obj->m_model = model;
    Effect* effect = new Effect();
    effect->Create(DX->m_Device.Get(), L"Shader/Demo_3.fx", VertexFlag::VF_POSCOLTEX); 
    ID3D11SamplerState* state = DX->Get_SamplerState().Get();
    effect->SetSampleDesc(state);

    m_obj->m_effect = effect;//일단 색상값만.

    HRESULT hr = S_OK;
    hr = DirectX::CreateWICTextureFromFile(DX->m_Device.Get(), L"../Data/dinoskin.jpg", nullptr, &g_DinoTextureRv);
    if (FAILED(hr))
    {
        std::cout << "텍스쳐 로드 실패" << std::endl;
    }

    m_obj->m_effect->m_texture = g_DinoTextureRv;
    

}

