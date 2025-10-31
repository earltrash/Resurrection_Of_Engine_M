#pragma once

//Mesh를 포함하는 

#include "Model.h"
#include <string>

//얘의 할일은
// 
// 확장자를 제외한 이름으로 보관하거나 하는 식? 일단 기본적인 형태로만 해보자.
// 
//1. Resource Manager로 부터 MeshResource를 파싱 및 저장 (정확히는 3DModeldata를 자료구조로 정리
//2. Texture나 Material는 모르겠다. 
//3. StaticMeshComponent나 dynamicMeshComponent의 3d Instance에 들어가는 3d Model의 데이터를 여기서 받아옴. 
//
// Resorce와 그려지는 Instance를 분리하는 과정 
//
// Model를 통해 material의 주소나 정보값을 넘길 수도 있다. -> 그럼 굳이 다른 곳에서 Matrial을 관리해야 할까. 
// 정확히는 material의 경로만 저장해 두고, 필요할 때, texture 정보를 저장한 곳에서 가져오면 되지 않을까. 
//
//
//

enum class ModelType
{
	Static,
	Skeleton
};



class MeshResource
{
public:
	MeshResource() = default;
	~MeshResource() = default;

public:

	void LoadFile(std::string FilePath , ModelType Type ); //ResourceManager를 통해서 호출되는 함수.
	std::unordered_map<std::string, Model> m_Modelmap;


};

