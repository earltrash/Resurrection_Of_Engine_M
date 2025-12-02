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
		flags = aiProcess_Triangulate |             // 사각형 이상을 삼각형으로 변환 (필수)
		aiProcess_ConvertToLeftHanded |
			aiProcess_CalcTangentSpace|
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
	std::filesystem::path p;

	std::cout << "현재 경로" << std::filesystem::current_path() << endl;
	const aiScene* Fbx_Model = Importer.ReadFile(FilePath, flags);

	if (!Fbx_Model || Fbx_Model->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Fbx_Model->mRootNode)
	{
		std::cerr << "Assimp Load Error: " << Importer.GetErrorString() << std::endl;
		std::cerr << "읽었던 경로는" << " " << FilePath << endl;

		return 0;
	}

	//

	std::unique_ptr<Model> model = make_unique<Model>(); 
	std::vector<std::shared_ptr<Material>> globalMaterials;

	for (int i = 0; i < Fbx_Model->mNumMaterials; i++) {
		auto mat = make_shared<Material>();
		
		aiMaterial* Material = Fbx_Model->mMaterials[i];
		mat->Create(Material);
		globalMaterials.push_back(mat);
	}

	for (int i = 0; i < Fbx_Model->mNumMeshes; i++)
	{
		aiMesh* pAiMesh = Fbx_Model->mMeshes[i];

		//parts 라고 보는 게 더 직관적일 듯 
		std::shared_ptr<Mesh> mesh = make_shared<Mesh>();
		mesh->Create(pAiMesh);

		int Material_IDX = pAiMesh->mMaterialIndex;
		
		std::shared_ptr<Material> mat = globalMaterials[Material_IDX];

		model->m_Parts.push_back({ mesh, mat });
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