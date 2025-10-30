#include "Graphics.h"

void Graphics::SetUp(Graphics_Set set)
{
	m_hwnd = set.hwnd;
	m_height = set.height;
	m_width = set.width;
	
	createSwapChain();
	createStencilAndDepth();
	setViewPort();
	createRenderTargetView();
}

void Graphics::createSwapChain()
{
	DXGI_SWAP_CHAIN_DESC sd = {};

	sd.Windowed = true;						           
	sd.OutputWindow = m_hwnd;							
	sd.BufferCount = 1;									
	sd.BufferDesc.Width = m_width;						
	sd.BufferDesc.Height = m_height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		
	sd.BufferDesc.RefreshRate.Numerator = false ? 60 : 0;	
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.SampleDesc.Count = 1;								
	sd.SampleDesc.Quality = 0;

	D3D_FEATURE_LEVEL featureLevels[] = {
	   D3D_FEATURE_LEVEL_11_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);


	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		featureLevels,
		numFeatureLevels,
		D3D11_SDK_VERSION,
		&sd,
		&m_pSwapChain,
		&m_pDevice,
		NULL,
		&m_pDeviceContext);

}



void Graphics::createRenderTargetView()
{
	ID3D11Texture2D* BackBuffer;
	 m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&BackBuffer));

	m_pDevice->CreateRenderTargetView(BackBuffer, nullptr, &m_pRenderTargetView);

	::SafeRelease(BackBuffer);

	
}


//¿¬±¸.
void Graphics::createStencilAndDepth()
{
	HRESULT hr = S_OK;

	D3D11_TEXTURE2D_DESC   td = {};
	td.Width = m_width;
	td.Height = m_height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D32_FLOAT;		  
	td.SampleDesc.Count = 1;					
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;	
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;

	ID3D11Texture2D* pDS = NULL;						 
	hr = m_pDevice->CreateTexture2D(&td, NULL, &pDS);
	D3D11_DEPTH_STENCIL_VIEW_DESC  dd = {};
	dd.Format = td.Format;
	dd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;		
	dd.Texture2D.MipSlice = 0;

	//±íÀÌ-½ºÅÙ½Ç ¹öÆÛ ºä »ý¼º.
	hr = m_pDevice->CreateDepthStencilView(pDS, &dd, &m_pDepthStencilView);
	
}


void Graphics::setViewPort()
{
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width =  (FLOAT) m_width;
	vp.Height = (FLOAT) m_height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_pDeviceContext->RSSetViewports(1, &vp);
}
