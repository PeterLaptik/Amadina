#ifndef INTERPRETER_H_INCLUDED
#define INTERPRETER_H_INCLUDED

#include "../view_2d/viewpanel.h"
#include <unordered_map>

typedef void (*command_function)(ViewPanel*);

// Command line interpreter
class CommandInterpreter
{
    public:
        CommandInterpreter();
        virtual ~CommandInterpreter();

        void RegisterCommand(const std::string &name, command_function);

        void ExecuteCommand(const std::string &name);

        void ParseCommand(const std::string &line);

        void SetActivePanel(ViewPanel *panel);

        void ResetActivePanel(void);

    protected:

    private:

        std::unordered_map<std::string,command_function> m_commands;

        ViewPanel *m_active_panel;

};

#endif // INTERPRETER_H_INCLUDED
