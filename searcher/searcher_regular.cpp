#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <memory>

#include "searcher_regular.hpp"
#include "index.hpp"
#include "i_rank_page.hpp"

namespace client
{
SearcherRegular::SearcherRegular(data_base::Index &index, data_base::IRankPage& rank)
:m_index(index)
,m_rank(rank)
{
}

std::vector<std::pair<std::string, double>> SearcherRegular::search(std::vector<std::string> & vector_word)
{
    check_if_first_minus(vector_word);
  
    std::vector<std::pair<std::string, double>> vector_result;

    if(vector_word.size())
        m_index.get(vector_result, vector_word[0]);

    for(size_t i = 1 ; i <vector_word.size(); ++i)
    {
        std::unordered_map<std::string, size_t> map_temp;

        if (vector_word[i][0] != '-'){
            
            m_index.get(map_temp, vector_word[i]);
            remove_unshare_between_2_results_of_words(vector_result , map_temp);
        }
        else{
            vector_word[i].erase(0,1);
            m_index.get(map_temp, vector_word[i]);
            remove_share_between_2_results_of_words(vector_result , map_temp);
        }
    }     

    for(auto &url : vector_result)
    {
        url.second *= m_rank.get_rank(url.first);
    }

    std::sort(vector_result.begin(), vector_result.end(), sort_second);
 
    return vector_result;
}

void SearcherRegular::remove_unshare_between_2_results_of_words(std::vector<std::pair<std::string, double>> & vector_result, std::unordered_map<std::string, size_t> & map_temp) 
{
    auto begin = vector_result.begin();
    
    while(begin != vector_result.end())
    {        
        if(!map_temp.count((begin)->first) ) 
        {
            begin = vector_result.erase((begin)); 
        }
        else
        {
            (begin)->second = (map_temp[(begin)->first] < (begin)->second) ? map_temp[(begin)->first] : (begin)->second;
            ++begin;
        }
    }
}

void SearcherRegular::remove_share_between_2_results_of_words(std::vector<std::pair<std::string, double>> &vector_result, std::unordered_map<std::string, size_t> const& map_temp) const
{
    auto begin = vector_result.begin();
    
    while(begin != vector_result.end())
    {        
        if(map_temp.count((begin)->first) ) 
        {
            begin = vector_result.erase((begin)); 
        }
        else
        {
            ++begin;
        }
    }   
}

void SearcherRegular::check_if_first_minus(std::vector<std::string> &vector_word)
{
    if(vector_word[0][0] == '-')
    {   
        auto begin = vector_word.begin();
        auto end = vector_word.end();

        while(begin != end)
        {
            if((*begin)[0] != '-')
            {
                auto temp = *begin;
                *begin = vector_word[0];
                vector_word[0] = temp;
                break;
            }
            ++begin;
        }
    }
}

bool SearcherRegular::sort_second(std::pair<std::string, double> const &a, std::pair<std::string, double> const &b)
{
    return a.second > b.second;
}

}
