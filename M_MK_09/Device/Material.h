#pragma once
class aiMaterial;
#include <wrl/client.h>


enum class MaterialMapFlags
{
	None = 0,
	BASECOLOR = 1 << 0,
	NORMAL = 1 << 1,
	SPECULAR = 1 << 2,

	EMISSIVE = 1 << 3,
	OPACITY = 1 << 4,
	METALNESS = 1 << 5,
	ROUGHNESS = 1 << 6
};


inline MaterialMapFlags operator|(MaterialMapFlags a, MaterialMapFlags b)
{
	return static_cast<MaterialMapFlags>(static_cast<int>(a) | static_cast<int>(b));
}

//+
inline MaterialMapFlags& operator|=(MaterialMapFlags& a, MaterialMapFlags b)
{
	a = a | b; 
	return a;
}

class MaterialTexture
{
public:

	MaterialTexture() = default;
	~MaterialTexture() = default;
public:
	
	bool Create(const std::wstring& filePath);
	ComPtr<ID3D11ShaderResourceView> m_pTexture = nullptr;
	std::wstring m_Path;
};



//multi texture로 material을 표현할 거니깐 사실 material = material texture라고 보는 게 맞을 듯 ㅇㅇ 
class Material
{

public:
	Material() = default;
	~Material() = default;

public:
	void Create(aiMaterial* material);
	void Bind(ID3D11DeviceContext* DXDC);//상수 버퍼로 처리하기. 
private:
	MaterialMapFlags m_Flag = MaterialMapFlags::None; //Texture Set 및, Render pass State 설정을 위해.
	std::shared_ptr<MaterialTexture> m_tex_Albedo;
	std::shared_ptr<MaterialTexture> m_tex_Normal;
	std::shared_ptr<MaterialTexture> m_tex_Spec;
	std::shared_ptr<MaterialTexture> m_tex_Emissive;
	std::shared_ptr<MaterialTexture> m_tex_Metal;
	std::shared_ptr<MaterialTexture> m_tex_Roughness;
	std::shared_ptr<MaterialTexture> m_tex_Opacity;
};

