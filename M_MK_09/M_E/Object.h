#pragma once
#include "Component.h"
#include "ListenerComponent.h" //�̰� ��ĥ �� ������ ���ĺ���. �ʹ� �̻���
#include "Transform.h"

//class Transform;

//���� ���� 
#include "Effect.h"

class Object : public std::enable_shared_from_this<Object>
	//Transform�� �ڽ����� �ϰ�, Local Position�� �����ϰ� �ϴ� wrwapping�� �ʿ���. 
{
public:
	Object() {}
	virtual ~Object() { m_Components.clear(); }
		

		virtual void Update() 
		{
			for (auto& cmp : m_Components)
			{
				cmp->Update();
			}


			m_effect->Update(); //�ӽ�

		};

		virtual void FixedUpdate(float dt) 
		{
			for (auto& obj : m_Components)
			{
				obj->FixedUpdate(dt);
			}
		}

		virtual void Render() 
		{
			//�ӽ�
			//m_effect->Apply(); //update���� ���� ��
		}; 

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
		
	//�� ģ���� ���� ������Ʈ �� 
	Effect* m_effect = nullptr;

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
		static_assert(std::is_base_of<Component, T>::value, "Component�� �ڽ��̾�� �Ѵٴ� ���� ");

		auto comp = std::make_shared<T>(std::forward<Args>(args)...);

		comp->SetOwner(shared_from_this());

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
