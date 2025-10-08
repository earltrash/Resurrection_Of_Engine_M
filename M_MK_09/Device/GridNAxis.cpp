#include "GridNAxis.h"
#include "Effect.h"
#include "Commons.h" // StrideFromFlag, VertexFlag 정의
#include <cassert>
#include <iostream>
using namespace DirectX;

//
// 기본 카메라 파라미터
//
XMVECTOR eye{ 0.0f, 30.0f, -30.0f };      // 카메라 위치
XMVECTOR lookat{ 0.0f, 30.0f, 0.0f };     // 바라보는 지점
XMVECTOR up{ 0.0f, 1.0f, 0.0f };          // 상방 벡터

float g_fFov = XMConvertToRadians(45.0f);
float g_fAspect = 1.6f;
float g_fZnear = 1.0f;
float g_fZfar = 300.0f;

//
// Grid + Axis 초기화
//
bool GridNAxis::Set_GridNAxis(ID3D11Device*& Dev)
{
    bool result = false;
    result = Set_Effect(Dev);
    if (!result)
    {
        std::cout << "GridNAxis Effect 생성 실패\n";
        assert(SUCCEEDED(result));
    }

#pragma region Axis
    const float L = 100.0f;

    //  이제 universal vertex 구조 사용 (Position + Color + DummyNormal)
    PosNCol axisVertices[] =
    {
        // X축 (빨강)
        { XMFLOAT3(0, 0, 0), XMFLOAT4(1, 0, 0, 1), },
        { XMFLOAT3(-L, 0, 0), XMFLOAT4(1, 0, 0, 1),  },

        // Y축 (초록)
        { XMFLOAT3(0, 0, 0), XMFLOAT4(0, 1, 0, 1), },
        { XMFLOAT3(0, L, 0), XMFLOAT4(0, 1, 0, 1),  },

        // Z축 (파랑)
        { XMFLOAT3(0, 0, 0), XMFLOAT4(0, 0, 1, 1), },
        { XMFLOAT3(0, 0, -L), XMFLOAT4(0, 0, 1, 1),  },
    };

    D3D11_BUFFER_DESC bd = {};
    bd.ByteWidth = sizeof(axisVertices);
    bd.Usage = D3D11_USAGE_IMMUTABLE;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData = {};
    InitData.pSysMem = axisVertices;

    HRESULT hr = Dev->CreateBuffer(&bd, &InitData, &m_AxisVB);
    if (FAILED(hr))
    {
        std::cout << "Axis VB 생성 실패\n";
        assert(SUCCEEDED(hr));
    }
#pragma endregion

#pragma region Grid
    GridVertices.clear();

    const int gridSize = 10;
    const float spacing = 10.0f;
    const float extent = gridSize * spacing;

    // grid 도 universal vertex 기반
    for (int i = -gridSize; i <= gridSize; ++i)
    {
        float x = i * spacing;
        float z = i * spacing;
        XMFLOAT4 lineColor = (i == 0) ? XMFLOAT4(1, 1, 1, 1) : XMFLOAT4(0.5f, 0.5f, 0.5f, 1);

        // Z축 평행선
        GridVertices.push_back({ XMFLOAT3(x, 0, -extent) ,lineColor });
        GridVertices.push_back({ XMFLOAT3(x, 0, extent) ,lineColor });

        // X축 평행선
        GridVertices.push_back({ XMFLOAT3(-extent, 0, z), lineColor });
        GridVertices.push_back({ XMFLOAT3(extent, 0, z), lineColor });
    }

    bd = {};
    bd.ByteWidth = static_cast<UINT>(sizeof(PosNCol) * GridVertices.size());
    bd.Usage = D3D11_USAGE_IMMUTABLE;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    InitData = {};
    InitData.pSysMem = GridVertices.data();

    hr = Dev->CreateBuffer(&bd, &InitData, &m_GridVB);
    if (FAILED(hr))
    {
        std::cout << "Grid VB 생성 실패\n";
        assert(SUCCEEDED(hr));
    }
#pragma endregion

    return S_OK;
}

//
// Effect 초기화
//
bool GridNAxis::Set_Effect(ID3D11Device*& Dev)
{
    fx = std::make_unique<Effect>();
    bool result = fx->Create(Dev, L"Shader/Default.fx", VertexFlag::VF_POSCOL);

    if (!result)
    {
        std::cout << "GridNAxis: Effect 생성 실패\n";
        return false;
    }

    XMMATRIX I = XMMatrixIdentity();
    XMMATRIX mView = XMMatrixLookAtLH(eye, lookat, up);
    XMMATRIX mProj = XMMatrixPerspectiveFovLH(g_fFov, g_fAspect, g_fZnear, g_fZfar);

    fx->SetWorld(I);
    fx->SetView(mView);
    fx->SetProj(mProj);
    fx->Update();

    return true;
}

//
// Draw
//
void GridNAxis::Draw()
{
    if (!fx) return;

    ID3D11DeviceContext* ctx = fx->GetContext();
    if (!ctx) return;

    ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    fx->Apply();

    UINT stride = static_cast<UINT>(StrideFromFlag(VertexFlag::VF_POSCOL));
    // stride = sizeof(Vertex);
    UINT offset = 0;

    if (m_AxisVB)
    {
        ctx->IASetVertexBuffers(0, 1, &m_AxisVB, &stride, &offset);
        ctx->Draw(6, 0);
    }

    if (m_GridVB)
    {
        ctx->IASetVertexBuffers(0, 1, &m_GridVB, &stride, &offset);
        ctx->Draw(static_cast<UINT>(GridVertices.size()), 0);
    }
}
