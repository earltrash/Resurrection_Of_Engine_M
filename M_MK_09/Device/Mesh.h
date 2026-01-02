#pragma once


struct V
{
	Vector4 Position;
	Vector2 TexCoord;
	Vector3 Normal;
	Vector4 Tangent;
	
};

class aiMesh;

class Mesh
{

public:
	void Create(aiMesh*); //ai mesh를 읽고. 

	void CreateVertexBuffer(V* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer);
	void CreateIndexBuffer(UINT* indices, UINT indexCount, ID3D11Buffer** vertexBuffer);

	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;

	UINT			m_Size = 0;			
	UINT			m_Stride = 0;	    
	UINT			m_Offset = 0;		
	UINT			m_VtxCnt = 0;
	UINT            m_IndexCnt = 0;
	UINT  m_MaterialIndex =0; //이건 FBX에 대한 구조가 잡히면 들어갈 수 있음.

	void Render(ID3D11DeviceContext* DXDC);

private:
	std::vector<V> m_Vertex;
	std::vector<UINT> m_Indices;
};


