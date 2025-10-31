#include "pch.h"
#include "MeshResource.h"




void MeshResource::LoadFile(std::string FilePath , ModelType Type)
{
	Assimp::Importer Importer;
	unsigned int flags =0;

	//Flag도 잘 읽어봐야 함.
	if (Type == ModelType::Static)
	{
		flags = aiProcess_Triangulate |             // 사각형 이상을 삼각형으로 변환 (필수)
		aiProcess_ConvertToLeftHanded |
		aiProcess_PreTransformVertices;      // 왼손 좌표계로 변환 (DirectX 필수)

		//aiProcess_CalcTangentSpace |        // PBR을 위한 탄젠트 벡터 계산
		//aiProcess_JoinIdenticalVertices |   // 정점 최적화
		//aiProcess_SortByPType;              // 하나의 메쉬가 여러 기본 요소를 가지지 않도록 분리
	}
	else
	{
		flags = aiProcess_Triangulate | // 삼각형으로 변환
			aiProcess_GenNormals |   // 노말 생성
			aiProcess_GenUVCoords |  // UV 생성
			aiProcess_CalcTangentSpace |  // 탄젠트 생성
			aiProcess_LimitBoneWeights |  // 본의 영향을 받는 정점의 최대 개수를 4개로 제한
			aiProcess_GenBoundingBoxes |  // 바운딩 박스 생성
			aiProcess_ConvertToLeftHanded;   // 왼손 좌표계로 변환
	}

	const aiScene* Fbx_Model = Importer.ReadFile(FilePath, flags);

	if (!Fbx_Model || Fbx_Model->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Fbx_Model->mRootNode)
	{
		std::cerr << "Assimp Load Error: " << Importer.GetErrorString() << std::endl;
		std::cerr << "읽었던 경로는" << " " << FilePath << endl;
	}

	Model model;


	if (Type == ModelType::Skeleton) //Skeleton일 경우에만 추가적으로 정보를 넣어주는 식으로 ?
	{
		//Skeleton인 경우에는 각 노드의 가중치와 본의 정보가 들어가기 때문에 추가하는 식으로.

	}

	
	model.m_Mesh.resize(Fbx_Model->mNumMeshes);


	for (int i = 0; i < Fbx_Model->mNumMeshes; i++)
	{
		aiMesh* pAiMesh = Fbx_Model->mMeshes[i];

		model.m_Mesh[i].Create(pAiMesh);
		//내부에서는 Mesh // Buffer // stride 같은 것들이 모두 처리가 됨. 
	}


	m_Modelmap.emplace(FilePath, model);


}
