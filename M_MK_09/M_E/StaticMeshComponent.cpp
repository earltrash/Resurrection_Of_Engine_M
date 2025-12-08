#pragma once
#include "StaticMeshComponent.h"
#include "DX_Renderer.h"
#include "ResourceManager.h"
#include "Model.h"

//DXRenderer가 갖고있는 List에 이걸 넣음. // 
//

//component를 주는 게 나으려나, 위치 정보를 어떻게 넘기지. 

void StaticMeshComponent::Render()
{
	
}

void StaticMeshComponent::Update(float dTime)
{
	RenderComponent::Update(dTime);

}

void StaticMeshComponent::FixedUpdate(float dTime)
{
}


//엔진에서 하는게 맞긴 하죠 
void StaticMeshComponent::SetModel(std::string Path)
{


	m_p_model = ResourceManager::Instance().GetModelResource()->GetModel(Path);

}

Model* StaticMeshComponent::GetModel()
{
	if (m_p_model)
		return m_p_model;

	else return nullptr;
		
}
