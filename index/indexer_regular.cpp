#include "index.hpp"
#include "indexer_regular.hpp"

namespace data_base
{
IndexerRegular::IndexerRegular(Index &index)
:m_index(index)
{
}

/**
 * @brief update index of words
 * 
 * @param word this word to insert into index
 * @param url This is the link where the word is
 */
void IndexerRegular::update(std::string const& word, std::string const& url)
{
     m_index.set(word, url);
}
    
} // namespace data_base
