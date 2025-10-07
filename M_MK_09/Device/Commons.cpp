#include "Commons.h"

DWORD AlignCBSize(DWORD size)
{
	DWORD sizeAligned = 0;
	BOOL bAligned = (size % 16) ? FALSE : TRUE;		//정렬(필요) 확인.

	if (bAligned) sizeAligned = size;
	else sizeAligned = (size / 16) * 16 + 16;		//정렬(필요) 크기 재산출.

	return sizeAligned;
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



////////////////////////////////////////////////////////////////////////////// 
//
// 상수 버퍼 생성 2 : Dynamic Constant Buffer
//
// [ 동적 버퍼 ]
// CPU 쓰기,  GPU 읽기 설정 가능. 버퍼 데이터의 잦은 변화시 사용하기에 적절한 버퍼.  
// 버퍼를 갱신할 때는 Map / UnMap 을 통해 처리합니다. 이를 위해 버퍼 생성시 
// D3D11_USAGE_DYNAMIC 설정이 필요하며, 이 플래그는 빈번한 Map 호출시의 성능문제를 최적화 시켜줍니다.
// 버퍼의 내용이 바뀌지 않는다면, 일반적인 정적버퍼 Static Buffer 를 사용하십시오.
//            
//  [주의] GPU 가 사용중인 버퍼를 접근(Map) 할 때에는 상당한 성능하락이 동반됩니다.
//  이 경우 Map 함수는 버퍼의 사용이 끝날 때까지 기다린 후 리턴됩니다.
//  단일 장면 구성시 여러번의 Map 과 Draw 가 사용될 경우에는 GPU 의 버퍼접근이 방지되며,
//  렌더링명령 Rendering Commands 가 완료된 이후에 (버퍼 포인터)가 리턴됩니다. 
//  
//  버퍼의 내용을 갱신할 때, D3D11_MAP_WRITE_DISCARD 플래그를 설정하면 
//  기존 버퍼의 데이터는 버려지며, 새로운 데이터로 교체됩니다.
//  만일 GPU 가 이전 데이터를 사용해 렌더링 중이라하더라도 충돌 없이 (이전데이터를 사용) 
//  렌더링이 완료되며 이후 이전 테이터는 제거됩니다.  
//  이를 위해 어플리케이션측의 추가적인 메모리 관리는 불필요합니다. 
//
//! \see [동적자원 사용법](https://learn.microsoft.com/en-us/windows/win32/direct3d11/how-to--use-dynamic-resources)
//! \see [Using Dynamic Buffers](https://learn.microsoft.com/en-us/windows/win32/direct3d11/how-to--use-dynamic-resources#using-dynamic-buffers)
//
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
		//ynError(hr, _T("CreateDynamicConstantBuffer : 동적 상수버퍼 생성 실패 : size=%d"), sizeAligned);
		return hr;
	}

	//외부로 전달.
	*ppCB = pCB;

	return hr;
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











// 일반적인 환경하에서 올바른 렌더링 결과를 기대한다면 아래의 조건이 동일 또는 호환되어야 합니다.
// 1.정점 버퍼 데이터.  Vertex Buffer Data
// 2.정점 구조 Vertex Format (Input Layout)
// 3.셰이더 (함수) 입력구조.  Vertex Shader (Input Layout)
// 4.셰이더 (함수) 입출력 시멘틱 (Semantics)
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



