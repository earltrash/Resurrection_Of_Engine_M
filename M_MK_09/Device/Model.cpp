#include "pch.h"

#include "Model.h"
#include "Material.h"

//�̰� �ϳ� ����... ��. 
void Model::Render(ID3D11DeviceContext* DXDC)
{
	DXDC->IASetVertexBuffers(0, 1, &m_Mesh->m_Vertexbuffer, &m_Mesh->m_Stride, &m_Mesh->m_Offset);
	DXDC->Draw(m_Mesh->m_VtxCnt, 0);
}
