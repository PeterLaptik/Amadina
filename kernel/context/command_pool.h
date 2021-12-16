#ifndef COMMAND_POOL_H_INCLUDED
#define COMMAND_POOL_H_INCLUDED

#include "../api/exports.h"
#include <deque>

class Command;
class Context;

class DLL_EXPORT CommandPool
{
    public:
        CommandPool(Context *context);
        CommandPool() = delete;
        virtual ~CommandPool();

        void Append(Command *command);
        void Undo(void);
        void Redo(void);
        void Clear(void);
        bool HasAccepted(void);
        bool HasDismissed(void);

    private:
        Context *m_context;
        std::deque<Command*> m_accepted;
        std::deque<Command*> m_dismissed;

};

#endif // COMMAND_POOL_H_INCLUDED
