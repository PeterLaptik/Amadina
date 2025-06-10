#ifndef MAIN_ABSTRACT_COMMAND_INCLUDED_H
#define MAIN_ABSTRACT_COMMAND_INCLUDED_H

class MainFrame;

class AbstractCommand
{
    public:
        AbstractCommand(Application *app)
            : m_app(app)
        { }

        virtual void Execute() = 0;

    protected:
        Application *m_app;
};

#endif
