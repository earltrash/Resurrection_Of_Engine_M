#pragma once

enum class e_Texture_Type
{
	DIFFUSE,
	NORMAL,
	MASK,
	
	//ETC

	MAX
};

//11_24 -> 일단 Phong Shader Model로 resource 수준을 맞추고, 후에 협엽 때 처리해보도록 하자. 

// 그냥 material 만들 때 읽어오는 식으로 하자. 굳이 TextureResource가 필요한 가? 


//EX
enum MaterialMapFlags
{
	BASECOLOR = 1 << 0,
	NORMAL = 1 << 1,
	SPECULAR = 1 << 2,

	EMISSIVE = 1 << 3,
	OPACITY = 1 << 4,
	METALNESS = 1 << 5,
	ROUGHNESS = 1 << 6
};



class Texture
{
public:
	Texture() = default;
	~Texture() = default;

public:
	bool Create(std::wstring& FilePath);
	ID3D11ShaderResourceView* GetTexture() { return m_Texture.Get(); }

private:
	std::string m_Name; //a.k.a filePath
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Texture = nullptr;
};



class TextureResource
{
public:
	TextureResource() = default;
	~TextureResource() = default;

	//void TextureLoad(std::string& path, e_Texture_Type Type); // IN CASE OF PBR

	void TextureLoad(std::wstring& path); //내부에서 
	Texture* GetTexture(std::wstring Key);


private:
	std::unordered_map<std::wstring, std::shared_ptr<Texture>> m_Texture_map;

};


