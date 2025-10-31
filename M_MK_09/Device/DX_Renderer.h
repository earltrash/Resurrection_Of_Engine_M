#pragma once
#include <list>
#include <memory>                 
#include <d3d11.h>                
#include <DirectXMath.h>          
#include <wrl/client.h>           

using namespace DirectX;
using Microsoft::WRL::ComPtr; 



extern class GridNAxis;
class Graphics;
class State;
class Model;
class Shader;


using namespace DirectX;

//�ʴ� �������� Core�� Singleton���� ������ ����.
class DX_Renderer
{
public:
		DX_Renderer() = default;
		~DX_Renderer() = default;
public:


	HRESULT DX_SetUP(HWND hwnd, float width, float height);
	HRESULT GridNAxis_SetUP(ID3D11Device* device);
	void StateSet_BeforeRender();
	void SetGridNAxis(XMMATRIX view);
	
	GridNAxis* GetGridFX();
	ComPtr<ID3D11SamplerState> Get_SamplerState(); ///��� ���߿� ���� ������.
	void UpdateGrid(float dTime);
	void DrawGridNAxis();
	void Flip();
	void Clear();


	void StaticMeshRender();
	void LoadModels(Model* model) { m_BeDrawnModel.push_back(model); }
	void Render();
private:
	std::list<Model*> m_BeDrawnModel;



private:
	std::shared_ptr<State> m_DxState;
	std::shared_ptr<Graphics> m_DxGraphics;
	std::shared_ptr<Shader> m_DxShader; // -> Layout & Shader Code & ConstBuffer;

	GridNAxis* GDNAX; //������̱� �ѵ�, 
public:
	ComPtr<ID3D11Device> m_Device = nullptr;
	ComPtr<ID3D11DeviceContext> m_DXDC = nullptr;
};