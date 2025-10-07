#include "GridNAxis.h"



//초기값

XMVECTOR eye{ 0.0f, 30.0f, -30.0f };		//카메라 위치.(Position)
XMVECTOR lookat{ 0.0f, 30.0f, 0.0f };		//바라보는 곳.(Position)
XMVECTOR up{ 0.0f, 1.0f, 0.0f };			//카메라 상방 벡터.(Direction)


float	g_fFov = XMConvertToRadians(45);	//기본 FOV 앵글. Field of View (Y) 
float	g_fAspect = 1.6f;					//가로:세로 비율. 960:600 = 1.6:1 (16:10) 800:600 = 1.33:1 (4:3) 
float	g_fZnear = 1.0f;					//시야 최소 거리 (1.0m) 
float	g_fZfar = 300.0f;					//시야 최대 거리 (300m) 

//해당 전역값을 Edittor의 전역 Camera를 통해서 받을까 아님. 
// Editor가 있고 Camera 를 member로 두는 형식으로 만들어 봐야겠다.





bool GridNAxis::Set_GridNAxis(ID3D11Device*& Dev)
{

    bool Result = false;
   Result = Set_Effect(Dev); // 거의 고정적인 vs ps 파일을 가져가기 때문에 

   if (!Result) std::cout << "GRIRD N AXIS EFFECT 생성 실패" << endl;
   assert(SUCCEEDED(Result));

#pragma region axis
    const float L = 100.0f; 

    PosNCol axisVertices[] =
    {
        // X 축 (빨강)
        { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
        { { -L,    0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },

        // Y 축 (초록)
        { { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
        { { 0.0f, L,    0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },

        // Z 축 (파랑)
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

    // Grid 정점 생성 (XZ 평면)
    for (int i = -gridSize; i <= gridSize; ++i)
    {
        float x = i * spacing;
        float z = i * spacing;

        // Z축 평행선: (x, 0, -extent) -> (x, 0, extent)
        GridVertices.push_back({ { x, 0.0f, -extent }, { 0.5f, 0.5f, 0.5f, 1.0f } });
        GridVertices.push_back({ { x, 0.0f, extent  }, { 0.5f, 0.5f, 0.5f, 1.0f } });

        // X축 평행선: (-extent, 0, z) -> (extent, 0, z)
        GridVertices.push_back({ { -extent, 0.0f, z}, { 0.5f, 0.5f, 0.5f, 1.0f } });
        GridVertices.push_back({ {extent, 0.0f, z }, { 0.5f, 0.5f, 0.5f, 1.0f } });
    }

     bd = {};
    bd.ByteWidth = sizeof(PosNCol) * GridVertices.size(); 
    bd.Usage = D3D11_USAGE_IMMUTABLE;                    
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

   
     InitData = {};
    InitData.pSysMem = GridVertices.data(); // 벡터의 내부 데이터 주소를 사용


    hr = Dev->CreateBuffer(&bd, &InitData, &m_GridVB); // m_GridVB에 저장
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
    result =  fx->Create(Dev, L"Shader/Default.fx"); //얘는 PROJDIR기준임.

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
        fx->Apply(); //위 get 함수 다 없앨까 생각중. ////////////////////////// device context에 다 처리 .
        
        //어찌 보면 얘네가 model 이긴 하지 
        if (m_AxisVB != nullptr && m_GridVB != nullptr)
        {
            UINT stride = sizeof(PosNCol);
            UINT offset = 0;
            cont->IASetVertexBuffers(0, 1, &m_AxisVB, &stride, &offset);
            cont->Draw(6, 0);

            cont->IASetVertexBuffers(0, 1, &m_GridVB, &stride, &offset);
            cont->Draw(GridVertices.size(), 0);
        }
        else cout << "? axis 랑 grid null인데ㅔ?" << endl;

    }
}
