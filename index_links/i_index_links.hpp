#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace data_base
{
    
class IIndexLinks
{
public:
    virtual ~IIndexLinks() = default;
    virtual void set(std::string const& , std::vector<std::string> const &) = 0;
    virtual std::unordered_map<std::string , std::unordered_map<std::string, double>>& copy_get_all() = 0;
    virtual size_t size() const = 0;
};

} // namespace rank_page
