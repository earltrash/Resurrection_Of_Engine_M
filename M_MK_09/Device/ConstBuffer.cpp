#include "ConstBuffer.h"
#include "Device.h"

HRESULT cbDEFAULT::Create(ID3D11Device* pDev)
{
	return ::CreateDynamicConstantBuffer(pDev, sizeof(cbMatrix_4), &m_pD3DBuffer);
}

HRESULT cbDEFAULT::Update(ID3D11DeviceContext* pDXDC)
{
	return UpdateDynamicBuffer(
		pDXDC,
		m_pD3DBuffer,
		&matrix,
		sizeof(cbMatrix_4));
}

HRESULT cbLIGHT::Create(ID3D11Device* pDev)
{
	return ::CreateDynamicConstantBuffer(pDev, sizeof(cbLT), &m_pD3DBuffer);
}

HRESULT cbLIGHT::Update(ID3D11DeviceContext* pDXDC)
{
	return UpdateDynamicBuffer(
		pDXDC,
		m_pD3DBuffer,
		&light,
		sizeof(cbLT));
}

HRESULT cbMATERIAL::Create(ID3D11Device* pDev)
{
	return ::CreateDynamicConstantBuffer(pDev, sizeof(cbMAT), &m_pD3DBuffer);
}

HRESULT cbMATERIAL::Update(ID3D11DeviceContext* pDXDC)
{
	return UpdateDynamicBuffer(
		pDXDC,
		m_pD3DBuffer,
		&material,
		sizeof(cbMAT));
}