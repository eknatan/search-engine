#pragma once

namespace data_structures
{
class Queue
{
public:
    virtual ~Queue() = default;
    
    virtual std::string pop() = 0;
    virtual void push(std::string const&) = 0;
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual std::string front() const = 0;
    virtual std::string back() const = 0;
};    
    
} // namespace data_structures
