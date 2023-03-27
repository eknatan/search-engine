#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <vector>
#include <mutex>

#include "i_rank_page.hpp"

namespace data_structures
{
class UnorderedSet;
}

namespace data_base
{
class IndexLinks;

class RankPage : public IRankPage
{
public:
    explicit RankPage(IndexLinks& );
    void update_rank() override;
    double get_rank(std::string const&) override;


private:
    void run();
    void change_map_to_divide_size_links();
    void create_map_rank();
    void rank_multiplication();

private:
    IndexLinks& m_index_links;
    std::unordered_map<std::string, std::unordered_map<std::string, double>> m_map_urls;
    std::unordered_map<std::string, double> m_map_rank;


    mutable std::mutex m_mutex;


};
    
} // namespace data_base