/*!*****************************************************************************
 * \file          CommandParse.cpp
 * \author        Eugene Ho Shu Sheng
 * \par DP email: shushengeugene.ho@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         This file contains the implementation of the CommandParse class.
 *******************************************************************************/
#include "CommandParse.h"
#include "GeomCompiler.h"


std::shared_ptr<TDS::CommandParser> TDS::CommandParser::m_Instance{};

TDS::CommandParser::CommandParser()
{
}

TDS::CommandParser::~CommandParser()
{
    for (auto& cmd : this->m_Commands)
    {
        if (cmd.second)
            delete cmd.second;
    }
}





void TDS::CommandParser::ExecuteDirect(std::string_view cmdName, std::string_view param1, std::string_view param2)
{
}

void TDS::CommandParser::checkForCommands()
{
    std::string input{};
    std::cout << "--Loaded ResourceLoader/Compiler..." << std::endl;
    while (is_Running)
    {
        std::getline(std::cin, input);

        std::istringstream iss(input);
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};

        if (!tokens.empty())
        {
            std::string_view cmdName = tokens[0];
            if (strcmp(tokens[0].c_str(), "Quit") == 0)
            {
                is_Running = false;
            }
            else if (m_Commands.find(cmdName.data()) != m_Commands.end())
            {
                if (tokens.size() >= 3)
                {
                    Execute(cmdName, tokens[1], tokens[2]);
                }
                else
                {
                    std::cout << "Invalid number of parameters." << std::endl;
                }
            }
            else
            {
                std::cout << "Unknown command." << std::endl;
            }
        }
    }
}



