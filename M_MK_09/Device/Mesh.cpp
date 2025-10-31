
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//XMFLOAT4 Pos;
//XMFLOAT3 Nor;
//XMFLOAT3 Tangent;
//XMFLOAT2 Uv;
//12

void Mesh::Create(aiMesh* mesh)
{
   // std::vector<unsigned int> indices; -> ��� ���߿� 

     // ���� flag�� ������ ����. vertex ������ ��ü�� �������� ������ ����.
      //���� ������ (��ġ, ���, UV, ź��Ʈ)

    m_Vertex.reserve(mesh->mNumVertices);

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        V vertex;
        vertex.Position = { mesh->mVertices[i].x , mesh->mVertices[i].y , mesh->mVertices[i].z ,1.0f };
        vertex.Normal = { mesh->mNormals[i].x , mesh->mNormals[i].y , mesh->mNormals[i].z };
        vertex.TexCoord = { mesh->mTextureCoords[0][i].x , mesh->mTextureCoords[0][i].y }; //��.. �ͱ� 
        vertex.Tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };



        m_Vertex.push_back( vertex);
    }

    UINT totalSize = m_Vertex.size() * sizeof(V);

    //���ؽ� ���� ������Ʈ.

    CreateVertexBuffer<V>(&m_Vertex[0], totalSize, &m_Vertexbuffer);

   
}
