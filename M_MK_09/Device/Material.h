#pragma once
class aiMaterial;

class Material
{

public:
	Material() = default;
	~Material() = default;

public:
	void Create(aiMaterial* material);
	void Bind(ID3D11DeviceContext* DXDC);//상수 버퍼로 처리하기. 

	//후에 Type까지 연동
	void SetTexture(std::wstring Path);


private:
	//일단 Phong 으로 처리할 거야.
	XMFLOAT4 DIFFUSE;
	XMFLOAT4 AMBIENT;
	XMFLOAT4 SPECULAR;
	FLOAT POWER;

	std::wstring Texture_Path; //일단 diffuse만.

	ComPtr<ID3D11ShaderResourceView> m_Diffuse_Texture; // 일단 이거만

	//일단 단일 Texture로 처리하는 식으로 하자.

	//PBR 로 할 거면 위에 있는 인자 값들이 다 Texture로 처리가 될거고, bit flag로 처리하는 방식으로 해야 편할 듯.
	//Texture Pointer? 





};

