#pragma once
#include "Component.h"

class RenderComponent : public Component 
{
public:
	RenderComponent() = default;
	virtual ~RenderComponent() = default;
public:
	virtual void Update(float dt);
	virtual void FixedUpdate(float dt);
	//virtual void GetModel(std::string Path); //template으로 받아버려? -> 일단 발전의 기회로.
public:
	virtual void Render();
};

