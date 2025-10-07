#pragma once
#include <memory>
#include <vector>
#include "Component.h"
#include "Listener.h"

class Object 
{
public:
	Object() {}
	virtual ~Object() { m_Components.clear(); }
		

		virtual void Update() 
		{
			for (auto& obj : m_Components)
			{
				obj->Update();
			}
		};

		virtual void FixedUpdate(float dt) 
		{
			for (auto& obj : m_Components)
			{
				obj->FixedUpdate(dt);
			}
		}

		virtual void Render() {}; //ecs 참고를 해볼까 

		void SetActive(bool b) { activated = b; };
		bool isActive() { return activated; }
public:
		
		

public:

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args);
		template<typename T>
		T* GetComponent() const;
		void ComponentClear() { m_Components.clear(); }

protected:

		std::vector<std::shared_ptr<Component>> m_Components;		
		bool activated = true;
};

#pragma region Component
template<typename T, typename ...Args>
inline T* Object::AddComponent(Args && ...args)
{
		static_assert(std::is_base_of<Component, T>::value, "Component의 자식이어야 한다는 거임 ");

		auto comp = std::make_shared<T>(std::forward<Args>(args)...);

		comp->SetOwner(this);

		T* ptr = comp.get();

		m_Components.emplace_back(comp);

		if (auto listener = std::dynamic_pointer_cast<ListenerComponent>(comp))
		{
			listener->RegisterListener();
		}

		return ptr;
}

template<typename T>
inline T* Object::GetComponent() const 
{
		for (auto& com : m_Components)
		{
				if (auto ptr = dynamic_cast<T*>(com.get()))
				{
						return ptr;
				}
		}

		return nullptr;
}

#pragma endregion
