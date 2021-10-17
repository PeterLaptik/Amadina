#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <vector>

class StatefulScreen;
class Point;
class Entity;

class Command
{
    public:
        Command();
        virtual ~Command();

        virtual void Execute(void) = 0;

        virtual Command* Clone(void) = 0;

    protected:
        void EnterPoint(void);
        void EnterEntity(void);
        void EnterEntities(void);

        void SetPoint(const Point &point);
        void SetEntity(Entity *entity);
        void SetEntities(const std::vector<Entity*> &vec);

    private:
        volatile bool m_is_executing;
        StatefulScreen *m_screen;

};

#endif // COMMAND_H_INCLUDED
