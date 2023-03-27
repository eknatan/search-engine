#pragma once

#include <string>
#include <gumbo.h>

#include "parser_words.hpp"

namespace data_base
{
class Indexer;
class ParserWordsInternal : public ParserWords 
{
public:
    ParserWordsInternal(Indexer& indexer);
    void extract_words_from_html(std::string const& str_html, std::string const& url) override;

private:
    void make_gumbo(std::string const& str_html, std::string const& url) ;
    void search_for_words(GumboNode *node , std::string const& url);

private:
    Indexer& m_indexer;
};
    
} // namespace data_base
