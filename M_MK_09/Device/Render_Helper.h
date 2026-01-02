#pragma once
// 상수 버퍼, RenderComponent를 통해 받아온 worldmatrix랑 model data를 vector로 갖을 클래스,
// 그리기 단계에 필요한, 특히 동적으로 변화하는 데이터를 해당 클래스에서 관리하도록 함.
#include <wrl/client.h>
#include "ConstBuffer.h"
#include <SimpleMath.h>

using namespace std;

class Model;


struct Render_Helper_SetUp
{
	Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DXDC;
};



//얘는 DX_Render대신 Game에 근접한 유닛이므로, 얘로 DX와 ENGINE 정확히는 CLIENT를 연결함. 
class Render_Helper
{
public:
	Render_Helper() = default;
	~Render_Helper() = default;

	void Initalize(Render_Helper_SetUp SetUp);
	void LoadModels(std::pair <Model*, Matrix> Render_Data);

	std::vector<pair<Model*, Matrix>>& Get_Model_Vec();
	std::vector<unique_ptr<IConstBuffer>>& Get_CB_Vec();

	IConstBuffer* GetCB(e_CB Type); //enum 땜에 전방 선언 꺤거 자존심 상하는데, 
	Matrix GetViewMatrix();
	Matrix GetProjMatrix();


	void CBUpdates();

	template<typename T>
	T* GetCB()
	{
		constexpr e_CB Type = CB_Type_Traits<T>::Type;
		int index = static_cast<int>(Type);
		if (index >= m_cbBuffers.size() || m_cbBuffers[index] == nullptr) return nullptr;
		IConstBuffer* buffer = m_cbBuffers[index].get();
		return dynamic_cast<T*>(buffer);
	}

private:
	std::vector<pair<Model*, Matrix>> m_Static;
	std::vector<unique_ptr<IConstBuffer>> m_cbBuffers;

private:
	Render_Helper_SetUp m_SetUp;
};

