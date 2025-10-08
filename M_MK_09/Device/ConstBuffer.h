#pragma once
#include "IConsttBuffer.h"
#include "DirectXMath.h"

using namespace DirectX;




struct cbMatrix_4
{
	XMMATRIX mTM;			
	XMMATRIX mView;						
	XMMATRIX mProj;			
	XMMATRIX mW;

	XMFLOAT4 Color; //뭐 안 읽으면 되는거 아닌가? 음......... 고민좀 해보자 
};
struct cbLT
{
	XMVECTOR Direction;		//!< 빛의 방향.
	XMVECTOR Diffuse;		//!< 주 광량 : 확산광 Diffuse Light.
	XMVECTOR Ambient;		//!< 보조 광량 : 주변광 Ambient Light.
	FLOAT    Range;			//!< 빛 도달 거리.
	BOOL	 LitOn;			//!< 조명 적용여부.
};
struct cbMAT
{
	XMVECTOR Diffuse = { 1,1,1,1 };		//!< 주 광량(확산광) 의 반사율(%) 
	XMVECTOR Ambient;		//!< 보조 광량(주변광) 의 반사율(%) 
};




//그럼 타입에 따라서 업데이트 해야하는 상수 버퍼를 나누는 형식으로 해야 겠네 

struct ConstBuffer_ANI
{
	XMFLOAT4X4 mTM;				//!< "World" 변환 행렬 변수 : DirectXMath, 비정렬, SIMD 비가속, 일반 저장용. 
	XMFLOAT4X4 mView;			//!< "View" 변환 행렬 변수 
	XMFLOAT4X4 mProj;			//!< "Projection" 변환 행렬 변수
	XMFLOAT4X4 mWVP;			//!< "World+View+Projection" 변환 행렬 변수

	XMFLOAT4 col;
	float  aniT;
};

typedef ConstBuffer_ANI	CBuffer_Ani;

class cbDEFAULT : public IConstBuffer
{
public:
	cbDEFAULT() = default;
	~cbDEFAULT() = default;

	HRESULT Create(ID3D11Device* pDev);
	HRESULT Update(ID3D11DeviceContext*pDXDC);
	ID3D11Buffer* GetBuffer() const { return m_pD3DBuffer; }
	UINT GetRegisterSlot() const { return m_RegisterSlot; }

	void SetWorld(XMMATRIX& TM) { matrix.mW = TM; }

	void SetView(XMMATRIX& TM) { matrix.mView = TM; }
	void SetProj(XMMATRIX& TM) { matrix.mProj = TM; }
	void SetTM(XMMATRIX& TM) { matrix.mTM = TM; }

	const std::type_info& GetTypeInfo() const override { return typeid(cbDEFAULT); }
	void SetColor(XMFLOAT4 col) { matrix.Color = col; }
private:
	ID3D11Buffer* m_pD3DBuffer;
	UINT m_RegisterSlot = 0;

private:
	cbMatrix_4 matrix;
};

class cbLIGHT : public IConstBuffer
{
public:

	cbLIGHT() = default;
	virtual ~cbLIGHT() = default;

	HRESULT Create(ID3D11Device* pDev);
	HRESULT Update(ID3D11DeviceContext* pDXDC);
	ID3D11Buffer* GetBuffer() const { return m_pD3DBuffer; }
	UINT GetRegisterSlot() const { return m_RegisterSlot; }

	void SetLightDir(XMVECTOR& val) { light.Direction = val; }
	void SetDiffuse(XMVECTOR& val) { light.Diffuse = val; }
	void SetAmbient(XMVECTOR& val) { light.Ambient = val; }
	void SetLightRange(FLOAT& val) { light.Range = val; }
	void LightOn(BOOL val) { light.LitOn = val; }

	void SetLight(cbLT& LIGHT) { light = LIGHT; }

	const std::type_info& GetTypeInfo() const override { return typeid(cbLIGHT); }
private:
	ID3D11Buffer* m_pD3DBuffer;
	UINT m_RegisterSlot = 1;


private:
	cbLT light;
};


class cbMATERIAL :public  IConstBuffer
{

public:

	cbMATERIAL() = default;
	virtual ~cbMATERIAL() = default;

	HRESULT Create(ID3D11Device* pDev);
	HRESULT Update(ID3D11DeviceContext* pDXDC);
	ID3D11Buffer* GetBuffer() const { return m_pD3DBuffer; }
	UINT GetRegisterSlot() const { return m_RegisterSlot; }

	void Set_Mat_Ambi(XMVECTOR& val) { material.Ambient = val; }
	void Set_Mat_Dif(XMVECTOR& val) { material.Diffuse = val; }
	const std::type_info& GetTypeInfo() const override { return typeid(cbMATERIAL); }

private:
	ID3D11Buffer* m_pD3DBuffer;
	UINT m_RegisterSlot = 3;


private:

	cbMAT material;
};
