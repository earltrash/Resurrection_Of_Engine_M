#pragma once
#include "Shader.h"

class ShaderResource
{
public:
	ShaderResource() = default;
	~ShaderResource() = default;
public:
	void Initalize(); //명시적으로 하는 게 마음 편하더라. 
public:
	void LoadShader(std::string FilePath, e_Shader_Type Shader_Type);
	void LoadShader(e_Shader_Type Shader_Type);
	Shader* GetShader(e_Shader_Type Type_Key);


private:
	std::vector<unique_ptr<Shader>> m_Shader_Vec; //굳이 map을 쓸 필요를 못 느껴.
};

