#pragma once
#include "Listener.h"
#include "InputManager.h"

class MouseListenerComponent : public ListenerComponent //���ο� shared-raw-shared�� ������ ����ȭ�� ���� ����.
{
public:
		explicit MouseListenerComponent(Callback cb) : callback(std::move(cb)){}

		~MouseListenerComponent() {   InputManager::Get().m_broadcaster->RemoveListener(shared_from_this()); } //Raii

		void _OnEvent(const InputEvent& msg) override {

				if (callback) callback(msg);
		};

		bool Matches(const InputEvent& msg)const {// ���� �ִ� �޽����� �ް�
			
			return (msg.type != EventType::KeyDown && msg.type != EventType::KeyUp);
		};
private:
		Callback callback;
};
