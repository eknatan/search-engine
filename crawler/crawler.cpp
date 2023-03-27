#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include "indexer.hpp"
#include "parser_url.hpp"
#include "parser_words.hpp"
#include "index_links.hpp"
#include "i_rank_page.hpp"

#include "queue.hpp"
#include "unordered_set.hpp"

#include "crawler.hpp"

namespace data_base
{

Crawler::Crawler(ParserWords & ParserWords, ParserUrl & ParserUrl, Indexer& Indexer, IndexLinks& index_links, IRankPage& rank, data_structures::Queue & queue, data_structures::UnorderedSet & set)
:m_parser_words(ParserWords)
,m_parser_url(ParserUrl)
,m_indexer(Indexer)
,m_index_links(index_links)
,m_rank(rank)
,m_queue(queue)
,m_set_links(set)
{
    
}

void Crawler::crawler(std::string const &url, bool bounded, size_t max_crawler)
{   
    m_max_crawler = max_crawler;

    m_set_links.insert(url);
    m_queue.push(url);  
   
    std::vector<std::thread> threads;
    auto lambda_crawler = [this](size_t id_thread, bool bounded){this->thread_crawler(id_thread, bounded); std::cout<<"finish\n";}; 
        
    for(size_t i = 0 ; i < 10 ; ++i)
    {
        m_mode_threads.push_back(true);
        threads.push_back(std::thread(lambda_crawler,i, bounded));
    }

    for(auto &thread : threads)
    {
        thread.join();
    }
}

void Crawler::thread_crawler(size_t id_thread, bool bounded)
{   
    while(m_sum_link <= m_max_crawler && (mode_threads() || !m_queue.empty()))
    {
        auto url_local =  m_queue.pop();
        m_sum_link++;

        std::string str_html;
        set_html_from_url(url_local, str_html);
        
        if(str_html.size())
        {
            m_parser_words.extract_words_from_html(str_html, url_local);

            std::vector<std::string> vector;
            m_parser_url.create_list_links(str_html, vector, url_local ,bounded);

            m_index_links.set(url_local, vector);

            bool mode_thread = false;
            if (vector.size())
                mode_thread = true;

            insert_queue(vector);

            m_mode_threads[id_thread] = mode_thread;
        }
        m_rank.update_rank();
        
    }   
}

void Crawler::set_html_from_url(std::string const &url, std::string &str_html) const
{

    try
    {
        curlpp::Cleanup myCleanup;
        curlpp::Easy myRequest;

        myRequest.setOpt<curlpp::options::Url>(url);
        myRequest.setOpt(curlpp::options::WriteFunction([&](char *data, size_t size, size_t nmemb) 
        {
            str_html.append(data, size * nmemb);
            return size * nmemb;
        }));

        myRequest.perform();
    }

    catch ( curlpp::LogicError & e )
	{
        std::cout<<"bad link logic\n";
	}

	catch ( curlpp::RuntimeError & e )
	{
	        std::cout<<"bad link runtime: "<<url<<"\n";
	}
}

void Crawler::insert_queue(std::vector<std::string> const& vector)
{
    auto size = vector.size();
    for (size_t i = 0; i < size; i++)
    {
        if(m_set_links.insert(vector[i]).second)
        {
            m_queue.push(vector[i]);
        }
    }
}

bool Crawler::mode_threads() const
{
    for( auto thread : m_mode_threads)
    {
        if (thread)
        {
            return true;
        }
    }
    return false;
}

} // namespace data_base
