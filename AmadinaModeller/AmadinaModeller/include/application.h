#ifndef MAIN_APPLICATION_INCLUDED_H
#define MAIN_APPLICATION_INCLUDED_H

namespace cad::command
{
    class ApplicationContext;
}

class Application
{
    public:
        virtual cad::command::ApplicationContext* GetAppContext() = 0;
};

#endif
