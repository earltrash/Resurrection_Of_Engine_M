#pragma once
using namespace DirectX;

class Effect
{
public:

	struct ConstBuffer
	{
		XMFLOAT4X4 mTM;
		XMFLOAT4X4 mView;
		XMFLOAT4X4 mProj;
		XMFLOAT4X4 mWVP;

		COLOR col;
		float aniT;
	};
	typedef ConstBuffer	CBuffer;


protected:
	
	ID3D11Device* m_pDev;           
	ID3D11DeviceContext* m_pDXDC;   

protected:
	
	ID3D11VertexShader* m_pVS;     
	ID3D11PixelShader* m_pPS;   

	ID3DBlob* m_pVSCode;            
	ID3D11Buffer* m_pCB;            

	//셰이더 상수데이터.
	ConstBuffer m_CBuffer;
	ID3D11InputLayout* m_pLayout;   


protected:
	int Load(const TCHAR* filename);

	//이펙트/셰이더 컴파일.
	HRESULT Compile(const WCHAR* FileName, const char* EntryPoint, const  char* ShaderModel, ID3DBlob** ppCode);

	//상수 버퍼 운용 메소드.
	HRESULT CreateConstBuffer(UINT size, ID3D11Buffer** ppCB);
	HRESULT CreateDynaConstBuffer(UINT size, void* pData, ID3D11Buffer** ppCB); // LPVOID -> void*
	HRESULT UpdateDynaConstBuffer(ID3D11DeviceContext* pDXDC, ID3D11Resource* pBuff, void* pData, UINT size); // LPDXDC, LPVOID -> 원본

	virtual int CreateInputLayout();
	//virtual int CreateInputLayout_Normal();

public:
	explicit Effect();
	virtual ~Effect();

	virtual int Create(ID3D11Device* pDev, const TCHAR* filename); // LPDEVICE -> ID3D11Device*
	virtual int Update(float dTime = 0);
	virtual void Apply(float dTime = 0);
	virtual void Release();

	
	//virtual int UpdateCB();
	
	 virtual void SetWorld(XMMATRIX* mTM);
	 virtual void SetMatrix(XMFLOAT4X4 mTM);
	 virtual void SetColor(COLOR col);
	 virtual void  SetView(XMMATRIX* mTM);
	 virtual void  SetProj(XMMATRIX* mTM);



	//멤버 접근자.
	ID3DBlob* GetVSCode() { return m_pVSCode; }            
	void* GetBufferPointer() { return m_pVSCode->GetBufferPointer(); } 
	SIZE_T GetBufferSize() { return m_pVSCode->GetBufferSize(); }

	CBuffer* GetCBuffer() { return &m_CBuffer; }
	ID3D11InputLayout* GetLayout() { return m_pLayout; }

	ID3D11VertexShader* GetVS() { return  m_pVS; }
	ID3D11PixelShader* GetPS() { return m_pPS; }
	ID3D11DeviceContext* GetContext() { return m_pDXDC; }



	DirectX::XMFLOAT4X4 GetCBView() { return m_CBuffer.mView; }
	DirectX::XMFLOAT4X4 GetCBProj() { return m_CBuffer.mProj; }
};


