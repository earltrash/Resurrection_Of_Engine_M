#pragma once
#include "ListenerComponent.h"
#include "InputManager.h"


class KeyListenerComponent : public ListenerComponent
{
public:
		explicit KeyListenerComponent(Callback cb) : callback(std::move(cb)) {}
		~KeyListenerComponent() {
			InputManager::Get().m_broadcaster->RemoveListener(shared_from_this());} //Raii


		void _OnEvent(const InputEvent& msg) override {
				if (callback) callback(msg);
				return;
		};
		bool Matches(const InputEvent& msg)const 
		{
			return (msg.type == EventType::KeyDown || msg.type == EventType::KeyUp);
		};  
private:
		Callback callback;

};