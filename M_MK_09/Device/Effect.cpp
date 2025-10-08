#pragma once
#include "Device.h" 
#include "Effect.h"
#include "Commons.h" 
#include <d3dcompiler.h>
#include "Model.h"

#pragma comment(lib, "D3DCompiler.lib")

Effect::Effect()
{
	m_pDev = nullptr;
	m_pDXDC = nullptr;

	m_pVS = nullptr;
	m_pPS = nullptr;

	m_pVSCode = nullptr;
	m_pCB = nullptr;
	m_pLayout = nullptr;

	// CBuffer 초기화
	ZeroMemory(&m_CBuffer, sizeof(ConstBuffer));
}
// Effect::~Effect()
Effect::~Effect()
{
	Release();
}

void Effect::Release()
{
	SafeRelease(m_pDXDC);
	SafeRelease(m_pVS);
	SafeRelease(m_pPS);
	SafeRelease(m_pVSCode);
	SafeRelease(m_pCB);
	SafeRelease(m_pLayout);
}

void Effect::SetWorld(XMMATRIX* mTM)
{
	XMFLOAT4X4 mView;
	XMStoreFloat4x4(&mView, *mTM);

	m_CBuffer.mTM = mView;
}

void Effect::SetMatrix(XMFLOAT4X4 mTM)
{
	
}

void Effect::SetView(XMMATRIX* mTM)
{
	XMFLOAT4X4 mView;
	XMStoreFloat4x4(&mView, *mTM);

	m_CBuffer.mView = mView;


}

void Effect::SetProj(XMMATRIX* mTM)
{
	XMFLOAT4X4 mView;
	XMStoreFloat4x4(&mView, *mTM);

	m_CBuffer.mProj = mView;
}

int Effect::Create(ID3D11Device* pDev, const TCHAR* filename)
{
	int res = 1;
	m_pDev = pDev;
	m_pDev->GetImmediateContext(&m_pDXDC);

	if (FAILED(Load(filename))) return 0;

	if (FAILED(CreateInputLayout())) return 0; //POS COL 

	ZeroMemory(&m_CBuffer, sizeof(ConstBuffer));
	if (FAILED(CreateDynaConstBuffer(sizeof(ConstBuffer), &m_CBuffer, &m_pCB))) return 0;


	return res;
}

// Effect::Load() - 셰이더 파일 컴파일 및 생성
int Effect::Load(const TCHAR* filename)
{
	HRESULT hr = S_OK;
	ID3D11VertexShader* pVS = nullptr;
	ID3DBlob* pVSCode = nullptr;

	hr = Compile(filename, "VS_Main", "vs_5_0", &pVSCode);
	if (FAILED(hr)) return hr;

	hr = m_pDev->CreateVertexShader(pVSCode->GetBufferPointer(), pVSCode->GetBufferSize(), nullptr, &pVS);
	if (FAILED(hr))
	{
		SafeRelease(pVSCode);
		return hr;
	}

	ID3D11PixelShader* pPS = nullptr;
	ID3DBlob* pPSCode = nullptr;

	hr = Compile(filename, "PS_Main", "ps_5_0", &pPSCode);
	if (FAILED(hr))
	{
		SafeRelease(pVS);
		SafeRelease(pVSCode);
		return hr;
	}

	hr = m_pDev->CreatePixelShader(pPSCode->GetBufferPointer(), pPSCode->GetBufferSize(), nullptr, &pPS);
	if (FAILED(hr))
	{
		SafeRelease(pVS);
		SafeRelease(pVSCode);
		SafeRelease(pPSCode);
		return hr;
	}
	SafeRelease(pPSCode); // PS 생성에 사용된 코드는 Layout에 필요 없으므로 해제

	m_pVS = pVS;
	m_pPS = pPS;
	m_pVSCode = pVSCode;
	

	return S_OK;
}

