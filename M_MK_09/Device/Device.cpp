#include "Device.h"

HRESULT DX_Device::CreateDeviceSwapChain(HWND hwnd)
{
	HRESULT hr = false;

	DXGI_SWAP_CHAIN_DESC sd = {};

	sd.Windowed = true;						            //전체화면 사용 여부
	sd.OutputWindow = hwnd;								//출력할 윈도우 핸들.
	sd.BufferCount = 1;									//백버퍼 개수.
	sd.BufferDesc.Width =  1920;						//해상도 결정.(백버퍼 크기)
	sd.BufferDesc.Height = 1080;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;						//백버퍼 색상규격 (A8R8G8B8) 창모드에서는 생략 가능 
	sd.BufferDesc.RefreshRate.Numerator = false ? 60 : 0;	//버퍼 갱신율.(수직동기화 VSync 활성화시 표준갱신율 적용 : 60hz)
	//sd.BufferDesc.RefreshRate.Numerator = 0;					//버퍼 갱신율.(수직동기화 VSync Off)
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//용도 설정: '렌더타겟' 
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	//sd.Flags = 0;
	sd.SampleDesc.Count = 1;								//AA 설정 "MSAA"
	sd.SampleDesc.Quality = 0;

	D3D_FEATURE_LEVEL featureLevels[] = {
	   D3D_FEATURE_LEVEL_11_0,
	 //  D3D_FEATURE_LEVEL_10_1,
	 //  D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);


	hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		featureLevels,     
		numFeatureLevels,  
		D3D11_SDK_VERSION,
		&sd,
		&m_SwapChain,
		&m_Device,
		NULL,
		&m_DXDC
	);

	if (FAILED(hr))
	{
		std::cout << "❌ D3D11CreateDeviceAndSwapChain 실패! hr = 0x"
			<< std::hex << hr << std::dec << std::endl;

		if (hr == DXGI_ERROR_UNSUPPORTED)
			std::cout << " GPU가 요청한 Feature Level을 지원하지 않습니다." << std::endl;
		else if (hr == E_INVALIDARG)
			std::cout << " DXGI_SWAP_CHAIN_DESC 설정값이 잘못되었습니다." << std::endl;
		else if (hr == E_OUTOFMEMORY)
			std::cout << " 메모리가 부족합니다." << std::endl;
	}
	else
	{
		std::cout << " Device & SwapChain 생성 성공!" << std::endl;
	}


	return hr;
}

HRESULT DX_Device::CreateRenderTargetView()
{
	HRESULT hr;
	ID3D11Texture2D* BackBuffer;
	hr = m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&BackBuffer));
	if (FAILED(hr)) return hr; 

		hr = m_Device->CreateRenderTargetView(BackBuffer, nullptr, &m_RTView);
		if (FAILED(hr)) return hr;

		::SafeRelease(BackBuffer); 

	return hr;
}

HRESULT DX_Device::CreateDepthStencil()
{
	HRESULT hr = S_OK;

	//깊이/스텐실 버퍼용 정보 구성.
	D3D11_TEXTURE2D_DESC   td = {};
	//ZeroMemory(&td, sizeof(td));
	td.Width = 1920;
	td.Height =1080;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D32_FLOAT;		// 32BIT. 깊이 버퍼.
	td.SampleDesc.Count = 1;						// AA 설정 "MSAA x4"
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;	// 깊이-스텐실 버퍼용으로 설정.
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;
	// 깊이 버퍼 생성.
	//ID3D11Texture2D* pDS = NULL;						 
	hr = m_Device->CreateTexture2D(&td, NULL, &m_pDS);
	if (FAILED(hr))
	{
		std::cout << "깊이/스텐실 전용 텍스쳐 생성 오류" << endl;
		return hr;
	}


	// 깊이-스텐실버퍼용 리소스 뷰 정보 설정. 
	D3D11_DEPTH_STENCIL_VIEW_DESC  dd = {};
	//ZeroMemory(&dd, sizeof(dd));
	dd.Format = td.Format;
	dd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;		//AA 없음.
	//dd.ViewDimension  = D3D11_DSV_DIMENSION_TEXTURE2DMS;	//+AA 설정 "MSAA"
	dd.Texture2D.MipSlice = 0;

	//깊이-스텐실 버퍼 뷰 생성.
	hr = m_Device->CreateDepthStencilView(m_pDS, &dd, &m_pDSView);
	if (FAILED(hr))
	{
		std::cout << "깊이/스텐실뷰 생성 실패." << endl;
		return hr;
	}
	return hr;
}

void DX_Device::SetViewPort(float width, float height)
{
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = (FLOAT)width; 
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_DXDC->RSSetViewports(1, &vp);
}

GridNAxis* DX_Device::GetGridFX()
{
	 return GDNAX.get(); 
}

void DX_Device::UpdateGrid(float dTime)
{ 
	 (GetGridFX()->GetFX()) ->Update(dTime); 
}

void DX_Device::DrawGridNAxis()
{
	GDNAX->Draw();
}

void DX_Device::Flip()
{
	m_SwapChain->Present(0, 0);

}
void DX_Device::Clear()
{
	const FLOAT bgColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_DXDC->ClearRenderTargetView(m_RTView, bgColor);

	// 깊이 스텐실 뷰 지우기
	m_DXDC->ClearDepthStencilView(m_pDSView, D3D11_CLEAR_DEPTH, 1, 0);
}

HRESULT DX_Device::DX_SetUP(HWND hwnd)
{
	HRESULT hr;
	hr = CreateDeviceSwapChain(hwnd);
	if (FAILED(hr)) assert(SUCCEEDED(hr));

	hr = CreateDepthStencil();
	if (FAILED(hr)) assert(SUCCEEDED(hr));

	hr = CreateRenderTargetView();
	if (FAILED(hr)) assert(SUCCEEDED(hr));

	m_DXDC->OMSetRenderTargets(1, &m_RTView, m_pDSView);


	hr = GridNAxis_SetUP(m_Device);
	if (FAILED(hr)) assert(SUCCEEDED(hr));

	
	return hr;
}

HRESULT DX_Device::GridNAxis_SetUP(ID3D11Device* Dev)
{
	HRESULT hr;
	GDNAX = make_unique<GridNAxis>();
	hr = GDNAX->Set_GridNAxis( Dev);
	
	return hr;
}