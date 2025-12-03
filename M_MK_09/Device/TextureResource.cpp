#include "pch.h"
#include "TextureResource.h"
#include "ResourceManager.h"

using Microsoft::WRL::ComPtr;
using namespace std;

void TextureResource::TextureLoad(std::wstring& path)
{
	shared_ptr<Texture> texture = make_shared<Texture>();
	if (texture->Create(path)) m_Texture_map.emplace(path, texture);

	else
	{ std::cout << "TextureLoad Faield: ";
	std::wcout << path << endl;
	}


}

Texture* TextureResource::GetTexture(std::wstring Key)
{
	if(m_Texture_map.find(Key) != m_Texture_map.end())
	{
		Texture* texture = m_Texture_map.at(Key).get();
		return texture;
	}
	else
	{
		//없으면 만들죠 뭐 
		shared_ptr<Texture> texture = make_shared<Texture>();

		if (texture->Create(Key))
		{
			m_Texture_map.emplace(Key, texture);

			return m_Texture_map.at(Key).get();
		}
		//없으면 진짜 없는건데

		else
		{
			std::cout << "이건 맵에도 없는데? 경로 확인좀 해봐" << endl;
			std::wcout << Key << endl;
			return nullptr;
		}
	}
}

//
bool Texture::Create(std::wstring& FilePath)
{
	ID3D11ShaderResourceView* Texture = nullptr;
	Texture =  ::CreateTexture(FilePath, ResourceManager::Instance().GetDevice().Get());

	if (Texture)
	{
		m_Texture = Texture;
		return true;
	}
	else 
		return false;
}
