#pragma once

//행렬, 계층 구조 
class Object;

#include "SimpleMath.h"
using namespace DirectX::SimpleMath;

class Transform 
{
public:

void Initalize();
void Update(float dTime); // Parent가 있는 경우, 해당 parent의 matrix를 통해 업데이트 

#pragma region GetSet
Vector3& Get_W_Pos() { return m_W_pos; }
Vector3& Get_W_Rot() { return m_W_rot; }
Vector3& Get_W_Scl() { return m_W_scl; }

Vector3& Get_L_Pos() { return m_L_pos; }
Vector3& Get_L_Rot() { return m_L_rot; }
Vector3& Get_L_Scl() { return m_L_scl; }

void Set_L_Pos(Vector3 NWPos) { m_L_pos = NWPos; m_ldirty = true; }
void Set_L_Rot(Vector3 NWRot) { m_L_rot = NWRot; m_ldirty = true;}
void Set_L_Scl(Vector3 NWScl) { m_L_scl = NWScl; m_ldirty = true;}

void Set_W_Pos(Vector3 NWPos) {m_W_pos = NWPos;  m_wdirty=   true;}
void Set_W_Rot(Vector3 NWRot) { m_W_rot = NWRot; m_wdirty = true;}
void Set_W_Scl(Vector3 NWScl) { m_W_scl = NWScl; m_wdirty = true;}


Matrix& GetLocalM()  { return m_locaMatrix ; }
Matrix& GetWorldM()  { return m_worldMatrix ; }

void SetLocalM(Matrix NWL) { m_locaMatrix = NWL; m_ldirty = true;}
void SetWorldM(Matrix NWW) { m_worldMatrix = NWW; m_wdirty = true;}

void SetOwner(Object* obj) { m_Owner = obj; }
#pragma endregion


private:
	Matrix m_locaMatrix;
	Matrix m_worldMatrix;

	Vector3 m_L_pos = Vector3(0,0,0);
	Vector3 m_L_rot = Vector3(0,0,0);
	Vector3 m_L_scl = Vector3(1, 1, 1);

	Vector3 m_W_pos;
	Vector3 m_W_rot;
	Vector3 m_W_scl;

private:
	bool m_ldirty = false; 
	bool m_wdirty = false;
	//매 프레임마다 행렬 연산을 하기 싫어요
private:
	Object* m_Owner = nullptr;
};