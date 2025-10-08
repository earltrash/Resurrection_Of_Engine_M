#pragma once
#include "Commons.h"
//StaticModel, SkinnedModel 애니 비 애니로 파생시키기
#include <unordered_map>




class Model
{
public:
	Model() = default;
	virtual ~Model(); 


	virtual int  Create(ID3D11Device* pDev, VOID* pBuff, UINT size, VertexFlag Type);
	virtual int  Update(float dTime = 0);
	virtual int  Draw(float dTime = 0, PRIMTYPE primType = PT_TRIANGLELIST, VertexFlag Type = VertexFlag::VF_POSCOL);
	virtual void Release();
	virtual void CreateVB(VOID* pBuff, UINT size, VertexFlag Type);
	const VertexFlag GetFlag() const { return m_Flag; } 

private:
	VertexFlag m_Flag = VertexFlag::VF_NONE; //draw 할떄 사용
	ID3D11Device* m_Dev = nullptr;
	ID3D11DeviceContext* m_Dct = nullptr;

	std::unordered_map<VertexFlag, Model_Prop> Data;

};



//이 클래스가 가져야하는 정보는 정점 버퍼, 
//stride나 cnt같은 정보들?