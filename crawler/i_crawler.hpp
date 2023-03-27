#pragma once

#include <string>

namespace data_base
{
class ICrawler
{
public:
    virtual ~ICrawler() = default;

    virtual void crawler(std::string const& url, bool bounded, size_t max_crawler) = 0;

};
    
} // namespace data_base
