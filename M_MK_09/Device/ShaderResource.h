#pragma once
class ShaderResource
{
public:
	ShaderResource() = default;
	~ShaderResource() = default;
public:

	//정형화 비 정형화 
	void LoadShader(std::string FilePath, e_Shader_Type Shader_Type);
	void LoadShader(e_Shader_Type Shader_Type);

	Shader& GetShader(e_Shader_Type Type_Key);


private:
	//std::vector<Shader> m_Shader; //Flag Indexing으로 검색
	std::unordered_map<e_Shader_Type, Shader> m_Shader_Map; //enum 갯수가 크기면 그닥 속도 차이는 없을 듯.
};

