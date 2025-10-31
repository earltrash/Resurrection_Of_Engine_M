#include "pch.h"
#include "Core.h"
#include "WICTextureLoader.h"


//�������� �����Ǵ� shader ?
// 
//Object�� �����Ǳ� ���ؼ� ������ �ϴ� shader ��ü Ȥ�� �����͵� �ᱹ ���� ������ ������Ʈ�� ������ �ʿ��ϱ� ��. 
//Model�� �׳� Model�̰� 

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
	const wchar_t* className = L"�������� ���ƿ� Engine_M";
	const wchar_t* windowName = L"Monster_World";

	HRESULT hr = __super::Create(className, windowName, 1920 ,1080);

    return hr;

}
bool Core::DX_Set()
{
    DX = make_shared< DX_Renderer>(); 

     DX->DX_SetUP(m_hWnd, w_width, w_height); //Graphics & State ���� 

     DX->GridNAxis_SetUP(DX->m_Device.Get());

    return 1;
}
bool Core::ModuleInit()
{
    m_timer = make_unique<GameTimer>();

    g_camera = make_shared<Camera>(); 
    g_camera->Initalize();

    m_Asimmper = make_unique<Asimpper>();
    m_Asimmper->Initalize(DX->m_Device.Get(), DX->m_DXDC.Get()); //MODEL ���� -> ���� ������ ���� DEVICE, CONTEXT ����. //���ҽ� �ų����� ���յ� ���� Ȥ�� Mesh�� å��
	
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
   // DX->UpdateGrid(dTime);
    CameraUpdate(dTime);
    //
    // 
    // ���� ������Ʈ 
    // ���� ������Ʈ 
    //
    //
}

void Core::Render(float dTime) //�� ��Ȳ ��� DX ������ ó��. Component�� ���� �ִ� �ֵ��� D3D Render�� ������ �������� ó��
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


float	fFov = XMConvertToRadians(45);	//�⺻ FOV �ޱ�. Field of View (Y) 
float	fAspect = 1.6f;					//����:���� ����. 960:600 = 1.6:1 (16:10) 800:600 = 1.33:1 (4:3) 
float	fZnear = 1.0f;					//�þ� �ּ� �Ÿ� (1.0m) 
float	fZfar = 300.0f;					//�þ� �ִ� �Ÿ� (300m) 

ID3D11ShaderResourceView* g_DinoTextureRv = nullptr;

void Core::CameraUpdate(float dTime) //�� ������Ʈ�� renderr�� �����ؾ� �ϳ� ��������
{
    g_camera->Update(dTime);

           
                XMVECTOR eye = g_camera->GetCameraMem().eye;
                XMVECTOR lookat = g_camera->GetCameraMem().lookat;
                XMVECTOR up = g_camera->GetCameraMem().up;

                //// View ��� ����
                XMMATRIX mView = XMMatrixLookAtLH(eye, lookat, up);
                XMMATRIX mProj = XMMatrixPerspectiveFovLH(fFov, fAspect, fZnear, fZfar);


                //�ϴ� �ϵ��ڵ� 
                XMMATRIX mWorld = XMMatrixIdentity();
                m_obj->m_effect->SetWorld(mWorld);
                m_obj->m_effect->SetView(mView);
                m_obj->m_effect->SetProj(mProj);
                m_obj->m_effect->SetColor(COLOR{ 0.5,1,1,1 }); //�̰� ������� ��.
                m_obj->m_effect->Update();

                //����� ���� ī�޶� ������Ʈ�� �������� view�� proj�� �����ϴ� �ֱ� ����. ���⼭ obj�� ���� �ִ� shader�� ��İ��� �޴� �͵� ������ ���̱� ��. 
                
                DX->SetGridNAxis(mView); 
                g_camera->SetDirty(false);
            

            //ī�޶��� ��Ƽ �÷��� ����, ĳ���� �������� ī�޶� ���� �� ��� ������Ʈ �Ǵ� �� �� �����ϱ�. �� ��Ȳ�� ���̴� �� ī�޶� ��������� ����Ŵ� �ϴ� ����. 
    
}

void Core::ModelParssing()
{
   // m_Asimmper->LoadModel("Models/test.obj", DX->m_Device);
    m_Asimmper->LoadModel("Models/Cube_Coord.obj", DX->m_Device.Get());

    Model* model = m_Asimmper->m_Models.front();

#pragma region model
    //Vertex manualVertices[] =
    //{
    //    // V1 (Apex): (0.0f, 11.66025f, 0.0f) - ���� ����
    // { {0.0f, 5.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f} },

    // // V3 (Right Base): (5.0f, 3.0f, 0.0f) - ���� �Ķ�
    // { {10.0f, 3.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f} },

    // // V2 (Left Base): (-5.0f, 3.0f, 0.0f) - ���� �ʷ�
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

    m_obj->m_effect = effect;//�ϴ� ���󰪸�.

    HRESULT hr = S_OK;
    hr = DirectX::CreateWICTextureFromFile(DX->m_Device.Get(), L"../Data/dinoskin.jpg", nullptr, &g_DinoTextureRv);
    if (FAILED(hr))
    {
        std::cout << "�ؽ��� �ε� ����" << std::endl;
    }

    m_obj->m_effect->m_texture = g_DinoTextureRv;
    

}

