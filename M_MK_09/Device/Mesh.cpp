#include "pch.h"

#include "Mesh.h"
#include "ResourceManager.h"


void Mesh::Create(aiMesh* mesh)
{
     //조건처리를 더 해도 되긴 함. //Optional ? 
    m_Vertex.reserve(mesh->mNumVertices);
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        V vertex;
        vertex.Position = { mesh->mVertices[i].x , mesh->mVertices[i].y , mesh->mVertices[i].z ,1.0f };
        vertex.Normal = { mesh->mNormals[i].x , mesh->mNormals[i].y , mesh->mNormals[i].z };
        vertex.TexCoord = { mesh->mTextureCoords[0][i].x , mesh->mTextureCoords[0][i].y }; 
        vertex.Tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };

        m_Vertex.push_back(vertex);
    }

    UINT vertexCount = m_Vertex.size();
    m_Indices.clear();
    m_Indices.reserve(mesh->mNumFaces * 3);

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            m_Indices.push_back(face.mIndices[j]);
        }
    }
    CreateIndexBuffer(&m_Indices[0], m_Indices.size(), &m_IndexBuffer);
    CreateVertexBuffer(&m_Vertex[0], vertexCount, &m_VertexBuffer);
}

void Mesh::CreateVertexBuffer(V* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer)
{
    D3D11_BUFFER_DESC bd = {};
    	bd.ByteWidth = vertexCount * sizeof(V); //바이트 단위
    	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    	bd.Usage = D3D11_USAGE_DEFAULT;      // 메모리 저장 위치와 접근 권한 설정 - GPU는 읽기/쓰기 가능, CPU는 접근 불가(직접 수정 불가
    	bd.CPUAccessFlags = 0;               // 생성된 후 cpu가 메모리를 read/write 가능한가? 0 이면 건들 ㄴㄴ / 접근하는 건 너무 느려! 
    
    	D3D11_SUBRESOURCE_DATA vbData = {};
    	vbData.pSysMem = vertices;
    
    	ResourceManager::Instance().GetDevice()->CreateBuffer(&bd, &vbData, vertexBuffer);
    
    	m_VtxCnt = vertexCount;
    	m_Stride = sizeof(V);
    	m_Offset = 0;
}

//flag 하나만 빼면 template처리를 할 수 있어. 

void Mesh::CreateIndexBuffer(UINT* indices, UINT indexCount, ID3D11Buffer** IndexBuffer)
{
    D3D11_BUFFER_DESC bd = {};
    bd.ByteWidth = sizeof(UINT) * indexCount;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.CPUAccessFlags = 0;  

    D3D11_SUBRESOURCE_DATA idData = {};
    idData.pSysMem = indices;
    ResourceManager::Instance().GetDevice()->CreateBuffer(&bd, &idData, IndexBuffer);

    m_IndexCnt = indexCount;
}

void Mesh::Render(ID3D11DeviceContext* DXDC)
{
    DXDC->IASetVertexBuffers(0, 1, &m_VertexBuffer, &m_Stride, &m_Offset);
    DXDC->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    DXDC->DrawIndexed(m_IndexCnt, 0, 0);
}

