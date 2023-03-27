#include "rank_page.hpp"

#include "index_links.hpp"
#include "unordered_set.hpp"

#include <vector>

namespace data_base
{
RankPage::RankPage(IndexLinks & indexLinks)
:m_index_links(indexLinks)
{
}

void RankPage::update_rank()
{
    if( m_index_links.size() % 10 == 0)
    {
        run();
    }
}

void RankPage::run()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_map_urls = m_index_links.copy_get_all();

    change_map_to_divide_size_links();
        
    create_map_rank();

    size_t calculation = 10;
    while(calculation)
    {
        rank_multiplication();
        --calculation;
    }

    // for(auto& url : m_map_rank)
    // {
    //     std::cout<<url.first<<": "<<url.second<<"\n";
    // }
}

void RankPage::change_map_to_divide_size_links() 
{
    for(auto &url : m_map_urls)
    {
        double sum_links = 0;
        for(auto &inner_map_urls : url.second)
        {
            sum_links += inner_map_urls.second;
        }

        for(auto &inner_map_urls : url.second)
        {
            inner_map_urls.second /= sum_links;
        }
    }

}

void RankPage::create_map_rank()
{
    auto size_map_urls = m_map_urls.size();
    for(auto &url : m_map_urls)
    {   
        m_map_rank [url.first] = 1.0/size_map_urls;
    }
}

void RankPage::rank_multiplication()
{
    std::unordered_map<std::string, double> temp_map_rank;

    for(auto &url : m_map_urls)
    {
        for(auto &inner_map_urls : url.second)
        {
            if(m_map_rank.count(inner_map_urls.first))
            {
                temp_map_rank [inner_map_urls.first] += 0.85*m_map_rank[inner_map_urls.first]*inner_map_urls.second; 

            }
        }
    }

    double size_map_rank = temp_map_rank.size();
    for(auto url_rank : temp_map_rank)
    {
        url_rank.second += (0.15*size_map_rank);
    }

    m_map_rank = temp_map_rank;

}

double RankPage::get_rank(std::string const& url )
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_map_rank.count(url))
        return m_map_rank[url];
    else
        return 0.0;
       
}

} // namespace data_base
