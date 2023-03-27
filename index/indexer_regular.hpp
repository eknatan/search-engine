#pragma once

#include <vector>
#include <string>

#include "indexer.hpp"

namespace data_base
{
class Index;
class IndexerRegular : public Indexer
{
public:
    explicit IndexerRegular(Index& index);
    void update(std::string const& vector_word, std::string const& url) override;

private:
    Index& m_index;
};


} // namespace data_base
