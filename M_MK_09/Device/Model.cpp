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


int Model::Update(float dTime) //���� �ִ� flag�� ���� �������۸� ����� render , ��ġ���� �ϴ� local ���� �����ϵ��� ��. 
{
	return 1;

}

void Model::Release()
{
	Data.clear();
}


//Mesh Component�� ����, �ϳ��� ���� ���� ��� �ܰ迡���� drawcall
int Model:: Draw(float dTime, PRIMTYPE primType, VertexFlag Type)
{

	m_Dct->IASetVertexBuffers(0, 1, &Data[Type].m_pVB, &Data[Type].m_Stride, &Data[Type].m_Offset);
	m_Dct->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)primType);
	m_Dct->Draw(Data[Type].m_VtxCnt, 0);

	return 1;
}

void Model::CreateVB(VOID* pBuff, UINT size, VertexFlag Type)
{
	ID3D11Buffer* pVB = nullptr; //��� DEFINE �ص� �� �� ���ٴ� ������ ��.

	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;					//���� �����
	bd.ByteWidth = size;							//���� ũ��
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//���� �뵵 : "���� ����" ��� ���� 
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.pSysMem = pBuff;					//���ۿ� �� ������ ���� : "������"..

	//���� ���� ����.
	hr = m_Dev->CreateBuffer(&bd, &rd, &pVB);
	if (FAILED(hr))
	{
		std::cout << "���� ���� ������ ���� �߻���!" << std::endl;
	}

	Data[Type].m_pVB = pVB;
	Data[Type].m_Size = size;
	Data[Type].m_Stride = sizeof(Vertex);
	Data[Type].m_Offset = 0;
	Data[Type].m_VtxCnt = size / sizeof(Vertex);
}