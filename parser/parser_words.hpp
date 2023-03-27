#pragma once

#include <string>

namespace data_base
{
class ParserWords
{
public:

    virtual ~ParserWords() = default;

    virtual void extract_words_from_html(std::string const& str_html, std::string const& url) = 0;

};
    
} // namespace data_base