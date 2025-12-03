#include "pch.h"
#include "TextureResource.h"
#include "ResourceManager.h"
#include "Material.h"

using Microsoft::WRL::ComPtr;

//이미 만들어진 것이 있다면 그거 return 해주는 sense가 필요.

std::shared_ptr<Texture> TextureResource::TextureLoad(std::wstring& path)
{
	std::shared_ptr<Texture> texture =  GetTexture(path);
	if (texture) return texture;

	else //없으면 만들죠 뭐 
	{
		std::shared_ptr<Texture> texture = std::make_shared<Texture>();
		if (texture->Create(path))
		{
			m_Texture_map.emplace(path, texture);
			return m_Texture_map.at(path);
		}
		
		else //없으면 진짜 없는건데
		{
			std::cout << "이건 맵에도 없는데? 경로 확인좀 해봐" << std::endl;
			std::wcout << path << std::endl;
			return nullptr;
		}
	}
}


std::shared_ptr<MaterialTexture>  TextureResource::MaterialTextureLoad(std::wstring& path)
{
	std::shared_ptr<MaterialTexture> texture = GetMaterialTexture(path);
	if (texture) return texture;

	else //없으면 만들죠 뭐 
	{
		std::shared_ptr<MaterialTexture> texture = std::make_shared<MaterialTexture>();
		if (texture->Create(path))
		{
			m_MTexture_map.emplace(path, texture);
			return m_MTexture_map.at(path);
		}

		else //없으면 진짜 없는건데
		{
			std::cout << "이건 맵에도 없는데? 경로 확인좀 해봐" << std::endl;
			std::wcout << path << std::endl;
			return nullptr;
		}
	}
}

std::shared_ptr<Texture> TextureResource::GetTexture(std::wstring Key)
{
	if (m_Texture_map.find(Key) != m_Texture_map.end())
	{
		std::shared_ptr<Texture> texture = m_Texture_map.at(Key);
		return texture;
	}
	else return nullptr;
}

std::shared_ptr<MaterialTexture> TextureResource::GetMaterialTexture(std::wstring Key)
{
	if (m_MTexture_map.find(Key) != m_MTexture_map.end())
	{
		std::shared_ptr<MaterialTexture> texture = m_MTexture_map.at(Key);
		return texture;
	}
	else return nullptr;
}


//
bool Texture::Create(std::wstring& FilePath)
{
	ID3D11ShaderResourceView* Texture = nullptr;
	Texture =  ::CreateTexture(FilePath, ResourceManager::Instance().GetDevice().Get());

	if (Texture)
	{
		m_Path = FilePath;
		m_Texture = Texture;
		return true;
	}
	else 
		return false;
}
