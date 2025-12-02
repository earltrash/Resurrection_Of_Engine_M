#pragma once

//ResourceManager로 부터 device같은 거는 받으시고, 
//texture 생성이랑, 

//TO DO  TEXTURE TYPE을 나눠서 RENDER 시 필요하면 SETTING 해 놓기 

//이거 비트 연산으로 처리하면 편할 거 같은ㄷ데, 
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
	ComPtr<ID3D11ShaderResourceView> m_Texture = nullptr;
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


