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

                // 1. weak_ptr를 shared_ptr로 잠금(lock) 시도
                if (auto listener = wptr.lock()) {

                    // 2. 잠금 성공: 객체가 살아있으므로 안전하게 접근하여 처리
                    if (listener->Matches(event)) {
                        listener->_OnEvent(event);
                    }

                    return false; // 살아있으므로 목록에서 제거하지 않음
                }

                // 3. 잠금 실패: 객체가 이미 소멸됨 (USE-AFTER-FREE 방지)
                return true; // 이 weak_ptr를 목록에서 제거 (만료된 객체 청소)
            }),
        m_listeners.end());
}

void EventDispatcher::RemoveListener(std::shared_ptr<ListenerComponent> listener)
{
    m_listeners.erase(
        std::remove_if(m_listeners.begin(), m_listeners.end(),
            [&listener](const std::weak_ptr<ListenerComponent>& wptr) {

                // 1. 소유권 비교를 통해 wptr가 listener_to_remove와 동일한 객체를 가리키는지 확인합니다.
                //    (nullptr과의 비교가 아닌, Control Block을 기반으로 비교합니다.)
                bool same_object = wptr.owner_before(listener) == false &&
                    listener.owner_before(wptr) == false;

                // 2. 동일한 객체를 찾았다면 (true), 제거 대상이 되도록 true를 반환합니다.
                return same_object;
            }),
        m_listeners.end());
}

void EventDispatcher::clean()
{
    m_listeners.clear();
}
