#pragma once
#include <memory>

class Object;

class Component
{
public:
		virtual ~Component() = default;
		virtual void Update() {}
		virtual void FixedUpdate(float dt) {}

		void SetOwner(std::shared_ptr<Object> owner) { m_Owner = owner; }
		std::weak_ptr<Object> GetOwner() { return m_Owner; }
		std::weak_ptr<Object> m_Owner;
};