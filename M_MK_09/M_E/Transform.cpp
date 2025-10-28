#include "pch.h"

#include "Transform.h"
#include "Object.h"


//해당 Transform에 대한 Update 호출은 Component들을 통해 호출될 예정. 
//물리, 렌더 -> 행위를 위해 위치 정보를 가져야 하는 컴포넌트들은 Transform을 상속 받음. 
//super::Update를 통해 Transform을 업데이트 하고, 자식 컴포넌트들을 업데이트 하는 형식..
//전반적으로 APP에서 오브젝트에 접근 -> Ccmponent들을 업데이트 하는 형식으로 처리.
//그렇기 때문에. 물리, 렌더와 같은 Transform의 업데이트 권한을 쥔 애들은 flag를 통해 
//행렬 연산에 대한 부담을 줄이도록 함. 
//flag의 근거는 이동 (입력을 통해서든 뭐든) 


void Transform::Update() //DX HELPER로 WRAPPING 하기 귀찮..
{
	if (m_ldirty)
	{
		//익숙한 Yena의 맛....
		XMMATRIX Translation = XMMatrixTranslation(m_L_pos.x, m_L_pos.y, m_L_pos.z);
		XMMATRIX Rotation = XMMatrixRotationRollPitchYaw(m_L_rot.x, m_L_rot.y, m_L_rot.z);
		XMMATRIX Scaling = XMMatrixScaling(m_L_scl.x, m_L_scl.y, m_L_scl.z);
		XMMATRIX Local_MATRIX = Scaling * Rotation * Translation;
		XMStoreFloat4x4(&m_locaMatrix, Local_MATRIX);
		

		Object* parent = m_Owner->GetParent().lock().get(); //유효성 검사는 lock 선에서

		if(parent != nullptr)
		{
			XMFLOAT4X4 P_W = parent->GetTransform().GetWorldM();

			XMMATRIX Parent_World_Matrix = XMLoadFloat4x4(&P_W);

			XMMATRIX WORLD = Local_MATRIX * Parent_World_Matrix;

			XMStoreFloat4x4(&m_worldMatrix, WORLD);

			
		}
		else //로컬이 즉 월드 
		{
			m_worldMatrix = m_locaMatrix;
		}
	} 

}



