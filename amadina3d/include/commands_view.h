#ifndef COMMANDS_VIEW_H_INCLUDED
#define COMMANDS_VIEW_H_INCLUDED

#include "command_abstract.h"

namespace cad
{
    namespace modeller
    {
        namespace command
        {
            ///\brief The command sets a 3D-view angle
            class CommandViewTop: public CommandAbstract
            {
                public:
                    CommandViewTop(Context *context = nullptr)
                        : m_context(context)
                    { }

                    virtual ~CommandViewTop()
                    { }

                    virtual void Execute()
                    {
                        if(m_context==nullptr)
                            return;
                        // Use view cube to implement animation
                        Handle(AIS_ViewCube) view_cube = m_context->GetViewCube();
                        Handle(AIS_ViewCubeOwner) click_emulator(new AIS_ViewCubeOwner(view_cube, V3d_Zpos));
                        view_cube->HandleClick(click_emulator);
                    }

                    virtual CommandAbstract* Clone(Context *context)
                    {
                        return new CommandViewTop(context);
                    }

                private:
                    Context *m_context;
            };

            ///\brief The command sets a 3D-view angle
            class CommandViewBottom: public CommandAbstract
            {
                public:
                    CommandViewBottom(Context *context = nullptr)
                        : m_context(context)
                    { }

                    virtual ~CommandViewBottom()
                    { }

                    virtual void Execute()
                    {
                        if(m_context==nullptr)
                            return;
                        // Use view cube to implement animation
                        Handle(AIS_ViewCube) view_cube = m_context->GetViewCube();
                        Handle(AIS_ViewCubeOwner) click_emulator(new AIS_ViewCubeOwner(view_cube, V3d_Zneg));
                        view_cube->HandleClick(click_emulator);
                    }

                    virtual CommandAbstract* Clone(Context *context)
                    {
                        return new CommandViewBottom(context);
                    }

                private:
                    Context *m_context;
            };

            ///\brief The command sets a 3D-view angle
            class CommandViewLeft: public CommandAbstract
            {
                public:
                    CommandViewLeft(Context *context = nullptr)
                        : m_context(context)
                    { }

                    virtual ~CommandViewLeft()
                    { }

                    virtual void Execute()
                    {
                        if(m_context==nullptr)
                            return;
                        // Use view cube to implement animation
                        Handle(AIS_ViewCube) view_cube = m_context->GetViewCube();
                        Handle(AIS_ViewCubeOwner) click_emulator(new AIS_ViewCubeOwner(view_cube, V3d_Xneg));
                        view_cube->HandleClick(click_emulator);
                    }

                    virtual CommandAbstract* Clone(Context *context)
                    {
                        return new CommandViewLeft(context);
                    }

                private:
                    Context *m_context;
            };

            ///\brief The command sets a 3D-view angle
            class CommandViewRight: public CommandAbstract
            {
                public:
                    CommandViewRight(Context *context = nullptr)
                        : m_context(context)
                    { }

                    virtual ~CommandViewRight()
                    { }

                    virtual void Execute()
                    {
                        if(m_context==nullptr)
                            return;
                        // Use view cube to implement animation
                        Handle(AIS_ViewCube) view_cube = m_context->GetViewCube();
                        Handle(AIS_ViewCubeOwner) click_emulator(new AIS_ViewCubeOwner(view_cube, V3d_Xpos));
                        view_cube->HandleClick(click_emulator);
                    }

                    virtual CommandAbstract* Clone(Context *context)
                    {
                        return new CommandViewRight(context);
                    }

                private:
                    Context *m_context;
            };

            ///\brief The command sets a 3D-view angle
            class CommandViewFront: public CommandAbstract
            {
                public:
                    CommandViewFront(Context *context = nullptr)
                        : m_context(context)
                    { }

                    virtual ~CommandViewFront()
                    { }

                    virtual void Execute()
                    {
                        if(m_context==nullptr)
                            return;
                        // Use view cube to implement animation
                        Handle(AIS_ViewCube) view_cube = m_context->GetViewCube();
                        Handle(AIS_ViewCubeOwner) click_emulator(new AIS_ViewCubeOwner(view_cube, V3d_Yneg));
                        view_cube->HandleClick(click_emulator);
                    }

                    virtual CommandAbstract* Clone(Context *context)
                    {
                        return new CommandViewFront(context);
                    }

                private:
                    Context *m_context;
            };

            ///\brief The command sets a 3D-view angle
            class CommandViewBack: public CommandAbstract
            {
                public:
                    CommandViewBack(Context *context = nullptr)
                        : m_context(context)
                    { }

                    virtual ~CommandViewBack()
                    { }

                    virtual void Execute()
                    {
                        if(m_context==nullptr)
                            return;
                        // Use view cube to implement animation
                        Handle(AIS_ViewCube) view_cube = m_context->GetViewCube();
                        Handle(AIS_ViewCubeOwner) click_emulator(new AIS_ViewCubeOwner(view_cube, V3d_Ypos));
                        view_cube->HandleClick(click_emulator);
                    }

                    virtual CommandAbstract* Clone(Context *context)
                    {
                        return new CommandViewBack(context);
                    }

                private:
                    Context *m_context;
            };
        }
    }
}

#endif // COMMANDS_VIEW_H_INCLUDED
