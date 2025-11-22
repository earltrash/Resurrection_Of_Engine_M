#include "pch.h"
#include "Render_Helper.h"

void Render_Helper::LoadModels(std::pair < Model*, XMMATRIX> Data)
{
	m_Static.push_back(Data);
	
}

void Render_Helper::Initalize(Render_Helper_SetUp SetUp)
{
	m_SetUp = SetUp;
	m_cbBuffers.reserve(static_cast<int>(e_CB::MAX));

	//assign은 복사로 이루어져서, unique_ptr이랑 같이 못 써요 
	m_cbBuffers.resize(static_cast<int>(e_CB::MAX));

	unique_ptr<cbDEFAULT> m_cb_Default = make_unique<cbDEFAULT>();
	m_cb_Default->Create(m_SetUp.m_Device.Get());

	unique_ptr<cbLIGHT> m_cb_Light = make_unique<cbLIGHT>();
	m_cb_Light->Create(m_SetUp.m_Device.Get());

	unique_ptr<cbMATERIAL>m_cb_Material = make_unique<cbMATERIAL>();
	m_cb_Material->Create(m_SetUp.m_Device.Get());


	m_cbBuffers[static_cast<int>(e_CB::CB_DEFAULT)] = std::move(m_cb_Default);
	m_cbBuffers[static_cast<int>(e_CB::CB_LIGHT)] = std::move(m_cb_Light);
	m_cbBuffers[static_cast<int>(e_CB::CB_MATERIAL)] = std::move(m_cb_Material);

}

std::vector<pair<Model*, XMMATRIX>>& Render_Helper::Get_Model_Vec()
{
	return std::ref(m_Static); //복사는 하기 싫어요 
}

std::vector<unique_ptr<IConstBuffer>>& Render_Helper::Get_CB_Vec()
{
	return std::ref(m_cbBuffers);
}

//폐지 예정 
IConstBuffer* Render_Helper::GetCB(e_CB Type)
{
	IConstBuffer* returned = m_cbBuffers.at(static_cast<int>(Type)).get();

	if (returned) return returned;

	else 
	return nullptr;
}

void Render_Helper::CBUpdates()
{
	for (auto& bufs : m_cbBuffers)
	{
		bufs.get()->Update(m_SetUp.m_DXDC.Get());
	}
}
