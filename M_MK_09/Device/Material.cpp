#include "pch.h"
#include "Material.h"
#include "ResourceManager.h"

#include <assimp/scene.h>
#include <filesystem>
#include "DX_Renderer.h" //얘가 필요하나? 
#include "Render_Helper.h"

//최적화 할 수 있는 부분은 여기일듯?


void Material::Create(aiMaterial* pMaterial)
{
	aiString texturePath;
	wstring basePath = L"Resources/Models/textures/";
	std::filesystem::path path;
	wstring finalPath;

	string name = pMaterial->GetName().C_Str();
	std::cout << "Material Name : " << name << endl;


	if (AI_SUCCESS == pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath))
	{
		string rawPath = texturePath.C_Str();
		path = (rawPath);

		finalPath = basePath + path.filename().wstring();
		m_tex_Albedo = ResourceManager::Instance().CreateMaterialTexture(finalPath);
		m_Flag |= MaterialMapFlags::BASECOLOR;
	}

	if (AI_SUCCESS == pMaterial->GetTexture(aiTextureType_NORMALS, 0, &texturePath))
	{

		path = ToWString(string(texturePath.C_Str()));
		finalPath = basePath + path.filename().wstring();
		m_tex_Normal = ResourceManager::Instance().CreateMaterialTexture(finalPath);
		m_Flag |= MaterialMapFlags::NORMAL;
	}

	if (AI_SUCCESS == pMaterial->GetTexture(aiTextureType_SPECULAR, 0, &texturePath))
	{
		path = ToWString(string(texturePath.C_Str()));
		finalPath = basePath + path.filename().wstring();
		m_tex_Spec = ResourceManager::Instance().CreateMaterialTexture(finalPath);
		m_Flag |= MaterialMapFlags::SPECULAR;
	}

	if (AI_SUCCESS == pMaterial->GetTexture(aiTextureType_EMISSIVE, 0, &texturePath))
	{
		path = ToWString(string(texturePath.C_Str()));
		finalPath = basePath + path.filename().wstring();
		m_tex_Emissive = ResourceManager::Instance().CreateMaterialTexture(finalPath);
		m_Flag |= MaterialMapFlags::EMISSIVE;
	}

	if (AI_SUCCESS == pMaterial->GetTexture(aiTextureType_OPACITY, 0, &texturePath))
	{
		path = ToWString(string(texturePath.C_Str()));
		finalPath = basePath + path.filename().wstring();
		m_tex_Opacity = ResourceManager::Instance().CreateMaterialTexture(finalPath);
		m_Flag |= MaterialMapFlags::OPACITY;
	}

	if (AI_SUCCESS == pMaterial->GetTexture(aiTextureType_METALNESS, 0, &texturePath))
	{
		path = ToWString(string(texturePath.C_Str()));
		finalPath = basePath + path.filename().wstring();
		m_tex_Metal = ResourceManager::Instance().CreateMaterialTexture(finalPath);
		m_Flag |= MaterialMapFlags::METALNESS;
	}

	if (AI_SUCCESS == pMaterial->GetTexture(aiTextureType_SHININESS, 0, &texturePath))
	{
		path = ToWString(string(texturePath.C_Str()));
		finalPath = basePath + path.filename().wstring();
		m_tex_Roughness = ResourceManager::Instance().CreateMaterialTexture(finalPath);
		m_Flag |= MaterialMapFlags::ROUGHNESS;
	}

}


// 최적화는 (이미 binding 된 Texture 유무라던가) 


void Material::Bind(ID3D11DeviceContext* DXDC)
{
    DXDC->PSSetShaderResources(0, 1, m_tex_Albedo->m_pTexture.GetAddressOf());
	//DXDC->PSSetShaderResources(1, 1, m_tex_Normal->m_pTexture.GetAddressOf());
    //DXDC->PSSetShaderResources(2, 1, m_tex_Spec->m_pTexture.GetAddressOf());
	//DXDC->PSSetShaderResources(3, 1, m_tex_Emissive->m_pTexture.GetAddressOf());
	//DXDC->PSSetShaderResources(4, 1, m_tex_Metal->m_pTexture.GetAddressOf());
	//DXDC->PSSetShaderResources(5, 1, m_tex_Roughness->m_pTexture.GetAddressOf());
	//DXDC->PSSetShaderResources(6, 1, m_tex_Opacity->m_pTexture.GetAddressOf());
}

bool MaterialTexture::Create(const std::wstring& filePath)
{
	ID3D11ShaderResourceView* Texture = nullptr;
	Texture = ::CreateTexture(filePath, ResourceManager::Instance().GetDevice().Get());

	if (Texture)
	{
		m_Path = filePath;
		m_pTexture = Texture;
		return true;
	}
	else
		return false;
}
