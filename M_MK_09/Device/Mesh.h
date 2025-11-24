#pragma once

struct V
{
	XMFLOAT4 Position;
	XMFLOAT3 Normal;
	XMFLOAT3 Tangent;
	XMFLOAT2 TexCoord;
};

class aiMesh;

class Mesh
{

public:
	void Create(aiMesh*); //ai mesh를 읽고. 

	void CreateVertexBuffer(V* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer);

	//기존 Model Property
	//이거 INDEX BUFFER로 수정하자 
	ID3D11Buffer* m_Vertexbuffer = nullptr;
	//Index Buffer로 수정해야 함.

	UINT			m_Size = 0;			
	UINT			m_Stride = 0;	    
	UINT			m_Offset = 0;		
	UINT			m_VtxCnt = 0;

	UINT  m_MaterialIndex =0; //이건 FBX에 대한 구조가 잡히면 들어갈 수 있음.

	void Render(ID3D11DeviceContext* DXDC);

private:
	std::vector<V> m_Vertex;
};

//ResourceManager-> 그 밑 애가 assimop를 통해서 처리? 해줄 거니. 따로 ㄴㄴ
//template<typename T>
//inline void Mesh::CreateVertexBuffer(T* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer)
//{
//	D3D11_BUFFER_DESC bd = {};
//	bd.ByteWidth = sizeof(T) * vertexCount;
//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.CPUAccessFlags = 0;
//
//	D3D11_SUBRESOURCE_DATA vbData = {};
//	vbData.pSysMem = vertices;
//
//	ResourceManager::Instance().GetDevice()->CreateBuffer(&bd, &vbData, vertexBuffer);
//
//	m_VtxCnt = vertexCount;
//	m_Stride = sizeof(T);
//	m_Offset = 0;
//}

