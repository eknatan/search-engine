#pragma once

#include <gumbo.h>

namespace data_base
{
class ParserUrl
{
public:

    virtual ~ParserUrl() = default;

    virtual void create_list_links(std::string const& str_html, std::vector<std::string> &vector_url, std::string const& url, bool bounded) = 0;
};
    
} // namespace data_base
