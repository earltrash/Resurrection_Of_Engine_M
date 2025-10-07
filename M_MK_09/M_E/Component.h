#pragma once
class Object;

class Component
{
public:
		virtual ~Component() = default;
		virtual void Update() {}
		virtual void FixedUpdate(float dt) {}

		void SetOwner(Object* owner) { m_Owner = owner; }
		Object* m_Owner = nullptr;
};