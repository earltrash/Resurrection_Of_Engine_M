#include "pch.h"
#include "ShaderResource.h"

using Microsoft::WRL::ComPtr;
using namespace std;

void ShaderResource::Initalize()
{
	m_Shader_Vec.reserve(int(e_Shader_Type::Max)); //Capacity

	//assign은 복사라 unique_ptr이랑 못 씀 
	m_Shader_Vec.resize(int(e_Shader_Type::Max)); //size
}

void ShaderResource::LoadShader(std::string FilePath, e_Shader_Type Shader_Type)
{
	//more detail or 뭐 언젠간 쓰지 않을까요 

}

void ShaderResource::LoadShader(e_Shader_Type Shader_Type)
{
	unique_ptr<Shader> shader = std::make_unique<Shader>();
	shader->Initalize(Shader_Type);

	Shader* existed = m_Shader_Vec.at(int(Shader_Type)).get();
	if (existed) std::cout << "중복" << std::endl;

	else
	{
		m_Shader_Vec[int(Shader_Type)] = std::move(shader);
	}
}

Shader* ShaderResource::GetShader(e_Shader_Type Type_Key)
{
		Shader* returned_ = m_Shader_Vec.at(int(Type_Key)).get();
		if (returned_) return returned_;
		else
		{
			std::cout << "Shader_Vec NULL : " << int(Type_Key) + "Null";
			return nullptr;
		}
	

}
