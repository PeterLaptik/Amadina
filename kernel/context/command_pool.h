#ifndef COMMAND_POOL_H_INCLUDED
#define COMMAND_POOL_H_INCLUDED

class CommandPool
{
    public:
        CommandPool(Context *context);
        ~CommandPool();

    private:
        std::thread m_current_thread;


};

#endif // COMMAND_POOL_H_INCLUDED
