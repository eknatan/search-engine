#include "unordered_set_safe.hpp"

namespace data_structures
{
bool UnorderedSetSafe::empty() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_unordered_Set.empty();
}

size_t UnorderedSetSafe::size() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_unordered_Set.size();
}

// std::unordered_set<std::string>::iterator UnorderedSetSafe::begin() 
// {
//     std::lock_guard<std::mutex> lock(m_mutex);
//     return m_unordered_Set.begin();
// }

// std::unordered_set<std::string>::const_iterator UnorderedSetSafe::cbegin() const
// {
//     std::lock_guard<std::mutex> lock(m_mutex);

//     return m_unordered_Set.cbegin();
// }

// std::unordered_set<std::string>::iterator UnorderedSetSafe::end() 
// {
//     std::lock_guard<std::mutex> lock(m_mutex);

//     return m_unordered_Set.end();
// }

// std::unordered_set<std::string>::const_iterator UnorderedSetSafe::cend() const
// {
//     std::lock_guard<std::mutex> lock(m_mutex);

//     return m_unordered_Set.cend();
// }

std::pair<std::unordered_set<std::string>::iterator, bool> UnorderedSetSafe::insert(std::string const& string)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_unordered_Set.insert(string);
}

std::pair<std::unordered_set<std::string>::iterator, bool> UnorderedSetSafe::insert(std::string & string)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_unordered_Set.insert(string);
}

std::unordered_set<std::string> UnorderedSetSafe::get_set() const
{
    return m_unordered_Set;
}

} // namespace data_structures
