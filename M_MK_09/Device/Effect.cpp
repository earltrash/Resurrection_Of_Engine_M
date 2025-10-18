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

void Effect::SetView(XMMATRIX TM)
{
	auto cb = GetConstantBuffer<cbDEFAULT>();

	if (cb)
	{
		cb->SetView(TM);
	}


}

void Effect::SetProj(XMMATRIX TM)
{
	auto cb = GetConstantBuffer<cbDEFAULT>();
	if (cb)
	{
		cb->SetProj(TM);
	}
}

void Effect::SetWorld(XMMATRIX TM)
{
	auto cb = GetConstantBuffer<cbDEFAULT>();
	if (cb)
	{
		cb->SetTM(TM);
	}
}

void Effect::SetMatrix(XMMATRIX TM)
{
	auto cb = GetConstantBuffer<cbDEFAULT>();
	if (cb)
	{
		cb->SetTM(TM);
	}
}

void Effect::SetColor(COLOR col)
{
	auto cb = GetConstantBuffer<cbDEFAULT>();
	if (cb)
	{
		cb->SetColor(col);
	}
}


int Effect::Create(ID3D11Device* pDev, const TCHAR* filename, VertexFlag flag)
{
	int res = 1;

	//장치 정보 획득.
	m_pDev = pDev;
	m_pDev->GetImmediateContext(&m_pDXDC);	//획득한 핸들은 꼭 Release 해야 합니다.

	// 셰이더 로드.
	Load(filename);
	CreateInputLayout(flag , m_pVSCode);

	Createbuffer_wrapped(flag);

	Update();


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
		/*std::wcout << " 셰이더 컴파일 실패! 파일: "
			<< std::wstring(FileName)
			<< ", Entry: " << EntryPoint
			<< ", Model: " << ShaderModel
			<< std::endl;

		if (pError)
		{
			std::string errMsg((char*)pError->GetBufferPointer(), pError->GetBufferSize());
			std::cout << "컴파일러 에러 메시지: \n" << errMsg << std::endl;
		}*/
		if (pError)
		{
			OutputDebugStringA((char*)pError->GetBufferPointer());
			pError->Release();
		}


	}

	SafeRelease(pError);
	return hr;

	SafeRelease(pError);
	return hr;
}

void Effect::Createbuffer_wrapped(VertexFlag type)
{
	if (type == VertexFlag::VF_POSCOL) //NOLIGHT가 맞는듯?
	{
		auto cbuffer = make_unique<cbDEFAULT>();
		cbuffer->Create(m_pDev);
		AddCB(std::move(cbuffer));
	}

	else if (type == VertexFlag::VF_POSNOR) // Light는 전역에서 관리. 후에는 Light 전용 Class에서 운용 
	{
		auto cbuffer_1 = make_unique<cbDEFAULT>();
		cbuffer_1->Create(m_pDev);
		AddCB(std::move(cbuffer_1));

		auto cbuffer_2 = make_unique<cbMATERIAL>();
		cbuffer_2->Create(m_pDev);
		AddCB(std::move(cbuffer_2));


		auto cbuffer_3 = make_unique<cbLIGHT>();
		cbuffer_3->Create(m_pDev);
		AddCB(std::move(cbuffer_3));
	}
	else if (type == VertexFlag::VF_POSCOLTEX)
	{
		auto cbuffer_1 = make_unique<cbDEFAULT>();
		cbuffer_1->Create(m_pDev);
		AddCB(std::move(cbuffer_1));
	}
	//나머지는 ANIMATION에서 처리 
	else assert(SUCCEEDED(false));

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

int Effect::CreateInputLayout(VertexFlag modelFlag, ID3DBlob* pVSCode) //helper 로 빼도 되고, 아님 여기 둬도 되미. 
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
	UINT offset = 0;

	// POSITION
	if ((modelFlag & VertexFlag::VF_POSITION) != VertexFlag::VF_NONE)
	{
		layout.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
						   0, offset, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		offset += sizeof(XMFLOAT3); // 수정: if 블록 안으로 이동
	}

	// COLOR
	if ((modelFlag & VertexFlag::VF_COLOR) != VertexFlag::VF_NONE)
	{
		layout.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,
						   0, offset, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		offset += sizeof(XMFLOAT4); // 수정: if 블록 안으로 이동
	}

	// TEXCOORD
	if ((modelFlag & VertexFlag::VF_TEXCOORD) != VertexFlag::VF_NONE)
	{
		layout.push_back({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
						   0, offset, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		offset += sizeof(XMFLOAT2); // 수정: if 블록 안으로 이동
	}

	// NORMAL
	if ((modelFlag & VertexFlag::VF_NORMAL) != VertexFlag::VF_NONE)
	{
		layout.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT,
						   0, offset, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		offset += sizeof(XMFLOAT3); // 수정: if 블록 안으로 이동
	}

	// 실제 생성
	if (layout.empty())
		return -1;

	HRESULT hr = m_pDev->CreateInputLayout(
		layout.data(), (UINT)layout.size(),
		pVSCode->GetBufferPointer(),
		pVSCode->GetBufferSize(),
		&m_pLayout
	);

	if (FAILED(hr))
		return -1;

	return 1;
}


void Effect::Apply(float dTime, SamplerIndex flag)
{
	Update();
	m_pDXDC->VSSetShader(m_pVS, nullptr, 0);
	m_pDXDC->PSSetShader(m_pPS, nullptr, 0);
	m_pDXDC->IASetInputLayout(m_pLayout);


	if (m_texture != nullptr)
	{
		m_pDXDC->PSSetShaderResources(0, 1, &m_texture);
		m_pDXDC->PSSetSamplers(0, 1, &GlobalSampler[static_cast<int>(flag)]);
	}

	for (const auto& cb : m_ConstantBuffers)
	{
		ID3D11Buffer* pCB = cb.get()->GetBuffer();
		UINT slot = cb.get()->GetRegisterSlot();
		m_pDXDC->VSSetConstantBuffers(slot, 1, &pCB);
		m_pDXDC->PSSetConstantBuffers(slot, 1, &pCB);
		//std::cout << "slot num" << slot << endl;
	}
}

void Effect::Update(float dTime)
{
	UpdateConstantBuffers();
}

int Effect::UpdateConstantBuffers()
{

	for (const auto& cb : m_ConstantBuffers)
	{
		cb->Update(m_pDXDC);
	}
	return 1;
}