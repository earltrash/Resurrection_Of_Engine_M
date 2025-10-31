#pragma once
#include "Component.h"


class RenderComponent : public Component
{
public:
	RenderComponent() = default;
	virtual ~RenderComponent() = default;
public:
	virtual void Update() {}
	virtual void FixedUpdate(float dt) {}

public:
	virtual void Render(){};


};

