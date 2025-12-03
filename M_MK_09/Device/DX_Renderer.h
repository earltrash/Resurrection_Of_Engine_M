#pragma once
#include <list>
#include <vector>
#include <memory>                 
#include <d3d11.h>                
#include <DirectXMath.h>          
#include <wrl/client.h>           
#include "Singleton.h"

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
	void StateSet_BeforeRender();
	Render_Helper* GetRH();
	Microsoft::WRL::ComPtr<ID3D11SamplerState> Get_SamplerState(); ///얘는 나중에 빠질 예정임.
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
public:
	Microsoft::WRL::ComPtr<ID3D11Device> m_Device = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DXDC = nullptr;
};