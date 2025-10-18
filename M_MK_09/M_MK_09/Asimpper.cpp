#include "pch.h"
#include "Asimpper.h"


bool Assimper::LoadModel(const std::string& filePath, ID3D11Device* device)
{
    const unsigned int flags =
        aiProcess_Triangulate |             // 삼각형화 (거의 필수)
        aiProcess_ConvertToLeftHanded;      // 왼손 좌표계 변환 (DirectX 용)

    const aiScene* scene = m_Importer.ReadFile(filePath, flags);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "Assimp Load Error: " << m_Importer.GetErrorString() << std::endl;
        return false;
    }

    // 루트 노드부터 재귀적으로 메쉬 처리 시작
    ProcessNode(scene->mRootNode, scene);

    return true;
}

void Assimper::ProcessNode(aiNode* node, const aiScene* scene)
{
    // 1. 현재 노드가 참조하는 모든 메쉬 인덱스를 순회합니다.
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        unsigned int meshIndex = node->mMeshes[i];
        aiMesh* mesh = scene->mMeshes[meshIndex];

        Model* subModel = ProcessModel(mesh, scene);
        m_Models.push_back(subModel); 
    }

    //이렇게 재귀적으로 처리 하지만, 지금은 간단한 mesh 정보만 처리하기 때문에 얘는 호출 안 됨. 파일 자체도 계층 구조가 아님
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }


    //if (scene->mRootNode->mNumMeshes == 0) //만약 없어도. scene의 mesh data를 읽어서 처리시키기.
    //{
    //    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    //    {
    //        aiMesh* mesh = scene->mMeshes[i];
    //        Model* model = ProcessModel(mesh, scene);
    //        m_Models.push_back(model);
    //    }
    //}



}

Model* Assimper::ProcessModel(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Model* model = new Model();
    VertexFlag Flag = VertexFlag::VF_NONE;

    // 1. 정점 데이터 (위치, 노멀, UV, 탄젠트)
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        
        
        vertex.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
            Flag |= VertexFlag::VF_POSITION;
        
        if (mesh->mNormals)
        {
            vertex.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };

                Flag |= VertexFlag::VF_NORMAL;
        }

        if (mesh->mTextureCoords[0])
        {
            vertex.TexCoord = {
         mesh->mTextureCoords[0][i].x,
         mesh->mTextureCoords[0][i].y };

            Flag |= VertexFlag::VF_TEXCOORD;
        }

        if (mesh->HasVertexColors(0))
        {
            aiColor4D& color = mesh->mColors[0][i];
            vertex.Color = { color.r, color.g, color.b, 1.0f }; //  여기서 A에 1.0f를 추가!
        }
        else
        {
            vertex.Color = { 1.0f, 1.0f, 1.0f, 1.0f }; // 정점 색상이 없을 경우 기본값
        }
        
        vertices.push_back(vertex);

    }
    std::cout << "Assimp Reported Vertex Count: " << mesh->mNumVertices << std::endl;
    UINT totalSize = vertices.size() * sizeof(Vertex);
    model->Create(m_Device, vertices.data(), totalSize, Flag);


    
    return model;
}
