#pragma once
#include "InputManager.h"

#include "Component.h"
#include <memory>
#include <functional>

using Callback = std::function<void(const InputEvent&)>;
using namespace std;

class ListenerComponent : public Component, public std::enable_shared_from_this<ListenerComponent>
{
public:
		ListenerComponent() = default;
		virtual ~ListenerComponent() = default;

		virtual void _OnEvent(const InputEvent& msg) {}
		virtual bool Matches(const InputEvent& msg) const = 0;  // 관심 있는 메시지만 받게


		virtual void RegisterListener()
		{
			std::shared_ptr<ListenerComponent> self = shared_from_this();
			InputManager::Get().m_broadcaster->AddListener(self);
		}

};
