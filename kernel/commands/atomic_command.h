#ifndef ATOMIC_COMMAND_H_INCLUDED
#define ATOMIC_COMMAND_H_INCLUDED

//#include "../entities/entity.h"
#include "../entities/point.h"
#include <vector>

class Point;
class Entity;

enum AtomicCommandType
{
    CMD_SELECT_POINT,
    CMD_SELECT_ENTITY,
    CMD_SELECT_ENTITY_GROUP
};


class BaseAtomicCommand
{
    public:
        BaseAtomicCommand(AtomicCommandType cmd_type) :
            m_type(cmd_type)
        { }

        virtual ~BaseAtomicCommand() {}

        virtual void SetPoint(const Point &point) = 0;

        virtual void SetEntity(const Entity* entity) = 0;

        virtual void SetEntityGroup(const std::vector<Entity*> &entities) = 0;

        AtomicCommandType GetCommandType(void) const
        {
            return m_type;
        }

    protected:
        AtomicCommandType m_type;
};



template<AtomicCommandType E>
class AtomicCommand: public BaseAtomicCommand
{
    public:
        AtomicCommand() :
            BaseAtomicCommand(E)
        { }

        virtual void SetPoint(const Point &point) {m_data.point = point;};
        virtual void SetEntity(const Entity* entity) {m_data.entity = entity;}
        virtual void SetEntityGroup(const std::vector<Entity*> &entities) {return;};



    private:
        union AtomicCommandData
        {
            Point point;
            Entity* entity;
        } m_data;
};


template<>
class AtomicCommand<CMD_SELECT_ENTITY_GROUP>: public BaseAtomicCommand
{
    public:
        AtomicCommand() :
            BaseAtomicCommand(CMD_SELECT_ENTITY_GROUP)
        { }

        virtual void SetPoint(const Point &point) {return;}

        virtual void SetEntity(const Entity* entity) {return;}

        virtual void SetEntityGroup(const std::vector<Entity*> &entities)
        {
            for(std::vector <Entity*>::const_iterator it=entities.begin();
                it!=entities.end(); ++it)
                {
                    m_data.push_back(*it);
                }
        }

    private:
        std::vector <Entity*> m_data;
};


#endif // ATOMIC_COMMAND_H_INCLUDED
