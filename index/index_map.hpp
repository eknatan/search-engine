#pragma once

#include <unordered_map>
#include <string>
#include <mutex>

#include "index.hpp"


namespace data_base
{

/**
 * @brief object IndexMap handle all words from html in unordered map
 */
class IndexMap : public Index
{
public:
    void set(std::string const& word, std::string const& url);
    void get(std::vector<std::pair<std::string, double>> &, std::string const& );
    void get(std::unordered_map<std::string, size_t>& , std::string const &);

private:   
    std::unordered_map<std::string , std::unordered_map<std::string, double>> m_map;
    mutable std::mutex m_mutex;

};
    
} // namespace data_base