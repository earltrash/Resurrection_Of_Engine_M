#pragma once
#include "Commons.h"

class Model
{
public:
	Model() = default;
	virtual ~Model(); 


	virtual int  Create(ID3D11Device* pDev, VOID* pBuff, UINT size, VertexFlag Type);
	virtual int  Update(float dTime = 0);
	virtual int  Draw(float dTime = 0, PRIMTYPE primType = PT_TRIANGLELIST, VertexFlag Type = VertexFlag::VF_NONE);
	virtual void Release();
	virtual void CreateVB(VOID* pBuff, UINT size, VertexFlag Type);
	VertexFlag GetFlag()  { return m_Flag; } 

private:
	VertexFlag m_Flag = VertexFlag::VF_NONE; //draw �ҋ� ���
	ID3D11Device* m_Dev = nullptr;
	ID3D11DeviceContext* m_Dct = nullptr;

	std::unordered_map<VertexFlag, Model_Prop> Data; //�̷��� ������ ������� mapping ���� 

};



//�� Ŭ������ �������ϴ� ������ ���� ����, 
//stride�� cnt���� ������?