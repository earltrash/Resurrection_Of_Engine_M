#include "Commons.h"

DWORD AlignCBSize(DWORD size)
{
	DWORD sizeAligned = 0;
	BOOL bAligned = (size % 16) ? FALSE : TRUE;		//����(�ʿ�) Ȯ��.

	if (bAligned) sizeAligned = size;
	else sizeAligned = (size / 16) * 16 + 16;		//����(�ʿ�) ũ�� �����.

	return sizeAligned;
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



////////////////////////////////////////////////////////////////////////////// 
//
// ��� ���� ���� 2 : Dynamic Constant Buffer
//
// [ ���� ���� ]
// CPU ����,  GPU �б� ���� ����. ���� �������� ���� ��ȭ�� ����ϱ⿡ ������ ����.  
// ���۸� ������ ���� Map / UnMap �� ���� ó���մϴ�. �̸� ���� ���� ������ 
// D3D11_USAGE_DYNAMIC ������ �ʿ��ϸ�, �� �÷��״� ����� Map ȣ����� ���ɹ����� ����ȭ �����ݴϴ�.
// ������ ������ �ٲ��� �ʴ´ٸ�, �Ϲ����� �������� Static Buffer �� ����Ͻʽÿ�.
//            
//  [����] GPU �� ������� ���۸� ����(Map) �� ������ ����� �����϶��� ���ݵ˴ϴ�.
//  �� ��� Map �Լ��� ������ ����� ���� ������ ��ٸ� �� ���ϵ˴ϴ�.
//  ���� ��� ������ �������� Map �� Draw �� ���� ��쿡�� GPU �� ���������� �����Ǹ�,
//  ��������� Rendering Commands �� �Ϸ�� ���Ŀ� (���� ������)�� ���ϵ˴ϴ�. 
//  
//  ������ ������ ������ ��, D3D11_MAP_WRITE_DISCARD �÷��׸� �����ϸ� 
//  ���� ������ �����ʹ� ��������, ���ο� �����ͷ� ��ü�˴ϴ�.
//  ���� GPU �� ���� �����͸� ����� ������ ���̶��ϴ��� �浹 ���� (���������͸� ���) 
//  �������� �Ϸ�Ǹ� ���� ���� �����ʹ� ���ŵ˴ϴ�.  
//  �̸� ���� ���ø����̼����� �߰����� �޸� ������ ���ʿ��մϴ�. 
//
//! \see [�����ڿ� ����](https://learn.microsoft.com/en-us/windows/win32/direct3d11/how-to--use-dynamic-resources)
//! \see [Using Dynamic Buffers](https://learn.microsoft.com/en-us/windows/win32/direct3d11/how-to--use-dynamic-resources#using-dynamic-buffers)
//
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
		//ynError(hr, _T("CreateDynamicConstantBuffer : ���� ������� ���� ���� : size=%d"), sizeAligned);
		return hr;
	}

	//�ܺη� ����.
	*ppCB = pCB;

	return hr;
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











// �Ϲ����� ȯ���Ͽ��� �ùٸ� ������ ����� ����Ѵٸ� �Ʒ��� ������ ���� �Ǵ� ȣȯ�Ǿ�� �մϴ�.
// 1.���� ���� ������.  Vertex Buffer Data
// 2.���� ���� Vertex Format (Input Layout)
// 3.���̴� (�Լ�) �Է±���.  Vertex Shader (Input Layout)
// 4.���̴� (�Լ�) ����� �ø�ƽ (Semantics)
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



