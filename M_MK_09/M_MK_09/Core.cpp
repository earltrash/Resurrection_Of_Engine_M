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


    D3D11_DEPTH_STENCIL_DESC dsDesc = {};
    dsDesc.DepthEnable = FALSE; // Depth Test 비활성화
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; // Depth Write 비활성화
    dsDesc.DepthFunc = D3D11_COMPARISON_ALWAYS; // Test 무조건 통과 (DepthEnable=FALSE 시 불필요)
    // Stencil 설정은 일단 기본값으로 둡니다.


    D3D11_RASTERIZER_DESC rsDesc = {};
    rsDesc.FillMode = D3D11_FILL_SOLID;
    rsDesc.CullMode = D3D11_CULL_BACK;
    // ... 나머지 설정 ...

    DX->m_Device->CreateRasterizerState(&rsDesc, &(DX->pSolidRS));

	return hr;
}
bool Core::ModuleInit()
{
    m_timer = make_unique<GameTimer>();

    g_camera = make_unique<Camera>();
    g_camera->Initalize();

    m_Asimmper = make_unique<Asimpper>();
    m_Asimmper->Initalize(DX->m_Device, DX->m_DXDC); //MODEL 생성 -> 버퍼 생성을 위한 DEVICE, CONTEXT 주입.
	

    m_obj = make_unique<Object>();




    g_camera->SetDirty(true); 
    CameraUpdate(0.0f);

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
    
    DX->m_DXDC->RSSetState(DX->pSolidRS);
    //이건 유닛단위에서 실행하는 게 맞는듯, 일단 Object의 멤버로 두고, MeshComponent랑 animation Component로 분리 하자 (이건 발표 때 설명 

    DX->m_DXDC->OMSetDepthStencilState(DX->pNoDepthDS, 0);
    m_obj->Render(); //나중에는 component를 통해서 render를 하던가 하겠음 ㅇㅇ .
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



void Core::CameraUpdate(float dTime) //값 업데이트는 renderr랑 연동해야 하나 어지럽네
{
    g_camera->Update(dTime);

            if (g_camera->GetDirty()) 
            {
                XMVECTOR eye = g_camera->GetCameraMem().eye;
                XMVECTOR lookat = g_camera->GetCameraMem().lookat;
                XMVECTOR up = g_camera->GetCameraMem().up;

                //// View 행렬 재계산
                XMMATRIX mView = XMMatrixLookAtLH(eye, lookat, up);
                XMMATRIX mProj = XMMatrixPerspectiveFovLH(fFov, fAspect, fZnear, fZfar);


                XMMATRIX mScale = XMMatrixScaling(100.0f, 100.0f, 100.0f); // 100배 확대
                XMMATRIX mTrans = XMMatrixTranslation(0.0f, 30.0f, 0.0f); // Y=30 (카메라 LookAt Y축 위치)로 이동
                XMMATRIX mWorld = mScale * mTrans;
                // -----------------------------------------------------------------

                m_obj->m_effect->SetWorld(mWorld);
                m_obj->m_effect->SetView(mView);
                m_obj->m_effect->SetProj(mProj);
                m_obj->m_effect->SetColor(COLOR{ 1,1,1,1 });

                m_obj->m_effect->Update();

                //어찌보면 전역 카메라 오브젝트가 전역적인 view랑 proj를 관장하는 애긴 하지. 여기서 obj가 갖고 있는 shader의 행렬값을 받는 것도 괜찮아 보이긴 함. 
                
                // DX 시스템에 업데이트
                DX->GetGridFX()->GetFX()->SetView(mView); //Line 그리는 애들 ㅇㅇ 그 fx 
                DX->GetGridFX()->GetFX()->Update(); //line draw는 render 단계에서 
                g_camera->SetDirty(false);
            }

            //카메라의 더티 플래그 말고도, 캐릭터 움직임을 카메라가 따라갈 때 행렬 업데이트 되는 게 더 맞으니깐. 저 상황은 쉐이더 및 카메라 디버깅으로 만든거니 일단 무시. 
    
}

void Core::ModelParssing()
{
  //  m_Asimmper->LoadModel("Models/test.obj", DX->m_Device);

  //  Model* model = m_Asimmper->m_Models.front();

    Vertex manualVertices[] =
    {
        // V1: 위쪽 (밝은 빨강)
        { {0.0f, 30.0f + 10.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f} },

        // V2: 왼쪽 아래 (밝은 초록)
        { {-10.0f, 30.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f} },

        // V3: 오른쪽 아래 (밝은 파랑)
        { {10.0f, 30.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f} },
    };

    UINT size = sizeof(manualVertices);

    Model* model = new Model();
    model->Create(DX->m_Device, manualVertices, size, VertexFlag::VF_POSCOL);


    m_obj->m_model = model;
    Effect* effect = new Effect();
    effect->Create(DX->m_Device, L"Shader/Default.fx", VertexFlag::VF_POSCOL);
    m_obj->m_effect = effect;//일단 색상값만.
}

