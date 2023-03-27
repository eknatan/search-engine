#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <memory>

#include "server.hpp"
#include "searcher.hpp"

const int char_length = 1024;

namespace client
{
Server::Server(Searcher& searcher)
:m_searcher(searcher)
{
    m_listener.listen(8080);
}

void Server::run_search(size_t max_result)
{
    m_max_result = max_result;
    auto input = [this](std::unique_ptr<sf::TcpSocket> socket){this->run(*socket);};

    std::vector<std::thread> threads_input;

    for(;;)
    {
        std::unique_ptr<sf::TcpSocket> socket(new sf::TcpSocket());
        m_listener.accept(*socket);
        threads_input.push_back(std::thread(input, std::move(socket)));
    }
    
    for (auto &thread : threads_input)
    {
        thread.detach();
    }
}

void Server::run(sf::TcpSocket & socket)
{
    std::vector<std::string> vector_word;
    get_input(vector_word, socket);

    auto vector_result = m_searcher.search(vector_word);
    result(socket, vector_result);

    socket.disconnect();
}

void Server::get_input(std::vector<std::string> & vector_word, sf::TcpSocket& socket) const
{
    std::string enter_word = ("Please enter a search term: ");
    socket.send(enter_word.c_str(), enter_word.size()); 
    
    char data_receive[char_length];
    size_t received;
    if (socket.receive(data_receive ,char_length, received) != sf::Socket::Done)
    {
        std::string error_message = "Error receiving search words, too much length.";
         socket.send(error_message.c_str(), error_message.size());
    }

    data_receive[received] = '\0';
    std::istringstream ss(data_receive);

    std::string word;
    while (ss >> word)
    {
    vector_word.push_back(word);
    }
}


void Server::result(sf::TcpSocket& socket, std::vector<std::pair<std::string, double>>& vector_result) const
{
    cat_vector(vector_result);

    if (vector_result.size() == 0)
    {
        vector_result.push_back(std::make_pair("This word does not exist in the search results",0));
    }
     
    std::string string_result; 
    for(auto &i : vector_result)
    {
        // string_result += std::to_string(i.second) + "\t";
        string_result += i.first + "\n";
    }

    socket.send(string_result.c_str(), string_result.size());
    
}

void Server::cat_vector(std::vector<std::pair<std::string, double>> &vector_result) const
{
    auto max_result = (m_max_result < vector_result.size()) ? m_max_result : vector_result.size();

    vector_result.erase(vector_result.begin()+ max_result, vector_result.end());
}

}// namespace client