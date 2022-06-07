#ifndef DISPATCHER_H_INCLUDED
#define DISPATCHER_H_INCLUDED

#include <string>
#include <unordered_map>

class Command;

namespace modeller {
    namespace command {

        class CommandDispatcher
        {
            public:
                CommandDispatcher();
                virtual ~CommandDispatcher();

            private:
                std::unordered_map<std::string,Command*> m_commands;
        };

    }
}

#endif // DISPATCHER_H_INCLUDED
