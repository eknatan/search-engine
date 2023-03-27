#include <thread>

#include "queue_safe.hpp"
#include "unordered_set_safe.hpp"

#include "index_map.hpp"
#include "indexer_regular.hpp"

#include "index_links.hpp"
#include "rank_page.hpp"

#include "parser_words_internal.hpp"
#include "parser_url_internal.hpp"

#include "crawler.hpp"

#include "terminal.hpp"
#include "server.hpp"
#include "searcher_regular.hpp"

#include "application.hpp"

using namespace data_structures;
using namespace data_base;
using namespace client;


int main()
{
  //initialize data_structures
  UnorderedSetSafe set;
  QueueRegular queue;
  
  //initialize index words
  IndexMap index_map;
  IndexerRegular indexer(index_map);

  //initialize index urls
  IndexLinks index_links;  
  RankPage rank(index_links);
  
  //initialize parser url and words
  ParserUrlInternal parser_url;
  ParserWordsInternal parser_word(indexer);
  
  //initialize crawler to site
  Crawler crawler(parser_word, parser_url, indexer, index_links, rank ,queue, set);
  
  //initialize input_output
  SearcherRegular searcher(index_map, rank);
  Terminal input_terminal(searcher);
  Server input_server(searcher);
  
  // initialize application search and configuration 
  Application application(crawler, input_terminal, input_server, "configuration.txt");
    
  // activates terminal and server search options 
  application.run();
    
  return 0;
}