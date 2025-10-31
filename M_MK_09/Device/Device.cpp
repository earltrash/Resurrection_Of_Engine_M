#include "Device.h"
#include "GridNAxis.h"
#include "Graphics.h"
#include "State.h"


//Graphics로 대체시킬 예정 삭제 예정 


GridNAxis* DX_Renderer::GetGridFX()
{
	 return GDNAX; 
}

void DX_Renderer::UpdateGrid(float dTime)
{ 
	 (GetGridFX()->GetFX()) ->Update(dTime); 
}

void DX_Renderer::DrawGridNAxis()
{
	GDNAX->Draw();
}

ComPtr<ID3D11SamplerState> DX_Renderer::Get_SamplerState()
{
	return m_DxState->Get_Sampler();
}
void DX_Renderer::Flip()
{
	m_DxGraphics->GetSwapChain()->Present(0, 0);

}
void DX_Renderer::Clear()
{
	const FLOAT bgColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_DxGraphics->GetDeviceContext()->ClearRenderTargetView(m_DxGraphics->GetRenderTargetView().Get(), bgColor);
	m_DxGraphics->GetDeviceContext()->ClearDepthStencilView(m_DxGraphics->GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH, 1, 0);

}

void DX_Renderer::StateSet_BeforeRender()
{
	
	m_DXDC->RSSetState(m_DxState->Get_Rasterize().Get());
	m_DXDC->OMSetDepthStencilState(m_DxState->Get_DepthStencil().Get(), 0);

	m_DXDC->OMSetRenderTargets(
		1,
		m_DxGraphics->GetRenderTargetView().GetAddressOf(),
		m_DxGraphics->GetDepthStencilView().Get()          
	);

	

}

void DX_Renderer::SetGridNAxis(XMMATRIX view)
{
	GDNAX->GetFX()->SetView(view);
	GDNAX->GetFX()->Update();
}

DX_Renderer DX_Renderer::Get_Instance()
{
	static DX_Renderer instance;

	return instance;
}


HRESULT DX_Renderer::DX_SetUP(HWND hwnd, float width, float height)
{
	m_DxGraphics = std::make_shared<Graphics>();
	Graphics_Set Set_G;
	Set_G.hwnd = hwnd;
	Set_G.width = width;
	Set_G.height = height;

	m_DxGraphics->SetUp(Set_G);

	m_Device = m_DxGraphics->GetDevice();
	m_DXDC = m_DxGraphics->GetDeviceContext();

	m_DxState = std::make_shared<State>();
	State_Set Set_S;
	Set_S.Device = m_Device;
	Set_S.DeviceContext = m_DXDC;

	m_DxState->Set_Up(Set_S);



	return E_NOTIMPL;
}
HRESULT DX_Renderer::GridNAxis_SetUP(ID3D11Device* Dev)
{
	HRESULT hr;
	GDNAX = new GridNAxis();
	hr = GDNAX->Set_GridNAxis( Dev);
	
	return hr;
}

