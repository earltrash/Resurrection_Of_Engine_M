#pragma once
#include "ConstBuffer.h" //여기 내부 싹다 고쳐야 할 듯.


//hlsl의 맥락.
enum class e_Shader_Type
{
	



};

//->HLSL 양식을 좀 보고 
//Shader VS/PS
// VSCODE
// 
//Layout -> 이거는 Vertex 구조를 통합했으니 다 들어가지 않을까 싶긴 하지만. 모르니깐 ㅇㅇ 
//Filename -> 디버깅 용 

struct Shader_Set
{
	//Device -> Shader 생성을 위한 
	//

};


//랜더 될 때는 얘가 갖고 있는 모든 
// Shader Code Compile
// Layout 생성
// ConstBuffer 

class Shader
{
public:
	Shader() = default;
	~Shader() = default;


public:
	void SetUp(Shader_Set Set);
	void ShaderLoad(std::string FileName);


private:
	//std::vector<>


};

