#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

namespace data_base
{
class Index
{
public:
    virtual void set(std::string const& word, std::string const& url) = 0;
    virtual void get(std::vector<std::pair<std::string, double>>& vector_result, std::string const& word) = 0;
    virtual void get(std::unordered_map<std::string, size_t>& map_result, std::string const &word) = 0;


};
    
} // namespace data_base
