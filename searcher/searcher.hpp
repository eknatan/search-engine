#pragma once

#include <vector>
#include <string>

namespace client
{
class Searcher
{
public:
    virtual std::vector<std::pair<std::string, double>> search(std::vector<std::string> & word) = 0;


};
    
} // namespace client
