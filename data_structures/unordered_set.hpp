#pragma once

#include <unordered_set>
#include <iostream>

namespace data_structures
{
class UnorderedSet
{
public:
    virtual ~UnorderedSet() = default;

    virtual bool empty() const = 0;
    virtual size_t size() const = 0;

    // virtual std::unordered_set<std::string>::iterator begin() = 0;
    // virtual std::unordered_set<std::string>::const_iterator cbegin() const = 0;

    // virtual std::unordered_set<std::string>::iterator end() = 0;
    // virtual std::unordered_set<std::string>::const_iterator cend() const = 0;

    virtual std::pair<std::unordered_set<std::string>::iterator ,bool> insert(std::string const&) = 0;
    virtual std::pair<std::unordered_set<std::string>::iterator ,bool> insert(std::string&) = 0;

    virtual std::unordered_set<std::string> get_set() const = 0;
};    
    
} // namespace data_structures