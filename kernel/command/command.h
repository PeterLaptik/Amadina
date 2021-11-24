#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <vector>

class Context;
class StatefullScreen;
class Point;
class Entity;


enum CMDResult
{
    RES_OK = 0,
    RES_ERROR = 1,
    RES_CANCEL = 2,
    RES_FINISHED = 3
};

class Command
{
    public:
        Command(Context *context);
        Command() = delete;
        virtual ~Command();

        virtual void Execute(void) = 0;

        virtual void Terminate(void);

        virtual Command* Clone(void) = 0;

        Context* GetContext(void)
        {
            return m_context;
        }

        bool IsFinished(void)
        {
            return m_is_finished;
        }

    protected:
        // The flag can be set to true from outside
        // using method Terminate().
        // True-value means that code from a general thread
        // attempts to stop the thread of 'Execute'-method
        volatile bool m_is_finished;

        CMDResult EnterPoint(Point *point);
        CMDResult EnterEntity(Entity *entity);
        CMDResult EnterEntities(std::vector<Entity*> *entity_set);
        //CMDResult PrintMessage(const std::string msg);

        void SetPoint(const Point &point);
        void SetEntity(Entity *entity);
        void SetEntities(const std::vector<Entity*> &vec);

    private:
        // Shows if a command is waiting for input:
        // it means that the command is waiting for
        // point, entity, set of entities etc.
        // When data is inputed the state is reset to false
        volatile bool m_is_executing;
        // Shows if the input canceled
        // Generally canceled input means
        // that the command has to be canceled too
        volatile bool m_is_canceled;

        Context *m_context;
        StatefullScreen *m_screen;

};

#endif // COMMAND_H_INCLUDED
