#ifndef ABSTRACT_COMMAND_H_INCLUDED
#define ABSTRACT_COMMAND_H_INCLUDED

#include "../entities/entity.h"
#include "../entities/point.h"
#include <array>

class ScreenInterface;

struct CommandReciever
{
    Entity *entity;
    Point point;
};

///\brief Command interface

template <std::size_t m_size>
class AbstractCommand
{
    public:
        void Execute(void);

        void GetFirstCommand(void)
        {
            AtomicCommand* it = m_commands.begin();
            return *it;
        }

        void GetNextCommand()
        {

        }


    private:
        // List of a commands to evaluate
        // The list has to be initialized in a derived class constructor
        std::array<int, m_size> m_commands;
        // Created entities
        // Removed entities

};





#endif // ABSTRACT_COMMAND_H_INCLUDED
