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
int Model:: Draw(float dTime, PRIMTYPE primType, VertexFlag Type) //일단 기본값으로 해보자 
{

	Type = this->GetFlag(); 
	//topology 정보도 같이 가진다면 편하겠다만. 일단 열어두자. 이러면 Flag 정보는 flag 내에서만 처리될 수 있어서 draw도 편함.


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

	// bd.Usage와 bd.BindFlags 설정은 문제없음
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = size;							// 120 바이트 (3 * 40 bytes)
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.pSysMem = pBuff;

	// 정점 버퍼 생성 및 HRESULT 확인
	hr = m_Dev->CreateBuffer(&bd, &rd, &pVB);

	if (FAILED(hr))
	{
		std::cerr << " 정점 버퍼 생성 실패! HRESULT: 0x"
			<< std::hex << hr << std::dec << " | pVB: " << pVB << std::endl;
	}
	else
	{
		std::cout << " 정점 버퍼 생성 성공! pVB: " << pVB << std::endl;
	}


	Data[Type].m_pVB = pVB;
	Data[Type].m_Size = size;



	//Data[Type].m_Stride = static_cast<UINT>(StrideFromFlag(Type));  // VF_POSCOL에 맞춰 28바이트
	Data[Type].m_Stride = sizeof(Vertex);                           // VF_POSCOL에 맞춰 28바이트

	//Data[Type].m_VtxCnt = size / sizeof(Vertex);                   // 실제 Vertex 크기(40바이트)로 나눠 정점 개수(3) 계산
	Data[Type].m_VtxCnt = size / Data[Type].m_Stride;

	Data[Type].m_Offset = 0;
}