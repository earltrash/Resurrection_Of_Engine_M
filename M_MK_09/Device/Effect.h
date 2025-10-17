#pragma once
#include "Commons.h"
#include "ConstBuffer.h"

class Effect
{
public:

	std::vector<std::unique_ptr<IConstBuffer>> m_ConstantBuffers;

protected:
	
	ID3D11Device* m_pDev = nullptr;
	ID3D11DeviceContext* m_pDXDC = nullptr;
	ID3D11SamplerState* m_Sampler_Desc = nullptr;
protected:
	
	ID3D11VertexShader* m_pVS = nullptr;
	ID3D11PixelShader* m_pPS = nullptr;

	ID3DBlob* m_pVSCode = nullptr;
	ID3D11Buffer* m_pCB = nullptr;

	ID3D11InputLayout* m_pLayout = nullptr;


protected:
	int Load(const TCHAR* filename);

	//이펙트/셰이더 컴파일.
	HRESULT Compile(const WCHAR* FileName, const char* EntryPoint, const  char* ShaderModel, ID3DBlob** ppCode);
	void Createbuffer_wrapped(VertexFlag type);
	//상수 버퍼 운용 메소드.
	HRESULT CreateConstBuffer(UINT size, ID3D11Buffer** ppCB);
	HRESULT CreateDynaConstBuffer(UINT size, void* pData, ID3D11Buffer** ppCB); // LPVOID -> void*
	HRESULT UpdateDynaConstBuffer(ID3D11DeviceContext* pDXDC, ID3D11Resource* pBuff, void* pData, UINT size); // LPDXDC, LPVOID -> 원본

	virtual int CreateInputLayout();
	virtual int CreateInputLayout(VertexFlag modelFlag, ID3DBlob* pVSCode);
	//virtual int CreateInputLayout_Normal();

public:
	explicit Effect();
	virtual ~Effect();

	virtual int Create(ID3D11Device* pDev, const TCHAR* filename , VertexFlag flag); // LPDEVICE -> ID3D11Device*
	virtual void Update(float dTime = 0);
	virtual void Apply(float dTime = 0);
	virtual void Release();
	virtual int UpdateConstantBuffers();
	void AddCB(std::unique_ptr<IConstBuffer> val) { m_ConstantBuffers.push_back(std::move(val)); }
	void SetSampleDesc(ID3D11SamplerState* sd) { m_Sampler_Desc = sd; }
	
	ID3D11ShaderResourceView* m_texture = nullptr;


	//virtual int UpdateCB();
	
	 virtual void SetWorld(XMMATRIX mTM);
	 virtual void SetMatrix(XMMATRIX TM);
	 virtual void SetColor(COLOR col); //일단 미정 
	 virtual void  SetView(XMMATRIX mTM);
	 virtual void  SetProj(XMMATRIX mTM);



	//멤버 접근자.
	ID3DBlob* GetVSCode() { return m_pVSCode; }            
	void* GetBufferPointer() { return m_pVSCode->GetBufferPointer(); } 
	SIZE_T GetBufferSize() { return m_pVSCode->GetBufferSize(); }


	ID3D11InputLayout* GetLayout() { return m_pLayout; }

	ID3D11VertexShader* GetVS() { return  m_pVS; }
	ID3D11PixelShader* GetPS() { return m_pPS; }
	ID3D11DeviceContext* GetContext() { return m_pDXDC; }






	template<typename T>
	T* GetConstantBuffer();

};

template<typename T>
inline T* Effect::GetConstantBuffer()
{
	const std::type_info& target_type = typeid(T);

	for (const auto& cb : m_ConstantBuffers)
	{
		if (cb->GetTypeInfo() == target_type)
		{
			return static_cast<T*>(cb.get());
		}
	}
	return nullptr;
}

