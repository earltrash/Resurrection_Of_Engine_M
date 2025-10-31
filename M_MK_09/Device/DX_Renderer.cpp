#pragma once

#include "pch.h"


#include "DX_Renderer.h"
#include "GridNAxis.h"
#include "Graphics.h"
#include "State.h"
#include "Model.h"

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


//쉐이더 코드를 하나로 통일할 거기 때문에.

void DX_Renderer::StaticMeshRender()
{

	//쉐이더 세팅
	//상수버퍼 -> 특히 월드 행렬.
	//Layout 정렬하기 .





	for (const auto& model : m_BeDrawnModel)
	{
		//


		model->Render(m_DXDC.Get());
	}
}

void DX_Renderer::Render()
{
	Clear();
	StateSet_BeforeRender(); //State Set
	DrawGridNAxis();

	//Shader Set

	//Model Set


	StaticMeshRender();

	Flip();
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

	m_DXDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

}

void DX_Renderer::SetGridNAxis(XMMATRIX view)
{
	GDNAX->GetFX()->SetView(view);
	GDNAX->GetFX()->Update();
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

