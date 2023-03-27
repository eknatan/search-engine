#pragma once

namespace data_base
{
class Indexer
{
public:
    virtual ~Indexer()= default;
    virtual void update(std::string const& vector_word, std::string const& url) = 0;
};
    
} // namespace data_base
