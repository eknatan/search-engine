#pragma once

#include <string>

namespace data_base {class Crawler;}
namespace client {class InputOutput;}

class Application
{
public:
    Application(data_base::Crawler &, client::InputOutput &, client::InputOutput&, std::string const& file_name);

    void configuration(std::string const& name_file);
    void run();

private:
    data_base::Crawler &m_crawler;
    client::InputOutput &m_input_output_terminal;
    client::InputOutput &m_input_output_server;

    std::string m_url;
    bool m_bounded;
    size_t m_max_crawler;
    size_t m_max_result;
};