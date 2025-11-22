#include "pch.h"
#include "Shader.h"
#include "Commons.h" //helper들만 남는다면 얘를 pch.h에 두는 것도 좋아 보여
#include "ResourceManager.h"

Shader::Shader()
{
	m_Type = e_Shader_Type::Max;
}

void Shader::Initalize(e_Shader_Type Type)
{
	m_Type = Type;
	CreateVS_N_IL();
	CreatePS();
}

void Shader::CreateVS_N_IL()
{
	//일단 기본만 하자고, 
	D3D11_INPUT_ELEMENT_DESC Static[] =
	{
		//Sementic ,IND,           FORMAT              ,SLOT ,     OFFSET                 ,     CLASS                ,RATE
		{"POSITION" , 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0 , D3D11_APPEND_ALIGNED_ELEMENT ,D3D11_INPUT_PER_VERTEX_DATA , 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};


	D3D11_INPUT_ELEMENT_DESC UI[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};


	if (m_Type == e_Shader_Type::Static_)
	{
		ID3D10Blob* Vertex_Blob = nullptr;
		::HR_T(::ShaderCompile(L"..\Shader\Default.fx", "VS_main", "vs_5_0", &Vertex_Blob)); //define도 나중에 넣을 수 있으면 넣어 보자.
		::HR_T(ResourceManager::Instance().GetDevice()->CreateInputLayout(Static, ARRAYSIZE(Static), Vertex_Blob->GetBufferPointer(),
			Vertex_Blob->GetBufferSize(), m_pInputLayout.GetAddressOf()));
		::HR_T(ResourceManager::Instance().GetDevice()->CreateVertexShader(Vertex_Blob->GetBufferPointer(),
			Vertex_Blob->GetBufferSize(), NULL, m_pVertexShader.GetAddressOf())); //class llinkage는 뭐지 
		::SafeRelease(Vertex_Blob);
	}

}

void Shader::CreatePS()
{

	if (m_Type == e_Shader_Type::Static_)
	{
		ID3D10Blob* Pixel_Blob = nullptr;
		HR_T(::ShaderCompile(L"..\Shader\Default.fx", "PS_main", "ps_5_0", &Pixel_Blob));
		HR_T(ResourceManager::Instance().GetDevice()->CreatePixelShader(Pixel_Blob->GetBufferPointer(), Pixel_Blob->GetBufferSize(),
			NULL, m_pPixelShader.GetAddressOf()));
		::SafeRelease(Pixel_Blob);
	}
}

ID3D11InputLayout* Shader::GetIL()
{
	ID3D11InputLayout* returned = m_pInputLayout.Get();
	if (returned) return returned;

	else return nullptr;
}

ID3D11PixelShader* Shader::GetPS()
{
	ID3D11PixelShader* returned = m_pPixelShader.Get();
	if (returned) return returned;

	else return nullptr;
}


ID3D11VertexShader* Shader::GetVS()
{
	ID3D11VertexShader* returned = m_pVertexShader.Get();
	if (returned) return returned;

	else return nullptr;
}


