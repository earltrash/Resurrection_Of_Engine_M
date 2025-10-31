#include "pch.h"

#include "ResourceManager.h"

void ResourceManager::ModelLoad(std::string filepath, ModelType Type)
{
	m_MeshResource->LoadFile(filepath, Type);
}

void ResourceManager::Set_Up(RM_Set Set)
{
	m_pDevice = Set.Device;
	m_pDeviceContext = Set.DeviceContext;
}

ComPtr<ID3D11Device> ResourceManager::GetDevice()
{
	return m_pDevice;
}

ComPtr<ID3D11DeviceContext> ResourceManager::GetDeviceContext()
{
	return m_pDeviceContext;
}
