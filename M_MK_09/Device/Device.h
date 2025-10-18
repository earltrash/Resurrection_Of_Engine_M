#pragma once
#include "Commons.h" 
#include "GridNAxis.h"


extern class GridNAxis;



using namespace DirectX;
using namespace std;

class DX_Device
{
public: //일단 공부해야 하니깐 열어 버려 
	ID3D11Device* m_Device = nullptr;
	ID3D11DeviceContext* m_DXDC = nullptr;

	IDXGISwapChain* m_SwapChain = nullptr;
	ID3D11RenderTargetView* m_RTView = nullptr;

	ID3D11Texture2D* m_pDS = nullptr;					//깊이-스텐실 버퍼.
	ID3D11DepthStencilView* m_pDSView = nullptr;				//깊이-스텐실 버퍼-뷰 

	ID3D11RasterizerState* pSolidRS = nullptr;
	ID3D11DepthStencilState* pNoDepthDS = nullptr;
private:
	unique_ptr<GridNAxis> GDNAX;

private:

	HRESULT CreateDeviceSwapChain(HWND hwnd);
	HRESULT CreateRenderTargetView();
	HRESULT CreateDepthStencil();
	HRESULT CreateSampler();
public:
	HRESULT DX_SetUP(HWND hwnd);
	HRESULT GridNAxis_SetUP(ID3D11Device* device);
	void SetViewPort(float widh, float ht);
	
	GridNAxis* GetGridFX();

	void UpdateGrid(float dTime);


	void DrawGridNAxis();
	void Flip();
	void Clear();

};