#pragma once
#include "Input.h"     // InputEvent ���� �ʿ�
#include <vector>
#include <memory>

// ListenerComponent ���� ���� (��ȯ include ����)
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
