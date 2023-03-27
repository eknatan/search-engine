#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>

#include "i_index_links.hpp"

namespace data_base
{
/**
 * @brief IndexLinks this data structures that handle all links that extract words 
 * 
 */
class IndexLinks : public IIndexLinks
{
public:
    void set(std::string const& ,std::vector<std::string> const&) override;
    std::unordered_map<std::string , std::unordered_map<std::string, double>> & copy_get_all() override;
    size_t size() const override;

private:
    std::unordered_map<std::string , std::unordered_map<std::string, double>> m_map_links;
    mutable std::mutex m_mutex;
};

} // namespace data_base