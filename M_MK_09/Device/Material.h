#pragma once
class aiMaterial;

#include <wrl/client.h>


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

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Diffuse_Texture; // 일단 이거만

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texAlbedo;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texNormal;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texMRA;

};

