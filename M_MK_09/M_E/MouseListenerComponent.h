#pragma once
#include "Listener.h"
#include "InputManager.h"

class MouseListenerComponent : public ListenerComponent //새로운 shared-raw-shared로 소유권 이중화를 막기 위함.
{
public:
		explicit MouseListenerComponent(Callback cb) : callback(std::move(cb)){}

		~MouseListenerComponent() {   InputManager::Get().m_broadcaster->RemoveListener(shared_from_this()); } //Raii

		void _OnEvent(const InputEvent& msg) override {

				if (callback) callback(msg);
		};

		bool Matches(const InputEvent& msg)const {// 관심 있는 메시지만 받게
			
			return (msg.type != EventType::KeyDown && msg.type != EventType::KeyUp);
		};
private:
		Callback callback;
};
