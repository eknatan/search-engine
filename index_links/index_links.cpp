#include "index_links.hpp"

#include <iostream>

namespace data_base
{

void IndexLinks::set(std::string const & source_url, std::vector<std::string> const& vector_urls)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    for(auto url : vector_urls)
        m_map_links[source_url] [url] ++;
}

std::unordered_map<std::string, std::unordered_map<std::string, double>> & IndexLinks::copy_get_all() 
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_map_links;
}

size_t IndexLinks::size() const
{   
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_map_links.size();
}

} // namespace rank_page

