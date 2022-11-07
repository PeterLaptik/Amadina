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
            class CommandViewAbstract: public CommandAbstract
            {
                public:
                    CommandViewAbstract(V3d_TypeOfOrientation orientation, Context *context = nullptr)
                        : m_context(context), m_orientation(orientation)
                    { }

                    virtual ~CommandViewAbstract()
                    { }

                    virtual void Execute()
                    {
                        if(m_context==nullptr)
                            return;
                        // Use view cube to implement animation
                        Handle(AIS_ViewCube) view_cube = m_context->GetViewCube();
                        Handle(AIS_ViewCubeOwner) click_emulator(new AIS_ViewCubeOwner(view_cube, m_orientation));
                        view_cube->HandleClick(click_emulator);
                    }

                private:
                    Context *m_context;
                    V3d_TypeOfOrientation m_orientation;
            };

            ///\brief The command sets a 3D-view angle
            class CommandViewTop: public CommandViewAbstract
            {
                public:
                    CommandViewTop(Context *context = nullptr)
                        : CommandViewAbstract(V3d_Zpos, context)
                    { }

                    virtual ~CommandViewTop()
                    { }

                    virtual CommandAbstract* Clone(Context *context)
                    {
                        return new CommandViewTop(context);
                    }
            };

            ///\brief The command sets a 3D-view angle
            class CommandViewBottom: public CommandViewAbstract
            {
                public:
                    CommandViewBottom(Context *context = nullptr)
                        : CommandViewAbstract(V3d_Zneg, context)
                    { }

                    virtual ~CommandViewBottom()
                    { }

                    virtual CommandAbstract* Clone(Context *context)
                    {
                        return new CommandViewBottom(context);
                    }
            };

            ///\brief The command sets a 3D-view angle
            class CommandViewLeft: public CommandViewAbstract
            {
                public:
                    CommandViewLeft(Context *context = nullptr)
                        : CommandViewAbstract(V3d_Xneg, context)
                    { }

                    virtual ~CommandViewLeft()
                    { }

                    virtual CommandAbstract* Clone(Context *context)
                    {
                        return new CommandViewLeft(context);
                    }
            };

            ///\brief The command sets a 3D-view angle
            class CommandViewRight: public CommandViewAbstract
            {
                public:
                    CommandViewRight(Context *context = nullptr)
                        : CommandViewAbstract(V3d_Xpos, context)
                    { }

                    virtual ~CommandViewRight()
                    { }

                    virtual CommandAbstract* Clone(Context *context)
                    {
                        return new CommandViewRight(context);
                    }
            };

            ///\brief The command sets a 3D-view angle
            class CommandViewFront: public CommandViewAbstract
            {
                public:
                    CommandViewFront(Context *context = nullptr)
                        : CommandViewAbstract(V3d_Yneg, context)
                    { }

                    virtual ~CommandViewFront()
                    { }

                    virtual CommandAbstract* Clone(Context *context)
                    {
                        return new CommandViewFront(context);
                    }
            };

            ///\brief The command sets a 3D-view angle
            class CommandViewBack: public CommandViewAbstract
            {
                public:
                    CommandViewBack(Context *context = nullptr)
                        : CommandViewAbstract(V3d_Ypos, context)
                    { }

                    virtual ~CommandViewBack()
                    { }

                    virtual CommandAbstract* Clone(Context *context)
                    {
                        return new CommandViewBack(context);
                    }
            };
        }
    }
}

#endif // COMMANDS_VIEW_H_INCLUDED
