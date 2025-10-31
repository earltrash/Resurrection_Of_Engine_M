
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
   // std::vector<unsigned int> indices; -> 얘는 나중에 

     // 이제 flag로 만들지 않음. vertex 데이터 자체는 고정으로 가져갈 거임.
      //정점 데이터 (위치, 노멀, UV, 탄젠트)

    m_Vertex.reserve(mesh->mNumVertices);

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        V vertex;
        vertex.Position = { mesh->mVertices[i].x , mesh->mVertices[i].y , mesh->mVertices[i].z ,1.0f };
        vertex.Normal = { mesh->mNormals[i].x , mesh->mNormals[i].y , mesh->mNormals[i].z };
        vertex.TexCoord = { mesh->mTextureCoords[0][i].x , mesh->mTextureCoords[0][i].y }; //음.. 왤까 
        vertex.Tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };



        m_Vertex.push_back( vertex);
    }

    UINT totalSize = m_Vertex.size() * sizeof(V);

    //버텍스 버퍼 업데이트.

    CreateVertexBuffer<V>(&m_Vertex[0], totalSize, &m_Vertexbuffer);

   
}
