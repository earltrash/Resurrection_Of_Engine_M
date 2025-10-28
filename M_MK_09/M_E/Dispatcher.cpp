#include "pch.h"
#include "Dispatcher.h"
#include "ListenerComponent.h"  

void EventDispatcher::AddListener(std::shared_ptr<ListenerComponent> listener)
{
    m_listeners.push_back(listener);
}

void EventDispatcher::Broadcast(const InputEvent& event)
{
    m_listeners.erase(
        std::remove_if(m_listeners.begin(), m_listeners.end(),
            [&event](std::weak_ptr<ListenerComponent>& wptr) {

                // 1. weak_ptr�� shared_ptr�� ���(lock) �õ�
                if (auto listener = wptr.lock()) {

                    // 2. ��� ����: ��ü�� ��������Ƿ� �����ϰ� �����Ͽ� ó��
                    if (listener->Matches(event)) {
                        listener->_OnEvent(event);
                    }

                    return false; // ��������Ƿ� ��Ͽ��� �������� ����
                }

                // 3. ��� ����: ��ü�� �̹� �Ҹ�� (USE-AFTER-FREE ����)
                return true; // �� weak_ptr�� ��Ͽ��� ���� (����� ��ü û��)
            }),
        m_listeners.end());
}

void EventDispatcher::RemoveListener(std::shared_ptr<ListenerComponent> listener)
{
    m_listeners.erase(
        std::remove_if(m_listeners.begin(), m_listeners.end(),
            [&listener](const std::weak_ptr<ListenerComponent>& wptr) {

                // 1. ������ �񱳸� ���� wptr�� listener_to_remove�� ������ ��ü�� ����Ű���� Ȯ���մϴ�.
                //    (nullptr���� �񱳰� �ƴ�, Control Block�� ������� ���մϴ�.)
                bool same_object = wptr.owner_before(listener) == false &&
                    listener.owner_before(wptr) == false;

                // 2. ������ ��ü�� ã�Ҵٸ� (true), ���� ����� �ǵ��� true�� ��ȯ�մϴ�.
                return same_object;
            }),
        m_listeners.end());
}

void EventDispatcher::clean()
{
    m_listeners.clear();
}
