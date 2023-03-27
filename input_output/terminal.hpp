#pragma once

#include <memory>

#include "input_output.hpp"

namespace client
{
class Searcher;
class Terminal : public InputOutput
{
public:
    explicit Terminal(Searcher&);
    void run_search(size_t) override;

private:
    void get_input(std::vector<std::string> & vector_word) const;
    void result(std::vector<std::pair<std::string, double>> & vector_result) const;
    void cat_vector(std::vector<std::pair<std::string, double>> & vector_result) const;


private:
    Searcher& m_searcher;

    std::string m_string_search;
    size_t m_max_result;


};
    
} // namespace client
