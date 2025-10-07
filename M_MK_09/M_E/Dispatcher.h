#pragma once
#include "Input.h"     // InputEvent 정의 필요
#include <vector>
#include <memory>

// ListenerComponent 전방 선언 (순환 include 방지)
class ListenerComponent;

class EventDispatcher
{
public:
    EventDispatcher() = default;
    ~EventDispatcher() = default;

    void AddListener(std::shared_ptr<ListenerComponent> listener);

    void Broadcast(const InputEvent& event);
    void RemoveListener(std::shared_ptr<ListenerComponent> listener);
    void clean();

private:
    std::vector<std::weak_ptr<ListenerComponent>> m_listeners;
};
