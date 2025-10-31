#include "pch.h"

#include "Mesh.h"
#include "ResourceManager.h"


void Mesh::Create(aiMesh* mesh)
{
    // std::vector<unsigned int> indices; -> 얘는 나중에 
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

    UINT vertexCount = m_Vertex.size() * sizeof(V);
    CreateVertexBuffer(&m_Vertex[0], vertexCount, &m_Vertexbuffer);
}

void Mesh::CreateVertexBuffer(V* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer)
{
    D3D11_BUFFER_DESC bd = {};
    	bd.ByteWidth = sizeof(V) * vertexCount;
    	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    	bd.Usage = D3D11_USAGE_DEFAULT;
    	bd.CPUAccessFlags = 0;
    
    	D3D11_SUBRESOURCE_DATA vbData = {};
    	vbData.pSysMem = vertices;
    
    	ResourceManager::Instance().GetDevice()->CreateBuffer(&bd, &vbData, vertexBuffer);
    
    	m_VtxCnt = vertexCount;
    	m_Stride = sizeof(V);
    	m_Offset = 0;
}