HRESULT Effect::Compile(const WCHAR* FileName, const  char* EntryPoint, const char* ShaderModel, ID3DBlob** ppCode)
{
	HRESULT hr = S_OK;
	ID3DBlob* pError = nullptr;

	UINT Flags = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
#ifdef _DEBUG
	Flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION; // 디버그 모드에서 최적화 건너뛰기
#endif

	hr = D3DCompileFromFile(FileName,
		nullptr, nullptr,
		EntryPoint,
		ShaderModel,
		Flags,
		0,
		ppCode,
		&pError
	);
	if (FAILED(hr))
	{
		std::wcout << " 셰이더 컴파일 실패! 파일: "
			<< std::wstring(FileName)
			<< ", Entry: " << EntryPoint
			<< ", Model: " << ShaderModel
			<< std::endl;

		if (pError)
		{
			std::string errMsg((char*)pError->GetBufferPointer(), pError->GetBufferSize());
			std::cout << "컴파일러 에러 메시지: \n" << errMsg << std::endl;
		}
	}

	SafeRelease(pError);
	return hr;

	SafeRelease(pError);
	return hr;
}

HRESULT Effect::CreateConstBuffer(UINT size, ID3D11Buffer** ppCB)
{
	HRESULT hr = S_OK;
	UINT alignSize = AlignCBSize(size);

	D3D11_BUFFER_DESC bd = {};
	//ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = alignSize;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	ID3D11Buffer* pCB = nullptr;
	hr = m_pDev->CreateBuffer(&bd, nullptr, &pCB);
	if (FAILED(hr))
	{
		std::cout << "Effect::CreateConstantBuffer : 상수버퍼 생성 실패" << std::endl;
		return hr;
	}

	//외부로 전달.
	*ppCB = pCB;

	return hr;
}

HRESULT Effect::CreateDynaConstBuffer(UINT size, void* pData, ID3D11Buffer** ppCB)
{
	HRESULT hr = S_OK;
	UINT alignSize = AlignCBSize(size);

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = alignSize;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = pData;
	sd.SysMemPitch = 0;
	sd.SysMemSlicePitch = 0;

	ID3D11Buffer* pCB = nullptr;

	hr = m_pDev->CreateBuffer(&bd, &sd, &pCB);
	if (FAILED(hr))
	{
		std::cout << "동적 상수 버퍼 생성 오류" << endl;;

		return hr;
	}

	*ppCB = pCB;

	return hr;
}


HRESULT Effect::UpdateDynaConstBuffer(ID3D11DeviceContext* pDXDC, ID3D11Resource* pBuff, void* pData, UINT size)
{
	HRESULT hr = S_OK;
	D3D11_MAPPED_SUBRESOURCE mr = {};

	hr = pDXDC->Map(pBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &mr);
	if (FAILED(hr))
	{
		std::cout << "동적 상수 버퍼 업뎅이트 오류" << endl;;
		return hr;
	}

	memcpy(mr.pData, pData, size);
	pDXDC->Unmap(pBuff, 0);

	return hr;
}

int Effect::CreateInputLayout() //이거 shader 만들 떄, flag 넣어서 처리하고 싶은데, Universal로 vertex를 받으니깐 offset을 잘 처리해야 될 거 같은데 
{
	HRESULT hr = S_OK;

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	hr = ::CreateInputLayout(m_pDev, layout, ARRAYSIZE(layout), m_pVSCode, &m_pLayout);

	if (FAILED(hr))
	{
		std::cout << "'레이아웃 셍성 오류" << endl;;
		return hr;
	}

	return S_OK;
}

void Effect::Apply(float dTime)
{
		m_pDXDC->VSSetShader(m_pVS, nullptr, 0);
		m_pDXDC->PSSetShader(m_pPS, nullptr, 0);
		m_pDXDC->IASetInputLayout(m_pLayout);
		m_pDXDC->VSSetConstantBuffers(0, 1, &m_pCB);
}

int Effect::Update(float dTime)
{
	XMMATRIX mWorld = XMLoadFloat4x4(&m_CBuffer.mTM);
	XMMATRIX mView = XMLoadFloat4x4(&m_CBuffer.mView);
	XMMATRIX mProj = XMLoadFloat4x4(&m_CBuffer.mProj);

	XMMATRIX mWVP = XMMatrixMultiply(mWorld, mView);
	mWVP = XMMatrixMultiply(mWVP, mProj);

	// 계산된 WVP를 CBuffer에 저장
	XMStoreFloat4x4(&m_CBuffer.mWVP, mWVP);

	UpdateDynaConstBuffer(m_pDXDC, m_pCB, &m_CBuffer, sizeof(ConstBuffer));
	return 1;
}

void Effect::SetColor(COLOR dTime)
{

}
