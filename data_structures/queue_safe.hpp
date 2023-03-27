#pragma once

#include <queue>
#include <mutex>
#include <string>
#include <condition_variable>

#include "queue.hpp"

namespace data_structures
{
class QueueRegular : public Queue
{
public:

    std::string pop() override;
    void push(std::string const&) override;
    size_t size() const override;
    bool empty() const override;
    std::string front() const override;
    std::string back() const override;

private:
    std::queue<std::string> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_not_empty;

};    
    
} // namespace data_structures