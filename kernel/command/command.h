#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <vector>

class Context;
class StatefullScreen;
class Point;
class Entity;

class Command
{
    public:
        Command(Context *context);
        Command() = delete;
        virtual ~Command();

        virtual void Execute(void) = 0;

        virtual Command* Clone(void) = 0;

        Context* GetContext(void)
        {
            return m_context;
        }

    protected:
        void EnterPoint(void);
        void EnterEntity(void);
        void EnterEntities(void);

        void SetPoint(const Point &point);
        void SetEntity(Entity *entity);
        void SetEntities(const std::vector<Entity*> &vec);

    private:
        volatile bool m_is_executing;
        volatile bool m_is_canceled;
        Context *m_context;
        StatefullScreen *m_screen;

};

#endif // COMMAND_H_INCLUDED
