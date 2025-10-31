#include "pch.h"
#include "MeshResource.h"




void MeshResource::LoadFile(std::string FilePath , ModelType Type)
{
	Assimp::Importer Importer;
	unsigned int flags =0;

	//Flag�� �� �о���� ��.
	if (Type == ModelType::Static)
	{
		flags = aiProcess_Triangulate |             // �簢�� �̻��� �ﰢ������ ��ȯ (�ʼ�)
		aiProcess_ConvertToLeftHanded |
		aiProcess_PreTransformVertices;      // �޼� ��ǥ��� ��ȯ (DirectX �ʼ�)

		//aiProcess_CalcTangentSpace |        // PBR�� ���� ź��Ʈ ���� ���
		//aiProcess_JoinIdenticalVertices |   // ���� ����ȭ
		//aiProcess_SortByPType;              // �ϳ��� �޽��� ���� �⺻ ��Ҹ� ������ �ʵ��� �и�
	}
	else
	{
		flags = aiProcess_Triangulate | // �ﰢ������ ��ȯ
			aiProcess_GenNormals |   // �븻 ����
			aiProcess_GenUVCoords |  // UV ����
			aiProcess_CalcTangentSpace |  // ź��Ʈ ����
			aiProcess_LimitBoneWeights |  // ���� ������ �޴� ������ �ִ� ������ 4���� ����
			aiProcess_GenBoundingBoxes |  // �ٿ�� �ڽ� ����
			aiProcess_ConvertToLeftHanded;   // �޼� ��ǥ��� ��ȯ
	}

	const aiScene* Fbx_Model = Importer.ReadFile(FilePath, flags);

	if (!Fbx_Model || Fbx_Model->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Fbx_Model->mRootNode)
	{
		std::cerr << "Assimp Load Error: " << Importer.GetErrorString() << std::endl;
		std::cerr << "�о��� ��δ�" << " " << FilePath << endl;
	}

	Model model;


	if (Type == ModelType::Skeleton) //Skeleton�� ��쿡�� �߰������� ������ �־��ִ� ������ ?
	{
		//Skeleton�� ��쿡�� �� ����� ����ġ�� ���� ������ ���� ������ �߰��ϴ� ������.

	}

	
	model.m_Mesh.resize(Fbx_Model->mNumMeshes);


	for (int i = 0; i < Fbx_Model->mNumMeshes; i++)
	{
		aiMesh* pAiMesh = Fbx_Model->mMeshes[i];

		model.m_Mesh[i].Create(pAiMesh);
		//���ο����� Mesh // Buffer // stride ���� �͵��� ��� ó���� ��. 
	}


	m_Modelmap.emplace(FilePath, model);


}
