#include "Commons.h"


ID3D11SamplerState** GlobalSampler = nullptr;

float StrideFromFlag(VertexFlag Flag) // 근데 그냥 stride는 vertex 단위로 받을 거라. 얘는 아마 폐지 되지 않을까 싶긴 해. 
{
	size_t stride = 0;
	if ((Flag & VertexFlag::VF_POSITION) != VertexFlag::VF_NONE) stride += sizeof(XMFLOAT3);
	if ((Flag & VertexFlag::VF_NORMAL) != VertexFlag::VF_NONE)   stride += sizeof(XMFLOAT3);
	if ((Flag & VertexFlag::VF_COLOR) != VertexFlag::VF_NONE)    stride += sizeof(XMFLOAT4);
	if ((Flag & VertexFlag::VF_TEXCOORD) != VertexFlag::VF_NONE) stride += sizeof(XMFLOAT2);
	return stride;
}

DWORD AlignCBSize(DWORD size)
{
	DWORD sizeAligned = 0;
	BOOL bAligned = (size % 16) ? FALSE : TRUE;		//정렬(필요) 확인.

	if (bAligned) sizeAligned = size;
	else sizeAligned = (size / 16) * 16 + 16;		//정렬(필요) 크기 재산출.

	return sizeAligned;
}

#pragma region CreateFunc
HRESULT CreateDynamicConstantBuffer(ID3D11Device* pDev, UINT size, ID3D11Buffer** ppCB)
{
	HRESULT hr = S_OK;
	ID3D11Buffer* pCB = nullptr;

	//정렬된 버퍼 크기 계산 
	DWORD sizeAligned = AlignCBSize(size);

	//상수 버퍼 정보 설정.
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;				//동적 정점버퍼 설정.
	bd.ByteWidth = sizeAligned;						//버퍼 크기 : 128비트 정렬 추가.
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;				//CPU 접근 설정. 

	/*//서브리소스 설정.
	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = pData;										//상수 데이터 설정.
	sd.SysMemPitch = 0;
	sd.SysMemSlicePitch = 0;
	*/

	//상수 버퍼 생성.
	hr = pDev->CreateBuffer(&bd, nullptr, &pCB);
	if (FAILED(hr))
	{
		std::cout << "상수 버퍼 생성 실패" << std::endl;
		return hr;
	}

	//외부로 전달.
	*ppCB = pCB;

	return hr;
}
int CreateVertexBuffer(ID3D11Device* pDev, LPVOID pData, UINT size, ID3D11Buffer** ppVB)
{
	HRESULT hr = S_OK;

	// 정점 버퍼 Vertex Buffer 정보 구성 
	D3D11_BUFFER_DESC bd = {};
	//ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;			//버퍼 사용방식
	bd.ByteWidth = size;							//버퍼 크기 (바이트)
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//버퍼 용도 : "정점 버퍼" 
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.pSysMem = pData;									//버퍼에 저장될 데이터 : "정점들"..

	//정점 버퍼 생성.
	ID3D11Buffer* pVB = nullptr;
	hr = pDev->CreateBuffer(&bd, &rd, &pVB);
	if (FAILED(hr))
	{
		std::cout << "정점 버퍼 생성 오류" << std::endl;;

		return hr;
	}


	*ppVB = pVB;
	return S_OK;
}
int CreateConstantBuffer(ID3D11Device* pDev, UINT size, ID3D11Buffer** ppCB)
{
	HRESULT hr = S_OK;

	//정렬된 버퍼 크기 계산 
	DWORD sizeAligned = AlignCBSize(size);

	//상수 버퍼 정보 설정.
	D3D11_BUFFER_DESC bd = {};
	//ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;				//버퍼 사용방식
	//bd.Usage	 = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeAligned;						//버퍼 크기 : 128비트 정렬 추가.
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//버퍼 용도 : "상수 버퍼" 
	//bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//상수 버퍼 생성.
	ID3D11Buffer* pCB = nullptr;
	hr = pDev->CreateBuffer(&bd, nullptr, &pCB);
	if (FAILED(hr))
	{
		//ynError(hr, _T("[실패] 상수 버퍼 생성 실패 : size=%d"), sizeAligned);
	}

	//외부로 리턴.
	*ppCB = pCB;

	return S_OK;
}
HRESULT CreateDynamicConstantBuffer(ID3D11Device* pDev, UINT size, LPVOID pData, ID3D11Buffer** ppCB)
{
	HRESULT hr = S_OK;
	ID3D11Buffer* pCB = nullptr;

	//정렬된 버퍼 크기 계산 
	DWORD sizeAligned = AlignCBSize(size);

	//상수 버퍼 정보 설정.
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;				//동적 정점버퍼 설정.
	bd.ByteWidth = sizeAligned;						//버퍼 크기 : 128비트 정렬 추가.
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;				//CPU 접근 설정.

	//서브리소스 설정.
	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = pData;							//상수 데이터 설정.
	sd.SysMemPitch = 0;
	sd.SysMemSlicePitch = 0;

	//상수 버퍼 생성.
	hr = pDev->CreateBuffer(&bd, &sd, &pCB);
	if (FAILED(hr))
	{
		std::cout << "상수 버퍼 생성 오류" << std::endl;

		return hr;
	}

	//외부로 전달.
	*ppCB = pCB;

	return hr;
}
int CreateInputLayout(ID3D11Device* pDev, D3D11_INPUT_ELEMENT_DESC* ed, DWORD num, ID3DBlob* pVSCode, ID3D11InputLayout** ppLayout)
{
	HRESULT hr = S_OK;

	ID3D11InputLayout* pLayout = nullptr;
	hr = pDev->CreateInputLayout(ed, num, pVSCode->GetBufferPointer(), pVSCode->GetBufferSize(), &pLayout);
	if (FAILED(hr))
	{
		std::cout << "'레이아웃 생성 오류" << std::endl;
		return hr;
	}
	*ppLayout = pLayout;

	return S_OK;
}
HRESULT UpdateDynamicBuffer(ID3D11DeviceContext* pDXDC, ID3D11Resource* pBuff, LPVOID pData, UINT size)
{
	HRESULT hr = S_OK;

	//정렬된 버퍼 크기 계산 
	DWORD sizeAligned = AlignCBSize(size);


	//버퍼 자원 정보 설정.
	D3D11_MAPPED_SUBRESOURCE mr = {};
	//ZeroMemory(&mr, sizeof(mr));
	mr.pData = nullptr;							//리소스 버퍼 포인터. Map 을 통해 획득됨. 

	//버퍼 버퍼 접근
	hr = pDXDC->Map(pBuff,						//버퍼 잠금 "Locked"
		0,
		D3D11_MAP_WRITE_DISCARD,	//CPU 접근 설정 
		0,
		&mr							//버퍼 포인터 얻기. 
	);
	if (FAILED(hr))
	{
		std::cout << "상수 버퍼 업데이트 실패했는뎁쇼" << std::endl;
		return hr;
	}

	memcpy(mr.pData, pData, size);				//버퍼 갱신.
	//memcpy(mr.pData, pData, sizeAligned);		//버퍼 갱신 (+정렬된 크기)
	pDXDC->Unmap(pBuff, 0);						//버퍼 닫기 : 감금해제 "Unlocked"

	return hr;
}
void GlobalSamplerCreate(ID3D11Device*& device)
{
	GlobalSampler = new ID3D11SamplerState * [static_cast<int>(SamplerIndex::SamplerMax)];

	D3D11_SAMPLER_DESC sd = {};
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.Filter = D3D11_FILTER_ANISOTROPIC;

	sd.MaxAnisotropy = 1;
	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;
	sd.MipLODBias = 0;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sd.BorderColor[0] = 1;
	sd.BorderColor[1] = 1;
	sd.BorderColor[2] = 1;
	sd.BorderColor[3] = 1;

	HRESULT hr = device->CreateSamplerState(&sd, &GlobalSampler[static_cast<int>(SamplerIndex::DEFAULT)]);

	if (FAILED(hr))
	{
		std::cout << "텍스쳐 샘플러 못 만듦" << std::endl;
		
	}

	sd = {};
	sd.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
	sd.Filter = D3D11_FILTER_ANISOTROPIC;

	sd.MaxAnisotropy = 1;
	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;
	sd.MipLODBias = 0;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sd.BorderColor[0] = 1;
	sd.BorderColor[1] = 1;
	sd.BorderColor[2] = 1;
	sd.BorderColor[3] = 1;

	 hr = device->CreateSamplerState(&sd, &GlobalSampler[static_cast<int>(SamplerIndex::MIRROR)]);

	if (FAILED(hr))
	{
		std::cout << "텍스쳐 샘플러 못 만듦" << std::endl;

	}


	sd = {};
	sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.Filter = D3D11_FILTER_ANISOTROPIC;

	sd.MaxAnisotropy = 1;
	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;
	sd.MipLODBias = 0;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sd.BorderColor[0] = 1;
	sd.BorderColor[1] = 1;
	sd.BorderColor[2] = 1;
	sd.BorderColor[3] = 1;

	 hr = device->CreateSamplerState(&sd, &GlobalSampler[static_cast<int>(SamplerIndex::CLAMP)]);

	if (FAILED(hr))
	{
		std::cout << "텍스쳐 샘플러 못 만듦" << std::endl;

	}


	sd = {};
	sd.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	sd.Filter = D3D11_FILTER_ANISOTROPIC;

	sd.MaxAnisotropy = 1;
	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;
	sd.MipLODBias = 0;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sd.BorderColor[0] = 1;
	sd.BorderColor[1] = 1;
	sd.BorderColor[2] = 1;
	sd.BorderColor[3] = 1;

	 hr = device->CreateSamplerState(&sd, &GlobalSampler[static_cast<int>(SamplerIndex::BORDER)]);

	if (FAILED(hr))
	{
		std::cout << "텍스쳐 샘플러 못 만듦" << std::endl;

	}

	sd = {};
	sd.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
	sd.Filter = D3D11_FILTER_ANISOTROPIC;

	sd.MaxAnisotropy = 1;
	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;
	sd.MipLODBias = 0;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sd.BorderColor[0] = 1;
	sd.BorderColor[1] = 1;
	sd.BorderColor[2] = 1;
	sd.BorderColor[3] = 1;

	hr = device->CreateSamplerState(&sd, &GlobalSampler[static_cast<int>(SamplerIndex::MIRRORONCE)]);

	if (FAILED(hr))
	{
		std::cout << "텍스쳐 샘플러 못 만듦" << std::endl;

	}


	
	
}
#pragma endregion

