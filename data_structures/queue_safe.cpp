#include "queue_safe.hpp"

#include <mutex>
#include <condition_variable>

namespace data_structures
{   
/**
 * @brief the function return front queue and out from queue front
 * 
 * @return std::string from queue front
 */
std::string QueueRegular::pop()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while(m_queue.size() == 0)
    {
        m_not_empty.wait(lock);
    }
    auto temp = m_queue.front();
    m_queue.pop();
    return temp;
}

/**
 * @brief the function insert to queue and notify all that queue not empty 
 * 
 * @param value this value is a string that he puts into the queue 
 */
void QueueRegular::push(std::string const& value)
{

    std::lock_guard<std::mutex> lock(m_mutex);
    m_queue.push(value);
    m_not_empty.notify_all();
}

size_t QueueRegular::size() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.size();
}

bool QueueRegular::empty() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.empty();
}

std::string QueueRegular::front() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.front(); 
}

std::string QueueRegular::back() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.back();
}
} // namespace data_structures
