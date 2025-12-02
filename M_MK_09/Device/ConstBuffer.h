#pragma once
#include "IConsttBuffer.h"

using namespace DirectX;



struct cbMatrix_4
{
	XMMATRIX mTM;			
	XMMATRIX mView;						
	XMMATRIX mProj;		

	XMMATRIX mW;

	XMVECTOR COL;

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
	XMVECTOR Ambient = { 1,1,1,1 }; ;		//!< 보조 광량(주변광) 의 반사율(%) 
	XMVECTOR Spec = { 1,1,1,1 }; ;
	FLOAT    Power = 30.f;
};

//구조체 타입은 따로 빼는 것도 나쁘지 않을 듯. -> 차피, 

class cbDEFAULT : public IConstBuffer
{
public:
	cbDEFAULT() = default;
	~cbDEFAULT() = default;

	HRESULT Create(ID3D11Device* pDev);
	HRESULT Update(ID3D11DeviceContext*pDXDC);
	ID3D11Buffer* GetBuffer() const { return m_pD3DBuffer; }
	UINT GetRegisterSlot() const { return m_RegisterSlot; }

	void SetWorld(XMMATRIX& TM) { matrix.mTM = TM; }

	void SetView(XMMATRIX& TM) { matrix.mView = TM; }
	void SetProj(XMMATRIX& TM) { matrix.mProj = TM; }
	void SetTM(XMMATRIX& TM) { matrix.mTM = TM; }
	const std::type_info& GetTypeInfo() const override { return typeid(cbDEFAULT); }

private:
	ID3D11Buffer* m_pD3DBuffer;
	UINT m_RegisterSlot = static_cast<int>(e_CB::CB_DEFAULT);

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
	UINT m_RegisterSlot = static_cast<int>(e_CB::CB_LIGHT);


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
	ID3D11Buffer* GetBuffer() const override { return m_pD3DBuffer; }
	UINT GetRegisterSlot() const override  { return m_RegisterSlot; }
	const std::type_info& GetTypeInfo() const override { return typeid(cbMATERIAL); } 

	void Set_Mat_Ambi(XMVECTOR& val) { material.Ambient = val; }
	void Set_Mat_Ambi(XMFLOAT4 val) { material.Ambient = XMLoadFloat4(&val); }

	void Set_Mat_Dif(XMVECTOR& val) { material.Diffuse = val; }
	void Set_Mat_Dif(XMFLOAT4 val) { material.Diffuse = XMLoadFloat4(&val); }

	void Set_Mat_Spc(XMVECTOR& val) { material.Spec = val; }
	void Set_Mat_Spc(XMFLOAT4 val) { material.Spec = XMLoadFloat4(&val); }

	void Set_Mat_Pw(float val) { material.Power = val; }


private:
	ID3D11Buffer* m_pD3DBuffer;
	UINT m_RegisterSlot = static_cast<int>(e_CB::CB_MATERIAL);


private:

	cbMAT material;
};




#pragma region Type_Traits

template <typename T>
struct CB_Type_Traits;

template<>
struct CB_Type_Traits<cbDEFAULT>
{
	static constexpr e_CB Type = e_CB::CB_DEFAULT;
};

template<>
struct CB_Type_Traits<cbLIGHT>
{
	static constexpr e_CB Type = e_CB::CB_LIGHT;
};

template <>
struct CB_Type_Traits<cbMATERIAL> {
	static constexpr e_CB Type = e_CB::CB_MATERIAL;
};

#pragma endregion
