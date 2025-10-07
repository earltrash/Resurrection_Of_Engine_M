#pragma once
#include <vector>
#include <array>
#include <memory>
#include "D3D11.h"
#include "DirectXMath.h"
#include <iostream>
using namespace DirectX;
typedef XMFLOAT4		COLOR;

struct PosNCol
{
	XMFLOAT3 POS;
	COLOR Color;
};

template<typename T>
inline void SafeRelease(T*& ptr)
{
	if (ptr) { ptr->Release(); ptr = nullptr; }
}

template<typename T>
inline void SafeDelete(T*& ptr)
{
	delete ptr; ptr = nullptr;
}

DWORD AlignCBSize(DWORD size);
int CreateVertexBuffer(ID3D11Device* pDev, LPVOID pData, UINT size, ID3D11Buffer** ppVB);
int CreateConstantBuffer(ID3D11Device* pDev, UINT size, ID3D11Buffer** ppCB);
HRESULT CreateDynamicConstantBuffer(ID3D11Device* pDev, UINT size, ID3D11Buffer** ppCB);
HRESULT CreateDynamicConstantBuffer(ID3D11Device* pDev, UINT size, LPVOID pData, ID3D11Buffer** ppCB);
int CreateInputLayout(ID3D11Device* pDev, D3D11_INPUT_ELEMENT_DESC* ed, DWORD num, ID3DBlob* pVSCode, ID3D11InputLayout** ppLayout);



