#include "terminal.hpp"
#include "searcher.hpp"

#include <sstream>
#include <iostream>

namespace client
{

Terminal::Terminal(Searcher& searcher)
:m_searcher(searcher)
{
}

void Terminal::run_search(size_t max_result)
{
    m_max_result = max_result;

    while(1)
    {
        std::vector<std::string> vector_word;
        get_input(vector_word);
        auto vector_result = m_searcher.search(vector_word);
        result(vector_result);
    }
}


void Terminal::get_input(std::vector<std::string> &vector_word) const
{
    std::cout << "Please enter a search term: ";
    std::string terms;
    getline(std::cin, terms);

    std::istringstream ss(terms);
    std::string word;
    while (ss >> word)
    {
        vector_word.push_back(word);
    }

}

void Terminal::result(std::vector<std::pair<std::string, double>> & vector_result) const
{
    cat_vector(vector_result);

    if (vector_result.size() == 0)
    {    
        vector_result.push_back(std::make_pair("This word does not exist in the search results",0));
    }

    for(auto i : vector_result)
    {
        std::cout<<i.first<<"\n";
    }
    std::cout<<"end result\n";
    
}

void Terminal::cat_vector(std::vector<std::pair<std::string, double>> & vector_result) const
{
    auto max_result = (m_max_result < vector_result.size()) ? m_max_result : vector_result.size();

    vector_result.erase(vector_result.begin()+ max_result, vector_result.end());

}

} // namespace client


