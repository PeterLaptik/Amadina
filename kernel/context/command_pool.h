#ifndef COMMAND_POOL_H_INCLUDED
#define COMMAND_POOL_H_INCLUDED

#include "../api/exports.h"
#include <deque>

class Command;

class DLL_EXPORT CommandPool
{
    public:
        CommandPool();
        virtual ~CommandPool();

        void Append(Command *command);
        void Undo(void);
        void Redo(void);
        void Clear(void);
        bool HasAccepted(void);
        bool HasDismissed(void);

    private:
        std::deque<Command*> m_accepted;
        std::deque<Command*> m_dismissed;

};

#endif // COMMAND_POOL_H_INCLUDED
