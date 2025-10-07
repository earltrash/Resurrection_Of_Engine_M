#include "GridNAxis.h"



//�ʱⰪ

XMVECTOR eye{ 0.0f, 30.0f, -30.0f };		//ī�޶� ��ġ.(Position)
XMVECTOR lookat{ 0.0f, 30.0f, 0.0f };		//�ٶ󺸴� ��.(Position)
XMVECTOR up{ 0.0f, 1.0f, 0.0f };			//ī�޶� ��� ����.(Direction)


float	g_fFov = XMConvertToRadians(45);	//�⺻ FOV �ޱ�. Field of View (Y) 
float	g_fAspect = 1.6f;					//����:���� ����. 960:600 = 1.6:1 (16:10) 800:600 = 1.33:1 (4:3) 
float	g_fZnear = 1.0f;					//�þ� �ּ� �Ÿ� (1.0m) 
float	g_fZfar = 300.0f;					//�þ� �ִ� �Ÿ� (300m) 

//�ش� �������� Edittor�� ���� Camera�� ���ؼ� ������ �ƴ�. 
// Editor�� �ְ� Camera �� member�� �δ� �������� ����� ���߰ڴ�.





bool GridNAxis::Set_GridNAxis(ID3D11Device*& Dev)
{

    bool Result = false;
   Result = Set_Effect(Dev); // ���� �������� vs ps ������ �������� ������ 

   if (!Result) std::cout << "GRIRD N AXIS EFFECT ���� ����" << endl;
   assert(SUCCEEDED(Result));

#pragma region axis
    const float L = 100.0f; 

    PosNCol axisVertices[] =
    {
        // X �� (����)
        { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        { { -L,    0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },

        // Y �� (�ʷ�)
        { { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { { 0.0f, L,    0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },

        // Z �� (�Ķ�)
        { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
        { { 0.0f, 0.0f, -L    }, { 0.0f, 0.0f, 1.0f, 1.0f } }
    };

    UINT vertexCount = ARRAYSIZE(axisVertices);
    D3D11_BUFFER_DESC bd = {};
    bd.ByteWidth = sizeof(PosNCol) * vertexCount;
    bd.Usage = D3D11_USAGE_IMMUTABLE;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData = {};
    InitData.pSysMem = axisVertices;

    HRESULT hr;

    hr = Dev->CreateBuffer(&bd, &InitData, &m_AxisVB);
    if (FAILED(hr))
    {
        assert(SUCCEEDED(hr)); 
    }

#pragma endregion

#pragma region Grid
    GridVertices.clear();

    int gridSize = 10;
    float spacing = 10.0f;
    float extent = gridSize * spacing;

    // Grid ���� ���� (XZ ���)
    for (int i = -gridSize; i <= gridSize; ++i)
    {
        float x = i * spacing;
        float z = i * spacing;

        // Z�� ���༱: (x, 0, -extent) -> (x, 0, extent)
        GridVertices.push_back({ { x, 0.0f, -extent }, { 0.5f, 0.5f, 0.5f, 1.0f } });
        GridVertices.push_back({ { x, 0.0f, extent  }, { 0.5f, 0.5f, 0.5f, 1.0f } });

        // X�� ���༱: (-extent, 0, z) -> (extent, 0, z)
        GridVertices.push_back({ { -extent, 0.0f, z}, { 0.5f, 0.5f, 0.5f, 1.0f } });
        GridVertices.push_back({ {extent, 0.0f, z }, { 0.5f, 0.5f, 0.5f, 1.0f } });
    }

     bd = {};
    bd.ByteWidth = sizeof(PosNCol) * GridVertices.size(); 
    bd.Usage = D3D11_USAGE_IMMUTABLE;                    
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

   
     InitData = {};
    InitData.pSysMem = GridVertices.data(); // ������ ���� ������ �ּҸ� ���


    hr = Dev->CreateBuffer(&bd, &InitData, &m_GridVB); // m_GridVB�� ����
    if (FAILED(hr))
    {
        assert(SUCCEEDED(hr));
    }

  
#pragma endregion

    return S_OK;
}

bool GridNAxis::Set_Effect(ID3D11Device*& Dev)
{
    bool result = 0;

    fx = make_unique<Effect>();
    result =  fx->Create(Dev, L"Shader/Default.fx"); //��� PROJDIR������.

    XMMATRIX Iden = XMMatrixIdentity();
    fx->SetWorld(&Iden);

    XMMATRIX mView = XMMatrixLookAtLH(eye, lookat, up);
    XMMATRIX mProj = XMMatrixPerspectiveFovLH(g_fFov, g_fAspect, g_fZnear, g_fZfar);

    fx->SetView(&mView);
    fx->SetProj(&mProj);

    fx->Update();

    return result;
}

void GridNAxis::Draw()
{
    ID3D11DeviceContext* cont = fx->GetContext();

    if (fx && cont)
    {

        

        cont->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
        fx->Apply(); //�� get �Լ� �� ���ٱ� ������. ////////////////////////// device context�� �� ó�� .
        
        //���� ���� ��װ� model �̱� ���� 
        if (m_AxisVB != nullptr && m_GridVB != nullptr)
        {
            UINT stride = sizeof(PosNCol);
            UINT offset = 0;
            cont->IASetVertexBuffers(0, 1, &m_AxisVB, &stride, &offset);
            cont->Draw(6, 0);

            cont->IASetVertexBuffers(0, 1, &m_GridVB, &stride, &offset);
            cont->Draw(GridVertices.size(), 0);
        }
        else cout << "? axis �� grid null�ε���?" << endl;

    }
}
