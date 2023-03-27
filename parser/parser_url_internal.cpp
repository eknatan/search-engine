#include <string>
#include <vector>
#include <mutex>

#include "parser_url_internal.hpp"

namespace data_base
{
void ParserUrlInternal::domain()
{
    auto first_str = m_url.find("//")+2;
    m_domain = m_url.substr(first_str, m_url.find("/",first_str)-first_str);
}

void ParserUrlInternal::create_list_links(std::string const &str_html, std::vector<std::string> &vector_url, std::string const &url, bool bounded)
{
    m_url = url;
    domain();
    make_gumbo(str_html, vector_url);
    bounded = bounded;
}

void ParserUrlInternal::make_gumbo(std::string const& str_html, std::vector<std::string> & vector_url) const
{
    GumboOutput* gumbo_output = gumbo_parse(str_html.c_str());
    search_for_links(gumbo_output->root, vector_url);
}

void ParserUrlInternal::search_for_links(GumboNode *node, std::vector<std::string> & vector_url) const
{
    
    if (node->type != GUMBO_NODE_ELEMENT)
        return;

    if (node->v.element.tag == GUMBO_TAG_A)
    {
        GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href");
        if (href)
        {
            auto fix_url = fixing_url(href->value);
            if(fix_url)
            {
                vector_url.push_back(fix_url.value());
            }
        }
    }

    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; i++)
    {
        search_for_links(static_cast<GumboNode*>(children->data[i]), vector_url);
    }
}

std::optional<std::string> ParserUrlInternal::fixing_url(std::string const& url) const
{
    std::optional<std::string> new_link;
    if(url.find("https://"+ m_domain) != url.npos)
    {
        new_link = url;
    }
    
    else if (url.find("http") == url.npos && url.find("#") == url.npos)
    {
        std::string str_temp;
        str_temp = "https://" + m_domain;
        str_temp += url; 
        new_link = str_temp;
    }
    return new_link;
}

} // namespace data_base