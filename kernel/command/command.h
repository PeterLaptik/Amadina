#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <vector>
#include <string>
#include "../api/exports.h"

class Context;
class Screen;
class Point;
class Entity;
class IAdapterDC;

enum CMDResult
{
    RES_OK = 0,
    RES_ERROR = 1,
    RES_CANCEL = 2,
    RES_FINISHED = 3
};

class DLL_EXPORT EntityBuilder
{
    public:
        virtual void SetPoint(const Point &point) = 0;
        virtual void SetEntities(const std::vector<Entity*> &selection) = 0;
        virtual void Redraw(IAdapterDC &dc, double x, double y)
        { }
};

///\brief Base command class.
/// Each command for drawing/editing (excepting of specific interactions)
/// has to be a sub-class of this class.
/// The class provides a common interface for using and executing commands
/// and contains main interactions routines which are used in sub-classes.
///
/// Main command logic executes in an overridden method run
/// using separate thread.
/// Following protected methods are used for interactions with screen context:
/// SetPoint (waits for picked point on a screen),
/// SetEntities (waits for entered entities on a screen)
/// All above methods are executed in a thread of a method 'Run'.
///
/// Commands should use methods AppendEntity/RemoveEntity
/// to add created entities and entities removed from a screen.
/// 'AppendEntity' appends new created entity to list of created objects.
/// 'RemoveEntity' appends existing entity from a screen to list
/// of removed objects.
/// Undo/redo, base destructor, and others procedures do not handle objects
/// which were not added via AppendEntity/RemoveEntity.
/// Do not delete entities removed from a screen manually.
/// Delete only objects not handled by AppendEntity/RemoveEntity.
///
/// Each command is kept as a prototype in a registration system.
/// So 'Clone' method should be overridden for every command.
///
/// Example of usage see in kernel/builders:
/// line_cmd.h, point_cmd, etc
///
class DLL_EXPORT Command: public EntityBuilder
{
    public:
        /// Command start out of context is not allowed:
        /// Only for prototypes
        Command(Context *context = nullptr);

        /// Base destructor.
        /// Handles lists of appended, removed entities
        virtual ~Command();

        /// Main execute method.
        /// Starts 'Run' implemented in appropriate sub-class.
        /// Sets flag 'm_is_finished' to false before 'Run' starts
        /// and true after 'Run' is executed
        void Execute(void);

        ///\brief Main command logic.
        /// Executes as a part of 'Execute'-method
        virtual void Run(void) = 0;

        /// Shows whether a command be executed multiply times.
        /// If yes, then command executor will clone previous command
        /// to start once more. It action is repeatable until
        /// user cancels command explicitly.
        ///\return true - if command can be executed multiply times
        virtual bool IsMultiCommand(void) const;

        /// Creates copy of a command.
        /// Each new command is implicitly created
        /// by cloning of existing prototype
        virtual Command* Clone(Context *context) = 0;

        /// Returns command context
        ///\return context object
        Context* GetContext();

        /// Tries terminate command from outside.
        /// When command is terminated it will be deleted
        /// with its thread
        void Terminate(void);

        /// Returns is command execution finished
        ///\return is command finished
        bool IsFinished(void) const;

        /// Returns is command canceled
        ///\return is command canceled
        bool IsCanceled(void) const;

        void SetPoint(const Point &point);
        void SetEntities(const std::vector<Entity*> &selection);

        void Accept(void);
        void Dismiss(void);
        bool IsAccepted(void) const;

        const std::vector<Entity*>& GetCreated(void) const;
        const std::vector<Entity*>& GetRemoved(void) const;

    protected:
        CMDResult EnterPoint(Point *point);
        CMDResult EnterEntity(Entity *entity);
        CMDResult EnterEntities(std::vector<Entity*> *entity_set);
        CMDResult PrintMessage(const std::string &msg);

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
        // Command state
        bool m_is_accepted;
};

#endif // COMMAND_H_INCLUDED
