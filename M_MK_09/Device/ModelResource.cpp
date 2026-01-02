#include "pch.h"
#include "ModelResource.h"

#include "Material.h"
#include "Mesh.h"

int ModelResource::LoadFile(std::string FilePath , ModelType Type)
{
	Assimp::Importer Importer;
	unsigned int flags =0;

	//Flag도 잘 읽어봐야 함.
	if (Type == ModelType::Static)
	{
		flags = aiProcess_Triangulate  |
			aiProcess_GenBoundingBoxes |
			aiProcess_CalcTangentSpace |
			aiProcess_ConvertToLeftHanded|
			aiProcess_PreTransformVertices;
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
	std::filesystem::path p;

	std::cout << "현재 경로" << std::filesystem::current_path() << std::endl;
	const aiScene* Fbx_Model = Importer.ReadFile(FilePath, flags);

	if (!Fbx_Model || Fbx_Model->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Fbx_Model->mRootNode)
	{
		std::cerr << "Assimp Load Error: " << Importer.GetErrorString() << std::endl;
		std::cerr << "읽었던 경로는" << " " << FilePath << std::endl;

		return 0;
	}

	std::unique_ptr<Model> model = std::make_unique<Model>(); 
	std::vector<std::shared_ptr<Material>> globalMaterials;

	for (int i = 0; i < Fbx_Model->mNumMaterials; i++) {
		auto mat = std::make_shared<Material>();
		
		aiMaterial* Material = Fbx_Model->mMaterials[i];
		mat->Create(Material);
		globalMaterials.push_back(mat);
	}

	for (int i = 0; i < Fbx_Model->mNumMeshes; i++)
	{
		aiMesh* pAiMesh = Fbx_Model->mMeshes[i];

		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->Create(pAiMesh);

		int Material_IDX = pAiMesh->mMaterialIndex;
		
		std::shared_ptr<Material> mat = globalMaterials[Material_IDX];

		model->m_v_Parts.push_back({ mesh, mat });
	}


	//정점 생성은 UI MODEL과 같이 하나를 돌려쓸겁니다! 
	for (UINT i = 0; i < Fbx_Model->mNumMeshes; i++)
	{
		aiMesh* pMesh = Fbx_Model->mMeshes[i];
		Vector3 meshMin = Vector3(pMesh->mAABB.mMin.x, pMesh->mAABB.mMin.y, pMesh->mAABB.mMin.z);
		Vector3 meshMax = Vector3(pMesh->mAABB.mMax.x, pMesh->mAABB.mMax.y, pMesh->mAABB.mMax.z);



		BoundingBox boundingBox;
		boundingBox.Center = (meshMin + meshMax) / 2;
		boundingBox.Extents = (meshMax - meshMin) / 2;
		model->m_v_Box.push_back(boundingBox);
	}
	
	
	if (Type == ModelType::Skeleton) //Skeleton일 경우에만 추가적으로 정보를 넣어주는 식으로 ?
	{
		//Skeleton인 경우에는 각 노드의 가중치와 본의 정보가 들어가기 때문에 추가하는 식으로.

	}

	
	m_Modelmap.emplace(FilePath, std::move(model));
}


Model* ModelResource::GetModel(std::string Key)
{
	if (m_Modelmap.find(Key) != m_Modelmap.end())
		return m_Modelmap.at(Key).get();
}