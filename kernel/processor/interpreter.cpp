#include "interpreter.h"
#include "drawmanager.h"
#include <sstream>
#include <algorithm>

CommandInterpreter::CommandInterpreter()
        : m_active_panel(nullptr)
{ }

CommandInterpreter::~CommandInterpreter()
{ }


void CommandInterpreter::RegisterCommand(const std::string &name, command_function cmd)
{
    m_commands.emplace(std::pair<std::string,command_function>(name, cmd));
}


void CommandInterpreter::ExecuteCommand(const std::string &name)
{
    if(!m_active_panel)
        return;

    std::unordered_map<std::string,command_function>::const_iterator it = m_commands.find(name);
    // If a command does not exist
    // then trying to parse the expression
    if(it==m_commands.end())
    {
        ParseCommand(name);
        return;
    }
    // Execute command
    command_function cmd = it->second;
    cmd(m_active_panel);
}

void CommandInterpreter::ParseCommand(const std::string &line)
{
    std::vector<std::string> tokens;
    std::stringstream in(line);
    std::string token;
    // Tokenized string
    while(getline(in, token, ' '))
        tokens.push_back(token);
    // Remove empty tokens
    tokens.erase(std::remove_if(tokens.begin(), tokens.end(), [](std::string i){return i=="";}), tokens.end());
    // Nothing to parse if less than two tokens
    if(tokens.size()<2)
        return;

    // Check for preference
    if(m_active_panel->GetDrawManager()->HasPreference(tokens.at(0)))
    {
        try
        {
            float value = std::stof(tokens.at(1));
            m_active_panel->GetDrawManager()->SetPreference(tokens.at(0), value);
        }
        catch (...)
        {
            // Wrong value received for the preference
            // Only float values can perform property values even if real value is integer or boolean
            // Do nothing: property has not been changed
        }
        return;
    }
}

void CommandInterpreter::SetActivePanel(ViewPanel *panel)
{
    m_active_panel = panel;
}

void CommandInterpreter::ResetActivePanel(void)
{
    m_active_panel = nullptr;
}
