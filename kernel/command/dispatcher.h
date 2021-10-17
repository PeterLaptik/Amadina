#ifndef DISPATCHER_H_INCLUDED
#define DISPATCHER_H_INCLUDED

#include <string>
#include <map>

class Command;

class CommandDispatcher
{
    public:
        CommandDispatcher();
        virtual ~CommandDispatcher();

        virtual void RegisterCommand(Command *cmd, const std::string &name);

        virtual Command* GetCommand(const std::string &name);

    private:
        std::map<std::string, Command*> m_command_map;
};

#endif // DISPATCHER_H_INCLUDED
