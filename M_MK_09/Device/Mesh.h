#pragma once
#include "Commons.h" //-> ���� ���� include�� �ﰡ.
#include "Device.h"
#include <vector>

class aiMesh;


struct V
{
	XMFLOAT4 Position;
	XMFLOAT3 Normal;
	XMFLOAT3 Tangent;
	XMFLOAT2 TexCoord;
	//12

};

//Vertex data�� vector�� ����. 
// 3D Model�� ���� ������ ������ �� ��� ������ �� ���� ����. (vertex buffer), 
// �˰Ե� �ǵ�, fbx�� material index?�� ������ �� �ִٰ� �ϴ����. �굵 ���⼭ ���������� ����.
// 
//���� StaticMeshResource �� ���ؼ� ������� 
// DX �������̽� ����ü �� Vertexbuffer�� ����, �ε��� ���۴� ���� �����ϰ� �ִ� ������ ��������.

//���ҽ�? ���� ������ ���� ����. ����? -> dx �������̽� ����ü�� wrapping ������. �ʿ��� ������ �������� �����ϴ� �� �´ٰ� ������.


//��� �ϴ� AIMesh ������ �ް�, ó���ϵ��� ����.
//assiper �� ���� �������.��Ȯ���� aimesh -> �̰Ŵ� obj�� �ٽ� ����� �ͱ��� �ϴ� ����ε��� ����.



class Mesh
{

public:
	void Create(aiMesh*);
	

	//STATIC MESH & ANIMATION /�� �� �� Mesh���� ó���� �� �ְ�. 
	template<typename T>
	void CreateVertexBuffer(T* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer);

	//���� Model Property
	ID3D11Buffer* m_Vertexbuffer = nullptr;
	UINT			m_Size = 0;			
	UINT			m_Stride = 0;	    
	UINT			m_Offset = 0;		
	UINT			m_VtxCnt = 0;		
	UINT  m_MaterialIndex;
private:
	std::vector<V> m_Vertex;

};

//ResourceManager-> �� �� �ְ� assimop�� ���ؼ� ó��? ���� �Ŵ�. ���� ����
template<typename T>
inline void Mesh::CreateVertexBuffer(T* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer)
{
	D3D11_BUFFER_DESC bd = {};
	bd.ByteWidth = sizeof(T) * vertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA vbData = {};
	vbData.pSysMem = vertices;

	//HR_T(m_Device->CreateBuffer(&bd, &vbData, vertexBuffer));

	m_VtxCnt = vertexCount;
	m_Stride = sizeof(T);
	m_Offset = 0;
}
