#include "pch.h"
#include "Model.h"
#include "Material.h"
#include "Mesh.h"

void Model::Render(ID3D11DeviceContext* DXDC)
{
	for (auto& part : m_Parts)
	{
		if (part.material) 
		part.material->Bind(DXDC);

		if (part.mesh)
		part.mesh->Render(DXDC);

	}

}
