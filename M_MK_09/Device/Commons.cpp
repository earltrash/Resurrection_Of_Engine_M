#include "pch.h"
#include "Commons.h"

float StrideFromFlag(VertexFlag Flag) //For Bytes 
{
	size_t stride = 0;
	if ((Flag & VertexFlag::VF_POSITION) != VertexFlag::VF_NONE) stride += sizeof(XMFLOAT3);
	if ((Flag & VertexFlag::VF_NORMAL) != VertexFlag::VF_NONE)   stride += sizeof(XMFLOAT3);
	if ((Flag & VertexFlag::VF_COLOR) != VertexFlag::VF_NONE)    stride += sizeof(XMFLOAT4);
	if ((Flag & VertexFlag::VF_TEXCOORD) != VertexFlag::VF_NONE) stride += sizeof(XMFLOAT2);
	return stride;
}

DWORD AlignCBSize(DWORD size)
{
	DWORD sizeAligned = 0;
	BOOL bAligned = (size % 16) ? FALSE : TRUE;		//����(�ʿ�) Ȯ��.

	if (bAligned) sizeAligned = size;
	else sizeAligned = (size / 16) * 16 + 16;		//����(�ʿ�) ũ�� �����.

	return sizeAligned;
}

#pragma region CreateFunc
HRESULT CreateDynamicConstantBuffer(ID3D11Device* pDev, UINT size, ID3D11Buffer** ppCB)
{
	HRESULT hr = S_OK;
	ID3D11Buffer* pCB = nullptr;

	//���ĵ� ���� ũ�� ��� 
	DWORD sizeAligned = AlignCBSize(size);

	//��� ���� ���� ����.
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;				//���� �������� ����.
	bd.ByteWidth = sizeAligned;						//���� ũ�� : 128��Ʈ ���� �߰�.
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;				//CPU ���� ����. 

	/*//���긮�ҽ� ����.
	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = pData;										//��� ������ ����.
	sd.SysMemPitch = 0;
	sd.SysMemSlicePitch = 0;
	*/

	//��� ���� ����.
	hr = pDev->CreateBuffer(&bd, nullptr, &pCB);
	if (FAILED(hr))
	{
		std::cout << "��� ���� ���� ����" << std::endl;
		return hr;
	}

	//�ܺη� ����.
	*ppCB = pCB;

	return hr;
}
int CreateVertexBuffer(ID3D11Device* pDev, LPVOID pData, UINT size, ID3D11Buffer** ppVB)
{
	HRESULT hr = S_OK;

	// ���� ���� Vertex Buffer ���� ���� 
	D3D11_BUFFER_DESC bd = {};
	//ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;			//���� �����
	bd.ByteWidth = size;							//���� ũ�� (����Ʈ)
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//���� �뵵 : "���� ����" 
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.pSysMem = pData;									//���ۿ� ����� ������ : "������"..

	//���� ���� ����.
	ID3D11Buffer* pVB = nullptr;
	hr = pDev->CreateBuffer(&bd, &rd, &pVB);
	if (FAILED(hr))
	{
		std::cout << "���� ���� ���� ����" << std::endl;;

		return hr;
	}


	*ppVB = pVB;
	return S_OK;
}
int CreateConstantBuffer(ID3D11Device* pDev, UINT size, ID3D11Buffer** ppCB)
{
	HRESULT hr = S_OK;

	//���ĵ� ���� ũ�� ��� 
	DWORD sizeAligned = AlignCBSize(size);

	//��� ���� ���� ����.
	D3D11_BUFFER_DESC bd = {};
	//ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;				//���� �����
	//bd.Usage	 = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeAligned;						//���� ũ�� : 128��Ʈ ���� �߰�.
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//���� �뵵 : "��� ����" 
	//bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//��� ���� ����.
	ID3D11Buffer* pCB = nullptr;
	hr = pDev->CreateBuffer(&bd, nullptr, &pCB);
	if (FAILED(hr))
	{
		//ynError(hr, _T("[����] ��� ���� ���� ���� : size=%d"), sizeAligned);
	}

	//�ܺη� ����.
	*ppCB = pCB;

	return S_OK;
}
HRESULT CreateDynamicConstantBuffer(ID3D11Device* pDev, UINT size, LPVOID pData, ID3D11Buffer** ppCB)
{
	HRESULT hr = S_OK;
	ID3D11Buffer* pCB = nullptr;

	//���ĵ� ���� ũ�� ��� 
	DWORD sizeAligned = AlignCBSize(size);

	//��� ���� ���� ����.
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;				//���� �������� ����.
	bd.ByteWidth = sizeAligned;						//���� ũ�� : 128��Ʈ ���� �߰�.
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;				//CPU ���� ����.

	//���긮�ҽ� ����.
	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = pData;							//��� ������ ����.
	sd.SysMemPitch = 0;
	sd.SysMemSlicePitch = 0;

	//��� ���� ����.
	hr = pDev->CreateBuffer(&bd, &sd, &pCB);
	if (FAILED(hr))
	{
		std::cout << "��� ���� ���� ����" << std::endl;

		return hr;
	}

	//�ܺη� ����.
	*ppCB = pCB;

	return hr;
}
int CreateInputLayout(ID3D11Device* pDev, D3D11_INPUT_ELEMENT_DESC* ed, DWORD num, ID3DBlob* pVSCode, ID3D11InputLayout** ppLayout)
{
	HRESULT hr = S_OK;

	ID3D11InputLayout* pLayout = nullptr;
	hr = pDev->CreateInputLayout(ed, num, pVSCode->GetBufferPointer(), pVSCode->GetBufferSize(), &pLayout);
	if (FAILED(hr))
	{
		std::cout << "'���̾ƿ� ���� ����" << std::endl;
		return hr;
	}
	*ppLayout = pLayout;

	return S_OK;
}
HRESULT UpdateDynamicBuffer(ID3D11DeviceContext* pDXDC, ID3D11Resource* pBuff, LPVOID pData, UINT size)
{
	HRESULT hr = S_OK;

	//���ĵ� ���� ũ�� ��� 
	DWORD sizeAligned = AlignCBSize(size);


	//���� �ڿ� ���� ����.
	D3D11_MAPPED_SUBRESOURCE mr = {};
	//ZeroMemory(&mr, sizeof(mr));
	mr.pData = nullptr;							//���ҽ� ���� ������. Map �� ���� ȹ���. 

	//���� ���� ����
	hr = pDXDC->Map(pBuff,						//���� ��� "Locked"
		0,
		D3D11_MAP_WRITE_DISCARD,	//CPU ���� ���� 
		0,
		&mr							//���� ������ ���. 
	);
	if (FAILED(hr))
	{
		std::cout << "��� ���� ������Ʈ �����ߴµ���" << std::endl;
		return hr;
	}

	memcpy(mr.pData, pData, size);				//���� ����.
	//memcpy(mr.pData, pData, sizeAligned);		//���� ���� (+���ĵ� ũ��)
	pDXDC->Unmap(pBuff, 0);						//���� �ݱ� : �������� "Unlocked"

	return hr;
}
#pragma endregion

