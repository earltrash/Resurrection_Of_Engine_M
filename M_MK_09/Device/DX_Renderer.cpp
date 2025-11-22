#pragma once

#include "pch.h"
#include "DX_Renderer.h"
#include "GridNAxis.h"
#include "Graphics.h"
#include "State.h"
#include "Model.h"
#include "Render_Helper.h"
#include "Resourcemanager.h"
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
	std::vector<std::pair<Model*, XMMATRIX>>& Mesh_Models  = m_Render_Helper.get()->Get_Model_Vec();
	Shader* Static_Mesh_Shader = ResourceManager::Instance().GetShaderResource()->GetShader(e_Shader_Type::Static_);

	m_DXDC->VSSetShader(Static_Mesh_Shader->GetVS(), nullptr, 0);
	m_DXDC->PSSetShader(Static_Mesh_Shader->GetPS(), nullptr, 0);
	m_DXDC->IASetInputLayout(Static_Mesh_Shader->GetIL());

	for (auto& model : Mesh_Models)
	{
		SetWorldMatrix(model.second); //update / Slot Setting까지 Wrapped.
		model.first->m_Material; //Texture, cb material에 대한 처리는 나중에 하자. material class develope 필요.


		model.first->Render(m_DXDC.Get());
	}
}

void DX_Renderer::Render()
{
	Clear();
	StateSet_BeforeRender(); //State Set
	DrawGridNAxis();

	//Shader Set
	ConstantBufferApply();
	//Model Set


	StaticMeshRender();

	Flip();
}

void DX_Renderer::ConstantBufferApply() //일단 미정 
{
	std::vector<unique_ptr<IConstBuffer>>& Vec = m_Render_Helper.get()->Get_CB_Vec();

	for (const auto& cb : Vec) 
	{
		cb.get()->Update(m_DXDC.Get());
		ID3D11Buffer* pCB = cb.get()->GetBuffer();
		UINT slot = cb.get()->GetRegisterSlot();
		m_DXDC->VSSetConstantBuffers(slot, 1, &pCB);
		m_DXDC->PSSetConstantBuffers(slot, 1, &pCB);
	}
}

void DX_Renderer::SetWorldMatrix(XMMATRIX WORLD_MATRIX)
{
	m_Render_Helper->GetCB<cbDEFAULT>()->SetWorld(WORLD_MATRIX);
	m_Render_Helper->GetCB<cbDEFAULT>()->Update(m_DXDC.Get());
	ID3D11Buffer* pCB = m_Render_Helper->GetCB<cbDEFAULT>()->GetBuffer();

	m_DXDC->VSSetConstantBuffers(static_cast<int>(e_CB::CB_DEFAULT), 1, &pCB);
	m_DXDC->PSSetConstantBuffers(static_cast<int>(e_CB::CB_DEFAULT), 1, &pCB); //조건
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

	m_DXDC->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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

	Render_Helper_SetUp Set_RH;
	Set_RH.m_Device = m_Device;
	Set_RH.m_DXDC = m_DXDC;

	m_Render_Helper = make_shared<Render_Helper>();
	m_Render_Helper->Initalize(Set_RH);

	return E_NOTIMPL;
}
HRESULT DX_Renderer::GridNAxis_SetUP(ID3D11Device* Dev)
{
	HRESULT hr;
	GDNAX = new GridNAxis();
	hr = GDNAX->Set_GridNAxis( Dev);
	
	return hr;
}

