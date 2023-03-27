#include "application.hpp"

#include "crawler.hpp"
#include "input_output.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <thread>

Application::Application(data_base::Crawler &crawler, client::InputOutput &terminal, client::InputOutput& server, std::string const& file_name)
:m_crawler(crawler)
,m_input_output_terminal(terminal)
,m_input_output_server(server)
{
    configuration(file_name);
}

void Application::configuration(std::string const& name_file)
{
    if (name_file.empty())
        std::cerr << "No configuration file specified" << std::endl;


    std::ifstream myfile (name_file);

    std::string line;
    if ( myfile.is_open() ) 
    {    
        std::getline (myfile, line);
        m_url = line.substr(line.find('=')+2,line.size()-line.find('='));

        std::getline (myfile, line);
        m_bounded = std::stoi(line.substr(line.find('=')+2,line.size()-line.find('=')));
        
        std::getline (myfile, line);
        m_max_crawler = std::stoi(line.substr(line.find('=')+2,line.size()-line.find('=')));
        
        std::getline (myfile, line);
        m_max_result = std::stoi(line.substr(line.find('=')+2,line.size()-line.find('=')));
    }
    else
        std::cerr << "Could not open configuration file " << name_file << std::endl;

}

void Application::run()
{ 
    auto lambda_crawler = [](data_base::Crawler &crawler, std::string & url, bool bounded, size_t max_crawler){crawler.crawler(url, bounded, max_crawler);};
    std::thread thread_crawler(lambda_crawler, std::ref(m_crawler), std::ref(m_url), m_bounded, m_max_crawler);

    auto lambda_input = [](client::InputOutput &input_output, size_t max_result){input_output.run_search(max_result);};
    std::thread thread_input_terminal(lambda_input, std::ref(m_input_output_terminal), m_max_result);
    std::thread thread_input_server(lambda_input, std::ref(m_input_output_server), m_max_result);
   
    thread_crawler.join();
    thread_input_terminal.join();
    thread_input_server.join();
}
