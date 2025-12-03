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

std::shared_ptr<MaterialTexture> ResourceManager::CreateMaterialTexture(std::wstring Path)
{
	std::shared_ptr<MaterialTexture> p_out = m_TextureResource->MaterialTextureLoad(Path);

	return p_out;
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
	TextureResource* returned = m_TextureResource.get();
	if (returned) return returned;
	else
		return nullptr;
}
