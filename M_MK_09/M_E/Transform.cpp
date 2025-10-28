#include "pch.h"

#include "Transform.h"
#include "Object.h"


//�ش� Transform�� ���� Update ȣ���� Component���� ���� ȣ��� ����. 
//����, ���� -> ������ ���� ��ġ ������ ������ �ϴ� ������Ʈ���� Transform�� ��� ����. 
//super::Update�� ���� Transform�� ������Ʈ �ϰ�, �ڽ� ������Ʈ���� ������Ʈ �ϴ� ����..
//���������� APP���� ������Ʈ�� ���� -> Ccmponent���� ������Ʈ �ϴ� �������� ó��.
//�׷��� ������. ����, ������ ���� Transform�� ������Ʈ ������ �� �ֵ��� flag�� ���� 
//��� ���꿡 ���� �δ��� ���̵��� ��. 
//flag�� �ٰŴ� �̵� (�Է��� ���ؼ��� ����) 


void Transform::Update() //DX HELPER�� WRAPPING �ϱ� ����..
{
	if (m_ldirty)
	{
		//�ͼ��� Yena�� ��....
		XMMATRIX Translation = XMMatrixTranslation(m_L_pos.x, m_L_pos.y, m_L_pos.z);
		XMMATRIX Rotation = XMMatrixRotationRollPitchYaw(m_L_rot.x, m_L_rot.y, m_L_rot.z);
		XMMATRIX Scaling = XMMatrixScaling(m_L_scl.x, m_L_scl.y, m_L_scl.z);
		XMMATRIX Local_MATRIX = Scaling * Rotation * Translation;
		XMStoreFloat4x4(&m_locaMatrix, Local_MATRIX);
		

		Object* parent = m_Owner->GetParent().lock().get(); //��ȿ�� �˻�� lock ������

		if(parent != nullptr)
		{
			XMFLOAT4X4 P_W = parent->GetTransform().GetWorldM();

			XMMATRIX Parent_World_Matrix = XMLoadFloat4x4(&P_W);

			XMMATRIX WORLD = Local_MATRIX * Parent_World_Matrix;

			XMStoreFloat4x4(&m_worldMatrix, WORLD);

			
		}
		else //������ �� ���� 
		{
			m_worldMatrix = m_locaMatrix;
		}
	} 

}



