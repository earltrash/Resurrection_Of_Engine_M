#include "pch.h"
#include "Asimpper.h"


bool Assimper::LoadModel(const std::string& filePath, ID3D11Device* device)
{
    const unsigned int flags =
        aiProcess_Triangulate |             // �ﰢ��ȭ (���� �ʼ�)
        aiProcess_ConvertToLeftHanded;      // �޼� ��ǥ�� ��ȯ (DirectX ��)

    const aiScene* scene = m_Importer.ReadFile(filePath, flags);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "Assimp Load Error: " << m_Importer.GetErrorString() << std::endl;
        return false;
    }

    // ��Ʈ ������ ��������� �޽� ó�� ����
    ProcessNode(scene->mRootNode, scene);

    return true;
}

void Assimper::ProcessNode(aiNode* node, const aiScene* scene)
{
    // 1. ���� ��尡 �����ϴ� ��� �޽� �ε����� ��ȸ�մϴ�.
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        unsigned int meshIndex = node->mMeshes[i];
        aiMesh* mesh = scene->mMeshes[meshIndex];

        Model* subModel = ProcessModel(mesh, scene);
        m_Models.push_back(subModel); 
    }

    //�̷��� ��������� ó�� ������, ������ ������ mesh ������ ó���ϱ� ������ ��� ȣ�� �� ��. ���� ��ü�� ���� ������ �ƴ�
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }


    //if (scene->mRootNode->mNumMeshes == 0) //���� ���. scene�� mesh data�� �о ó����Ű��.
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

    // 1. ���� ������ (��ġ, ���, UV, ź��Ʈ)
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
            vertex.Color = { color.r, color.g, color.b, 1.0f }; //  ���⼭ A�� 1.0f�� �߰�!
        }
        else
        {
            vertex.Color = { 1.0f, 1.0f, 1.0f, 1.0f }; // ���� ������ ���� ��� �⺻��
        }
        
        vertices.push_back(vertex);

    }
    std::cout << "Assimp Reported Vertex Count: " << mesh->mNumVertices << std::endl;
    UINT totalSize = vertices.size() * sizeof(Vertex);
    model->Create(m_Device, vertices.data(), totalSize, Flag);


    
    return model;
}
