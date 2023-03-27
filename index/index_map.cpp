#include "index_map.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <mutex>

namespace data_base
{
/**
 * @brief insert word into unordered map of index word
 * 
 * @param word this word that extract from html of url, 
 * @param url This is the link where the word is
 */
void IndexMap::set(std::string const& word, std::string const& url)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_map[word] [url] +=1;
}

/**
 * @brief gets into a vector the links he found for the word
 * 
 * @param vector_result this vector of links, that the word exists in him
 * @param word this word find
 */
void IndexMap::get(std::vector<std::pair<std::string, double>> & vector_result, std::string const& word)
{
    auto begin = m_map[word].begin();
    auto end = m_map[word].end();
  
    while(begin != end)
    {
        vector_result.push_back(*begin);
        ++begin;
    }

}

/**
 * @brief gets into a map the links he found for the word, 
 * 
 * @param map_result this map of links, that the word exists in him
 * @param word this word find
 */
void IndexMap::get(std::unordered_map<std::string, size_t>& map_result, std::string const &word)
{
    auto begin = m_map[word].begin();
    auto end = m_map[word].end();

    while(begin != end)
    {
        map_result.insert(*begin);
        ++begin;
    }
}

} // namespace data_base
