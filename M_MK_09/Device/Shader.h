#pragma once
//#include "ConstBuffer.h" 

enum class e_Shader_Type
{
	Static_,
	Skeleton,
	UI,

	


	Max
};

class Shader
{
public:
	Shader();
	~Shader() = default;
public:
	void Initalize(e_Shader_Type Type);
	void CreateVS_N_IL();
	void CreatePS();

	ID3D11VertexShader* GetVS();
	ID3D11PixelShader* GetPS();
	ID3D11InputLayout* GetIL();

private:
	e_Shader_Type m_Type;
	ComPtr<ID3D11VertexShader> m_pVertexShader = nullptr;
	ComPtr<ID3D11PixelShader> m_pPixelShader = nullptr;
	ComPtr<ID3D11InputLayout> m_pInputLayout = nullptr;
};

