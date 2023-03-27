#pragma once

#include <gumbo.h>
#include <optional>

#include "parser_url.hpp"


namespace data_base
{
class ParserUrlInternal : public ParserUrl
{

public:
    void create_list_links(std::string const& str_html, std::vector<std::string> &vector_url, std::string const& url, bool bounded);

private:
    void domain();
    void make_gumbo(std::string const& str_html, std::vector<std::string> & vector_url) const;
    void search_for_links(GumboNode *node, std::vector<std::string> & vector_url) const;
    std::optional<std::string> fixing_url(std::string const& url) const;

private:
    std::string m_domain;
    std::string m_url;


};

} // namespace data_base