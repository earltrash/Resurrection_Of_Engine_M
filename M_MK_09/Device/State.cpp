#include "pch.h"
#include "State.h"



void State::Set_Up(State_Set Set)
{

	m_pDevice = Set.Device;
	m_pDeviceContext = Set.DeviceContext;

	
	Set_DepthStencil();
	Set_BlendState();
	Set_Rasterizer();
	Set_BlendState();
	Set_Sampler();
}

void State::Set_Rasterizer()
{
	D3D11_RASTERIZER_DESC rsDesc = {};
	rsDesc.FillMode = D3D11_FILL_SOLID;
	rsDesc.FrontCounterClockwise = true;
	rsDesc.DepthBias = 0;
	rsDesc.DepthBiasClamp = 0;
	rsDesc.SlopeScaledDepthBias = 0;
	rsDesc.DepthClipEnable = true;
	rsDesc.ScissorEnable = false;
	rsDesc.MultisampleEnable = true;
	rsDesc.AntialiasedLineEnable = true;
	rsDesc.CullMode = D3D11_CULL_NONE;

	m_pDevice->CreateRasterizerState(&rsDesc, &m_pSolidRS);
}

void State::Set_DepthStencil()
{
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};

	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	m_pDevice->CreateDepthStencilState(&dsDesc, &m_pDepth);

	
}

void State::Set_Sampler()
{
	D3D11_SAMPLER_DESC sd = {};
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	sd.MaxAnisotropy = 1;
	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;
	sd.MipLODBias = 0;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sd.BorderColor[0] = 1;
	sd.BorderColor[1] = 1;
	sd.BorderColor[2] = 1;
	sd.BorderColor[3] = 1;

	m_pDevice->CreateSamplerState(&sd, &m_pSampler_);
	

}

void State::Set_BlendState()
{
}
