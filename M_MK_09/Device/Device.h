#pragma once
#include "Commons.h" 
using Microsoft::WRL::ComPtr;


extern class GridNAxis;
class Graphics;
class State;

//Renderer의 역할을 분리하고자 
// Render시의 상태
// 생성 시에 필요하거나, 렌더링의 근본적으로 필요한 객체들을 해당 클래스로 관리.
//얘네는 포인터


//Pipe line에서 설정하는 값들.
//Sampler BlendState DepthStencilState RasterizerState
//COMPTR로 



//얘는 Engine에 존재하는 ResourceManager -> Mesh Data랑 연결돼서 Buffer 생성 같은 경우. (아마 Graphics가 처리할 거 같긴 한데) Engine이 DX를 들고 있으니
//Engine에서 Device 빌려주는 거 그 이상은 사용 안 할듯.
//나중에 Class를 Renderer로 수정하면서 역할 자체는 Engine에서 그려야 하는 정보를 받아서 Render하는 식으로 처리.

using namespace DirectX;

//너는 이제부터 Core로 Singleton으로 가져올 거임.
class DX_Renderer
{
	private:
		DX_Renderer() = default;
		~DX_Renderer() = default;




public:
	HRESULT DX_SetUP(HWND hwnd, float width, float height);
	HRESULT GridNAxis_SetUP(ID3D11Device* device);
	void StateSet_BeforeRender();
	void SetGridNAxis(XMMATRIX view);

	static DX_Renderer Get_Instance();

	GridNAxis* GetGridFX();
	
	ComPtr<ID3D11SamplerState> Get_SamplerState(); ///얘는 나중에 빠질 예정임.

	void UpdateGrid(float dTime);
	void DrawGridNAxis();
	void Flip();
	void Clear();
private:
	std::shared_ptr<State> m_DxState;
	std::shared_ptr<Graphics> m_DxGraphics;
	GridNAxis* GDNAX; //디버깅이긴 한데, 

public:
	ComPtr<ID3D11Device> m_Device = nullptr;
	ComPtr<ID3D11DeviceContext> m_DXDC = nullptr;

};