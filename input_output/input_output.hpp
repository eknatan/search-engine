#pragma once

#include <string>
#include <vector>

namespace client
{
class InputOutput
{
public:
    virtual ~InputOutput() = default;
    virtual void run_search(size_t) = 0;

};
    
} // namespace client
