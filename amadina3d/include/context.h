#ifndef XD_MODELLER_CONTEXT_H
#define XD_MODELLER_CONTEXT_H

#include <V3d_View.hxx>
#include <AIS_ViewCube.hxx>

namespace cad
{
    namespace modeller
    {
        class Context
        {
            public:
                Context(Handle(V3d_View) view, Handle(AIS_ViewCube) view_cube);
                virtual ~Context();

                void RunCommand(const std::string &cmd_name);

                Handle(V3d_View) GetView(void);
                Handle(AIS_ViewCube) GetViewCube(void);

            private:
                Handle(V3d_View) m_view;
                Handle(AIS_ViewCube) m_view_cube;
        };
    }
}

#endif // XD_MODELLER_CONTEXT_H
