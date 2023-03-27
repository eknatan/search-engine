#pragma once

#include <SFML/Network.hpp>

#include "input_output.hpp"

namespace client
{
class Searcher;

class Server : public InputOutput
{
public:
    explicit Server(Searcher&);
    void run_search(size_t) override;

private:
    void run(sf::TcpSocket & socket);
    void get_input(std::vector<std::string> & vector_word, sf::TcpSocket&) const;
    void result(sf::TcpSocket& socket,std::vector<std::pair<std::string, double>> &) const;
    void cat_vector(std::vector<std::pair<std::string, double>> & vector_result) const;



private:
    Searcher& m_searcher;
    sf::TcpListener m_listener;
    size_t m_max_result;
};
    
} // namespace client
