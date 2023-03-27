#pragma once

namespace data_base
{
class IRankPage
{
public:
    virtual ~IRankPage() = default;
    virtual void update_rank() = 0;
    virtual double get_rank(std::string const&) = 0;
};
    
} // namespace data_base
