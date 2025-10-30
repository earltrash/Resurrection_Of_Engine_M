#pragma once

#include "Commons.h"



using Microsoft::WRL::ComPtr;
struct State_Set
{
	ComPtr<ID3D11Device> Device = nullptr;
	ComPtr<ID3D11DeviceContext> DeviceContext = nullptr;
};




class State
{
public: 
	State() = default;
	~State() = default;

	void Set_Up(State_Set);
	void Set_Rasterizer();
	void Set_DepthStencil();
	void Set_Sampler();
	void Set_BlendState();




	//일단 기본적인 것만
	ComPtr<ID3D11RasterizerState> Get_Rasterize() { return  m_pSolidRS; }
	ComPtr<ID3D11DepthStencilState> Get_DepthStencil() { return  m_pDepth; }
	ComPtr<ID3D11SamplerState> Get_Sampler() { return  m_pSampler_; }
	ComPtr<ID3D11BlendState> Get_BlendState() { return  m_pBlendState; }

private:
	ComPtr<ID3D11RasterizerState> m_pSolidRS = nullptr;
	ComPtr<ID3D11DepthStencilState> m_pDepth = nullptr;
	ComPtr<ID3D11SamplerState> m_pSampler_ = nullptr;
	ComPtr<ID3D11BlendState> m_pBlendState = nullptr;

	ComPtr<ID3D11Device> m_pDevice = nullptr;
	ComPtr<ID3D11DeviceContext> m_pDeviceContext = nullptr;


};

