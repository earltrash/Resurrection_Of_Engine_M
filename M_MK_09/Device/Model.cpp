#include "Model.h"


Model::~Model() { Release(); }




int Model::Create(ID3D11Device* pDev, VOID* pBuff, UINT size, VertexFlag Type)
{
	m_Dev = pDev;
	m_Flag = Type;

	m_Dev->GetImmediateContext(&m_Dct);

	CreateVB( pBuff, size, Type);
	return 1;

}


int Model::Update(float dTime) //갖고 있는 flag를 토대로 정점버퍼를 만들고 render , 위치값은 일단 local 에서 진행하도록 함. 
{
	return 1;

}

void Model::Release()
{
	Data.clear();
}


//Mesh Component로 빼는, 하나의 정점 버퍼 운용 단계에서의 drawcall
int Model:: Draw(float dTime, PRIMTYPE primType, VertexFlag Type)
{

	m_Dct->IASetVertexBuffers(0, 1, &Data[Type].m_pVB, &Data[Type].m_Stride, &Data[Type].m_Offset);
	m_Dct->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)primType);
	m_Dct->Draw(Data[Type].m_VtxCnt, 0);

	return 1;
}

void Model::CreateVB(VOID* pBuff, UINT size, VertexFlag Type)
{
	ID3D11Buffer* pVB = nullptr; //얘는 DEFINE 해도 될 거 같다는 생각이 듦.

	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;					//버퍼 사용방식
	bd.ByteWidth = size;							//버퍼 크기
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//버퍼 용도 : "정점 버퍼" 용로 설정 
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.pSysMem = pBuff;					//버퍼에 들어갈 데이터 설정 : "정점들"..

	//정점 버퍼 생성.
	hr = m_Dev->CreateBuffer(&bd, &rd, &pVB);
	if (FAILED(hr))
	{
		std::cout << "정점 버퍼 생성중 오류 발생함!" << std::endl;
	}

	Data[Type].m_pVB = pVB;
	Data[Type].m_Size = size;
	Data[Type].m_Stride = sizeof(Vertex);
	Data[Type].m_Offset = 0;
	Data[Type].m_VtxCnt = size / sizeof(Vertex);
}