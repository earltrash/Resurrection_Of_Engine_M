#pragma once
#include "Commons.h" //-> 쓸데 없는 include는 삼가.

//#include "Device.h"

struct V
{
	XMFLOAT4 Position;
	XMFLOAT3 Normal;
	XMFLOAT3 Tangent;
	XMFLOAT2 TexCoord;
};

//Vertex data를 vector로 관리. 
// 3D Model의 정점 정보가 가져야 할 모든 정보를 다 갖고 있음. (vertex buffer), 
// 알게된 건데, fbx에 material index?도 가져올 수 있다고 하더라고. 얘도 여기서 가져오도록 하자.
// 
//예는 StaticMeshResource 를 통해서 만들어짐 
// DX 인터페이스 구조체 중 Vertexbuffer를 보유, 인덱스 버퍼는 따로 공부하고 넣는 식으로 진행하자.
//리소스? 정점 정보에 대한 구분. 기준? -> dx 인터페이스 구조체를 wrapping 했으니. 필요한 정보를 기준으로 정의하는 게 맞다고 생각함.
//얘는 일단 AIMesh 형식을 받고, 처리하도록 하자.
//assiper 를 통해 만들어짐.정확히는 aimesh -> 이거는 obj로 다시 만드는 것까지 일단 열어두도록 하자.



class aiMesh;

class Mesh
{

public:
	void Create(aiMesh*); //ai mesh를 읽고. 

	void CreateVertexBuffer(V* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer);

	//기존 Model Property
	ID3D11Buffer* m_Vertexbuffer = nullptr;

	UINT			m_Size = 0;			
	UINT			m_Stride = 0;	    
	UINT			m_Offset = 0;		
	UINT			m_VtxCnt = 0;

	UINT  m_MaterialIndex =0; //이건 FBX에 대한 구조가 잡히면 들어갈 수 있음.

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

