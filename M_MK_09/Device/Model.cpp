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
int Model:: Draw(float dTime, PRIMTYPE primType, VertexFlag Type) //�ϴ� �⺻������ �غ��� 
{

	Type = this->GetFlag(); 
	//topology ������ ���� �����ٸ� ���ϰڴٸ�. �ϴ� �������. �̷��� Flag ������ flag �������� ó���� �� �־ draw�� ����.


	m_Dct->IASetVertexBuffers(0, 1, &Data[Type].m_pVB, &Data[Type].m_Stride, &Data[Type].m_Offset);
	m_Dct->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)primType);
	m_Dct->Draw(Data[Type].m_VtxCnt, 0);

	

	VertexFlag actualType = (Type != VertexFlag::VF_NONE) ? Type : this->GetFlag();

	return 1;
}

void Model::CreateVB(VOID* pBuff, UINT size, VertexFlag Type)
{
	
	ID3D11Buffer* pVB = nullptr;

	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	// bd.Usage�� bd.BindFlags ������ ��������
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = size;							// 120 ����Ʈ (3 * 40 bytes)
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.pSysMem = pBuff;

	// ���� ���� ���� �� HRESULT Ȯ��
	hr = m_Dev->CreateBuffer(&bd, &rd, &pVB);

	if (FAILED(hr))
	{
		std::cerr << " ���� ���� ���� ����! HRESULT: 0x"
			<< std::hex << hr << std::dec << " | pVB: " << pVB << std::endl;
	}
	else
	{
		std::cout << " ���� ���� ���� ����! pVB: " << pVB << std::endl;
	}


	Data[Type].m_pVB = pVB;
	Data[Type].m_Size = size;



	//Data[Type].m_Stride = static_cast<UINT>(StrideFromFlag(Type));  // VF_POSCOL�� ���� 28����Ʈ
	Data[Type].m_Stride = sizeof(Vertex);                           // VF_POSCOL�� ���� 28����Ʈ

	//Data[Type].m_VtxCnt = size / sizeof(Vertex);                   // ���� Vertex ũ��(40����Ʈ)�� ���� ���� ����(3) ���
	Data[Type].m_VtxCnt = size / Data[Type].m_Stride;

	Data[Type].m_Offset = 0;
}