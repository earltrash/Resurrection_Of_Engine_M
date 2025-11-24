#pragma once
#include <list>
#include <vector>
#include <memory>                 
#include <d3d11.h>                
#include <DirectXMath.h>          
#include <wrl/client.h>           
#include "Singleton.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr; 



extern class GridNAxis;
class Graphics;
class State;
class Render_Helper;



using namespace DirectX;

//너는 이제부터 Core로 Singleton으로 가져올 거임. //일단 대기 

class DX_Renderer : public Singleton<DX_Renderer>
{
private:
		 DX_Renderer() = default;
		~DX_Renderer() = default;
public:
	friend class Singleton;



	HRESULT DX_SetUP(HWND hwnd, float width, float height);
	HRESULT GridNAxis_SetUP(ID3D11Device* device);
	void StateSet_BeforeRender();
	void SetGridNAxis(XMMATRIX view);
	Render_Helper* GetRH();
	GridNAxis* GetGridFX();
	ComPtr<ID3D11SamplerState> Get_SamplerState(); ///얘는 나중에 빠질 예정임.
	void UpdateGrid(float dTime);
	void DrawGridNAxis();
	void Flip();
	void Clear();
	void StaticMeshRender();
	void Render();
	void ConstantBufferApply();
	void SetWorldMatrix(XMMATRIX WORLD_MATRIX); //render_helper_Wrapper_function

private:
	//Unique로 바꿀 생각 중 -> device를 resource에서 가져오는 경우가 흔해서, 
	std::shared_ptr<State> m_DxState;
	std::shared_ptr<Graphics> m_DxGraphics;
	std::shared_ptr<Render_Helper> m_Render_Helper;

	GridNAxis* GDNAX; //디버깅이긴 한데, 

public:
	ComPtr<ID3D11Device> m_Device = nullptr;
	ComPtr<ID3D11DeviceContext> m_DXDC = nullptr;
};