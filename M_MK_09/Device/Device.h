#pragma once
#include "Commons.h" //좀 커지면 pch로 뺄까도 고민 
#include "GridNAxis.h"

//여기에는 DX 객체를 담아두고 싶음. RENDER 적인 부분도 여기서 
//종합 관리 하고 싶은데, 최종적인 형태는 아마 계층 구조가 더 세분화 되지
//않을까 싶긴 함. 


using namespace DirectX;
using namespace std;

class DX_Device
{
private:
	ID3D11Device* m_Device = nullptr;
	ID3D11DeviceContext* m_DXDC = nullptr;

	IDXGISwapChain* m_SwapChain = nullptr;
	ID3D11RenderTargetView* m_RTView = nullptr;

	ID3D11Texture2D* m_pDS = nullptr;					//깊이-스텐실 버퍼.
	ID3D11DepthStencilView* m_pDSView = nullptr;				//깊이-스텐실 버퍼-뷰 


private:
	unique_ptr<GridNAxis> GDNAX;

private:

	HRESULT CreateDeviceSwapChain(HWND hwnd);
	HRESULT CreateRenderTargetView();
	HRESULT CreateDepthStencil();
public:
	HRESULT DX_SetUP(HWND hwnd);
	HRESULT GridNAxis_SetUP(ID3D11Device* device);
	void SetViewPort(float widh, float ht);
	
	inline GridNAxis* GetGridFX() { return GDNAX.get(); }

	void UpdateGrid(float dTime) { GetGridFX()->GetFX()->Update(dTime); }


	void DrawGridNAxis();
	void Flip();
	void Clear();

};