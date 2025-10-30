#pragma once
#include "Commons.h" 

using Microsoft::WRL::ComPtr;

struct Graphics_Set
{
	float width, height; //swapchain
	HWND hwnd; //devicw
};


class Graphics
{
public:
	Graphics() = default;
	~Graphics() = default;



public:
	//swapchain //height width
	//device //hwnd
	//context
	//rendertarget

	void SetUp(Graphics_Set set);


	ComPtr<ID3D11Device> GetDevice() { return m_pDevice; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return m_pDeviceContext; }
	ComPtr<IDXGISwapChain> GetSwapChain() { return m_pSwapChain; }
	ComPtr<ID3D11RenderTargetView> GetRenderTargetView() { return m_pRenderTargetView; }
	ComPtr<ID3D11DepthStencilView> GetDepthStencilView() { return m_pDepthStencilView; }
	D3D11_VIEWPORT GetViewport() { return m_Viewport; }



private:
	void createSwapChain();
	void createRenderTargetView();
	void createStencilAndDepth();
	void setViewPort();


private:
	ComPtr<ID3D11Device> m_pDevice;
	ComPtr<ID3D11DeviceContext> m_pDeviceContext = nullptr; // 즉시 디바이스 컨텍스트
	ComPtr<IDXGISwapChain> m_pSwapChain = nullptr;
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView = nullptr;
	ComPtr<ID3D11RenderTargetView> m_pRenderTargetView = nullptr;
	D3D11_VIEWPORT m_Viewport = {};


private:
	HWND m_hwnd;
	float m_height;
	float m_width;
};

