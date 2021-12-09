#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <vector>

class Context;
class Screen;
class Point;
class Entity;

enum CMDResult
{
    RES_OK = 0,
    RES_ERROR = 1,
    RES_CANCEL = 2,
    RES_FINISHED = 3
};

class DataReciever
{
    public:
        virtual void SetPoint(const Point &point) = 0;
};

class Command: public DataReciever
{
    public:
        /// Command start out of context is not allowed:
        /// Only for prototypes
        Command(Context *context = nullptr);

        virtual ~Command();

        /// Main execute method.
        /// Starts 'Run' implemented in appropriate sub-class.
        /// Sets flag 'm_is_finished' to false before 'Run' starts
        /// and true after 'Run' is executed
        void Execute(void);


        virtual void Run(void) = 0;

        /// Creates copy of a command.
        /// Each new command is implicitly created
        /// by cloning of existing prototype
        virtual Command* Clone(Context *context = nullptr) = 0;

        Context* GetContext(void)
        {
            return m_context;
        }

        void Terminate(void)
        {
            m_is_finished = true;
            m_is_canceled = true;
        }

        bool IsFinished(void)
        {
            return m_is_finished;
        }

        void SetPoint(const Point &point);

        void Accept(void)
        {
            m_is_accepted = true;
        }

        void Dismiss(void)
        {
            m_is_accepted = false;
        }

        bool IsAccepted(void)
        {
            return m_is_accepted;
        }

        const std::vector<Entity*>& GetCreated(void)
        {
            return m_created;
        }

        const std::vector<Entity*>& GetRemoved(void)
        {
            return m_removed;
        }

    protected:
        CMDResult EnterPoint(Point *point);
        CMDResult EnterEntity(Entity *entity);
        CMDResult EnterEntities(std::vector<Entity*> *entity_set);
        //CMDResult PrintMessage(const std::string msg);

        void AppendEntity(Entity *entity);
        void RemoveEntity(Entity *entity);

    private:
        // Main waiting cycle
        inline void WaitForInput(void);

        // Created entities
        std::vector<Entity*> m_created;
        // Remove entities
        std::vector<Entity*> m_removed;

        // Keeps true-value during executing 'Execute'-method.
        // The flag can be set to true from outside
        // using method Terminate().
        // True-value set from outside means
        // that code from a general thread
        // attempts to stop the thread of 'Execute'-method
        // In this case it is better to finish 'Execute'-method
        // as quickly as possible
        volatile bool m_is_finished;

        // Shows if a command is waiting for input:
        // it means that the command is waiting for
        // point, entity, set of entities etc.
        // When data is inputed the state is reset to false.
        // This flag is related to atomic operations
        // like 'EnterPoint', 'EnterEntity', etc,
        // but not to 'Execute'-method.
        // (see description of 'm_is_finished')
        // false 'm_is_executing' with false 'm_is_canceled'
        // returns OK-result
        volatile bool m_is_executing;

        // Shows if the input canceled
        // Generally canceled input means
        // that the command has to be canceled too.
        // Cancel on input returns non-OK result code.
        volatile bool m_is_canceled;

        // Input values pointers.
        // Keep pointers to entities to be set
        // from outside (from another thread)
        Point *m_point;
        Entity *m_entity;
        std::vector<Entity*> *m_entity_set;
        // Environment data
        Context *m_context;
        //Screen *m_screen;
        // Command state
        bool m_is_accepted;
};

#endif // COMMAND_H_INCLUDED
