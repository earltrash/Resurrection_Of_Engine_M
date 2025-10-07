#pragma once
#include "Commons.h" //�� Ŀ���� pch�� ��� ��� 
#include "GridNAxis.h"

//���⿡�� DX ��ü�� ��Ƶΰ� ����. RENDER ���� �κе� ���⼭ 
//���� ���� �ϰ� ������, �������� ���´� �Ƹ� ���� ������ �� ����ȭ ����
//������ �ͱ� ��. 


using namespace DirectX;
using namespace std;

class DX_Device
{
private:
	ID3D11Device* m_Device = nullptr;
	ID3D11DeviceContext* m_DXDC = nullptr;

	IDXGISwapChain* m_SwapChain = nullptr;
	ID3D11RenderTargetView* m_RTView = nullptr;

	ID3D11Texture2D* m_pDS = nullptr;					//����-���ٽ� ����.
	ID3D11DepthStencilView* m_pDSView = nullptr;				//����-���ٽ� ����-�� 


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