#pragma once

#include <string>
#include <queue>
#include <unordered_set>
#include <mutex>
#include <atomic>

#include "i_crawler.hpp"

namespace data_structures{
class Queue;
class UnorderedSet;
}

namespace data_base
{
class ParserWords;
class ParserUrl;
class Indexer;
class IndexLinks;
class IRankPage;

class Crawler : public ICrawler
{
public:
    Crawler(ParserWords&, ParserUrl&, Indexer&, IndexLinks&, IRankPage&  ,data_structures::Queue&, data_structures::UnorderedSet& );
    
    void crawler(std::string const& url, bool bounded, size_t max_crawler) override;

private:
    void thread_crawler(size_t id_thread, bool bounded);
    void set_html_from_url(std::string const& url, std::string & str_html) const;
    void insert_queue(std::vector<std::string> const& vector_url);
    bool mode_threads() const;

private:
    ParserWords& m_parser_words;
    ParserUrl& m_parser_url;
    Indexer& m_indexer;
    IndexLinks& m_index_links;
    IRankPage& m_rank;

    data_structures::Queue & m_queue;
    data_structures::UnorderedSet& m_set_links;
   
    std::atomic<size_t> m_max_crawler;

    std::atomic<size_t> m_sum_link = 0;
    std::vector<bool> m_mode_threads;

    mutable std::mutex m_mutex;
};
    
} // namespace data_base
