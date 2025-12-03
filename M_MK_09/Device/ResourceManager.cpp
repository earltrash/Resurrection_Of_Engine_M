#include "pch.h"
#include "ResourceManager.h"

using Microsoft::WRL::ComPtr;
using namespace std;

void ResourceManager::ModelLoad(std::string& filepath, ModelType Type)
{
	m_MeshResource->LoadFile(filepath, Type);
}

void ResourceManager::Set_Up(RM_Set Set)
{
	m_pDevice = Set.Device;
	m_pDeviceContext = Set.DeviceContext;


	m_MeshResource = std::make_unique< ModelResource>();
	m_ShaderResource = std::make_unique<ShaderResource>();
    m_TextureResource = std::make_unique<TextureResource>();

	m_ShaderResource->Initalize();
	m_ShaderResource->LoadShader(e_Shader_Type::Static_);
}

ComPtr<ID3D11Device> ResourceManager::GetDevice()
{
	return m_pDevice;
}

ComPtr<ID3D11DeviceContext> ResourceManager::GetDeviceContext()
{
	return m_pDeviceContext;
}

ShaderResource* ResourceManager::GetShaderResource()
{
	ShaderResource* returned = m_ShaderResource.get();
	if (returned) return returned;

	else
	return nullptr;
}

ModelResource* ResourceManager::GetModelResource()
{
	ModelResource* returned = m_MeshResource.get();
	if (returned) return returned;

	else
		return nullptr;
}

TextureResource* ResourceManager::GetTextureResource()
{

	return m_TextureResource.get();
}
