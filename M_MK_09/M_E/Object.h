#pragma once
#include "Component.h"
#include "ListenerComponent.h" //이거 고칠 수 있으면 고쳐보자. 너무 이상해
#include "Transform.h"

class Object : public std::enable_shared_from_this<Object>
{
public:
	Object() { m_transform.SetOwner(this); }
	virtual ~Object() { m_Components.clear(); }
		

		virtual void Update(float dTime) 
		{
			GetTransform().Update(dTime);
			
			for (auto& cmp : m_Components)
			{
				cmp->Update(dTime);
			}


		};

		virtual void FixedUpdate(float dt) 
		{
			for (auto& obj : m_Components)
			{
				obj->FixedUpdate(dt);
			}
		}

	

		void SetPosition(XMFLOAT3 position);
		void SetRotation(XMFLOAT3 rotation);
		void SetScale(XMFLOAT3 scale);
		
		XMFLOAT3 Get_L_Pos();
		XMFLOAT3 Get_L_Rot();
		XMFLOAT3 Get_L_Scl();

		XMFLOAT3 Get_W_Pos();
		XMFLOAT3 Get_W_Rot();
		XMFLOAT3 Get_W_Scl();


		void SetParent(shared_ptr<Object> parent);
		weak_ptr<Object> GetParent();
		 Transform GetTransform();  
public:
	
		template<typename T, typename... Args>
		T* AddComponent(Args&&... args);
		template<typename T>
		T* GetComponent() const;
		void ComponentClear() { m_Components.clear(); }

protected:
  weak_ptr<Object> m_parent;
  std::vector<std::shared_ptr<Component>> m_Components;		
  Transform m_transform;
  

};

#pragma region Component
template<typename T, typename ...Args>
inline T* Object::AddComponent(Args && ...args)
{
		static_assert(std::is_base_of<Component, T>::value, "Component의 자식이어야 한다는 거임 ");

		auto comp = std::make_shared<T>(std::forward<Args>(args)...);

		comp->Component::SetOwner(shared_from_this());

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
