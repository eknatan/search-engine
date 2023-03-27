#pragma once

#include <unordered_set>
#include <iostream>
#include <mutex>

#include "unordered_set.hpp"

namespace data_structures
{
class UnorderedSetSafe : public UnorderedSet
{
public:
    virtual bool empty() const override;
    virtual size_t size()const override;

    // virtual std::unordered_set<std::string>::iterator begin() override;
    // virtual std::unordered_set<std::string>::const_iterator cbegin() const override;

    // virtual std::unordered_set<std::string>::iterator end();
    // virtual std::unordered_set<std::string>::const_iterator cend() const override;

    virtual std::pair<std::unordered_set<std::string>::iterator ,bool> insert(std::string const&);
    virtual std::pair<std::unordered_set<std::string>::iterator ,bool> insert(std::string &);

    virtual std::unordered_set<std::string> get_set() const;

private:
    std::unordered_set<std::string> m_unordered_Set;
    mutable std::mutex m_mutex;
};    

} // namespace data_structures