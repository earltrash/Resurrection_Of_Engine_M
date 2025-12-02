#pragma once

struct V
{
	XMFLOAT4 Position;
	XMFLOAT2 TexCoord;
	XMFLOAT3 Normal;
	XMFLOAT3 Tangent;
	
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


