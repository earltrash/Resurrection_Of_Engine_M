#include "pch.h"
#include "RenderComponent.h"

void RenderComponent::Update(float dt)
{
}

void RenderComponent::FixedUpdate(float dt)
{
	Transform::Update(dt);
}

void RenderComponent::Render()
{
}
