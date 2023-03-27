#include <algorithm>
#include <sstream>
#include <gumbo.h>

#include "parser_words_internal.hpp"
#include "indexer.hpp"

namespace data_base
{
ParserWordsInternal::ParserWordsInternal(Indexer &indexer)
:m_indexer(indexer)
{
}

void ParserWordsInternal::extract_words_from_html(std::string const& str_html, std::string const& url)
{
    make_gumbo(str_html, url);
}

void ParserWordsInternal::make_gumbo(std::string const& str_html, std::string const& url)
{
    GumboOutput* gumbo_output = gumbo_parse(str_html.c_str());
    search_for_words(gumbo_output->root, url);
}

bool char_filter(char const c)
{
    return !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '-') || (c == '_'));
}

void ParserWordsInternal::search_for_words(GumboNode *node , std::string const& url)
{
    if (node->type == GUMBO_NODE_ELEMENT && node->v.element.tag == GUMBO_TAG_P) 
    {
      GumboVector* children = &node->v.element.children;
      for (unsigned int i = 0; i < children->length; ++i) 
      {
        if(static_cast<GumboNode*>(children->data[i])->type == GUMBO_NODE_TEXT)
        {
          std::stringstream ss(static_cast<GumboNode*>(children->data[i])->v.text.text);
          std::string word;
          while(ss >> word)
          {
            word.erase(std::remove_if(word.begin(), word.end(), char_filter), word.end());    
            if(word.begin() != word.end())
            {
              std::string word_lower;
              for(size_t i = 0; i <word.size(); ++i)
              {
                word_lower += tolower(word[i]);
              }
              m_indexer.update(word_lower , url);              
            }
          }
        }
      }
    } else if (node->type == GUMBO_NODE_ELEMENT &&
               node->v.element.tag != GUMBO_TAG_SCRIPT &&
               node->v.element.tag != GUMBO_TAG_STYLE) {
      GumboVector* children = &node->v.element.children;
      for (unsigned int i = 0; i < children->length; ++i) {
        search_for_words(static_cast<GumboNode*>(children->data[i]), url);
      }
    }
}



}// namespace