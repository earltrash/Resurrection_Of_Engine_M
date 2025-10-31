#pragma once
#include "Commons.h" 
using Microsoft::WRL::ComPtr;


extern class GridNAxis;
class Graphics;
class State;

//Renderer�� ������ �и��ϰ��� 
// Render���� ����
// ���� �ÿ� �ʿ��ϰų�, �������� �ٺ������� �ʿ��� ��ü���� �ش� Ŭ������ ����.
//��״� ������


//Pipe line���� �����ϴ� ����.
//Sampler BlendState DepthStencilState RasterizerState
//COMPTR�� 



//��� Engine�� �����ϴ� ResourceManager -> Mesh Data�� ����ż� Buffer ���� ���� ���. (�Ƹ� Graphics�� ó���� �� ���� �ѵ�) Engine�� DX�� ��� ������
//Engine���� Device �����ִ� �� �� �̻��� ��� �� �ҵ�.
//���߿� Class�� Renderer�� �����ϸ鼭 ���� ��ü�� Engine���� �׷��� �ϴ� ������ �޾Ƽ� Render�ϴ� ������ ó��.

using namespace DirectX;

//�ʴ� �������� Core�� Singleton���� ������ ����.
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
	
	ComPtr<ID3D11SamplerState> Get_SamplerState(); ///��� ���߿� ���� ������.

	void UpdateGrid(float dTime);
	void DrawGridNAxis();
	void Flip();
	void Clear();
private:
	std::shared_ptr<State> m_DxState;
	std::shared_ptr<Graphics> m_DxGraphics;
	GridNAxis* GDNAX; //������̱� �ѵ�, 

public:
	ComPtr<ID3D11Device> m_Device = nullptr;
	ComPtr<ID3D11DeviceContext> m_DXDC = nullptr;

};