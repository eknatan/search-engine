#pragma once

#include <vector>
#include <string>

#include "searcher.hpp"

namespace data_base {class Index;}
namespace data_base {class IRankPage;}


namespace client
{
class SearcherRegular : public Searcher
{

public:
    explicit SearcherRegular(data_base::Index &, data_base::IRankPage&);
    std::vector<std::pair<std::string, double>> search(std::vector<std::string> & word) override;

private:
    void remove_unshare_between_2_results_of_words(std::vector<std::pair<std::string, double>> & vector_result, std::unordered_map<std::string, size_t>& map_temp);
    void remove_share_between_2_results_of_words(std::vector<std::pair<std::string, double>> & vector_result, std::unordered_map<std::string, size_t>const& map_temp) const;
    void check_if_first_minus(std::vector<std::string> & vector_word);
    static bool sort_second(std::pair<std::string, double>const& a, std::pair<std::string, double> const& b); 

private:
    data_base::Index& m_index;
    data_base::IRankPage& m_rank;
    size_t m_max_result = 10;
};

}