#include "pch.h"
#include "ListenerComponent.h"
#include "InputManager.h"

void ListenerComponent::RegisterListener()
{
	
		std::shared_ptr<ListenerComponent> self = shared_from_this();
		InputManager::Get().m_broadcaster->AddListener(self);
	
}
