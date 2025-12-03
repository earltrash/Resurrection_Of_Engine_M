#pragma once

class MaterialTexture;

class Texture
{
public:
	Texture() = default;
	~Texture() = default;

public:
	bool Create(std::wstring& FilePath);
	ID3D11ShaderResourceView* GetTexture() { return m_Texture.Get(); }

private:
	std::wstring m_Path;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Texture = nullptr;
};



class TextureResource
{
public:
	TextureResource() = default;
	~TextureResource() = default;

	//void TextureLoad(std::string& path, e_Texture_Type Type); // IN CASE OF PBR

	std::shared_ptr<Texture> TextureLoad(std::wstring& path); //내부에서
	std::shared_ptr<MaterialTexture>  MaterialTextureLoad(std::wstring& path);
	std::shared_ptr<Texture> GetTexture(std::wstring Key);
	std::shared_ptr<MaterialTexture> GetMaterialTexture(std::wstring Key);


private:
	//multi textuer aka material texture와 single texture를 분리할 수 있도록 함. 

	std::unordered_map<std::wstring, std::shared_ptr<Texture>> m_Texture_map;
	std::unordered_map<std::wstring, std::shared_ptr<MaterialTexture>> m_MTexture_map;

};


