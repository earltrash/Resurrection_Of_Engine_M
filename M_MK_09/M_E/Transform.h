#pragma once
#include "pch.h"

//행렬, 계층 구조 
class Object;

class Transform 
{
public:

void Initalize();
void Update(); // Parent가 있는 경우, 해당 parent의 matrix를 통해 업데이트 

#pragma region GetSet
XMFLOAT3 Get_W_Pos() { return m_W_pos; }
XMFLOAT3 Get_W_Rot() { return m_W_rot; }
XMFLOAT3 Get_W_Scl() { return m_W_scl; }

XMFLOAT3 Get_L_Pos() { return m_L_pos; }
XMFLOAT3 Get_L_Rot() { return m_L_rot; }
XMFLOAT3 Get_L_Scl() { return m_L_scl; }

void Set_L_Pos(XMFLOAT3 NWPos) { m_L_pos = NWPos; m_ldirty = true; }
void Set_L_Rot(XMFLOAT3 NWRot) { m_L_rot = NWRot; m_ldirty = true;}
void Set_L_Scl(XMFLOAT3 NWScl) { m_L_scl = NWScl; m_ldirty = true;}

void Set_W_Pos(XMFLOAT3 NWPos) {m_W_pos = NWPos;  m_wdirty=   true;}
void Set_W_Rot(XMFLOAT3 NWRot) { m_W_rot = NWRot; m_wdirty = true;}
void Set_W_Scl(XMFLOAT3 NWScl) { m_W_scl = NWScl; m_wdirty = true;}


XMFLOAT4X4 GetLocalM() { return m_locaMatrix; }
XMFLOAT4X4 GetWorldM() { return m_worldMatrix; }

void SetLocalM(XMFLOAT4X4 NWL) { m_locaMatrix = NWL; m_ldirty = true;}
void SetWorldM(XMFLOAT4X4 NWW) { m_worldMatrix = NWW; m_wdirty = true;}

#pragma endregion


private:
	XMFLOAT4X4 m_locaMatrix;
	XMFLOAT4X4 m_worldMatrix;

	XMFLOAT3 m_L_pos = XMFLOAT3(0,0,0);
	XMFLOAT3 m_L_rot = XMFLOAT3(0,0,0);
	XMFLOAT3 m_L_scl = XMFLOAT3(1, 1, 1);

	XMFLOAT3 m_W_pos;
	XMFLOAT3 m_W_rot;
	XMFLOAT3 m_W_scl;

private:
	bool m_ldirty = false; 
	bool m_wdirty = false;
	//매 프레임마다 행렬 연산을 하기 싫어요
private:
	Object* m_Owner = nullptr;
};