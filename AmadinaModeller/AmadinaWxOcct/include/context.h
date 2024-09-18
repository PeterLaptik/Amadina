#ifndef XD_MODELLER_CONTEXT_H
#define XD_MODELLER_CONTEXT_H

#include "wxoccpanel.h"
#include "screen_modes.h"
#include <V3d_View.hxx>
#include <AIS_ViewCube.hxx>

namespace cad
{
    namespace modeller
    {
        class Context
        {
            public:
                Context(wxOccPanel *panel);

                virtual ~Context();

                void RunCommand(const std::string &cmd_name);

                void SetScreenMode(ScreenMode mode);

                Handle(V3d_View) GetView(void);
                Handle(AIS_ViewCube) GetViewCube(void);

            private:
                wxOccPanel *m_panel;
                Handle(V3d_View) m_view;
                Handle(AIS_ViewCube) m_view_cube;
        };
    }
}

#endif // XD_MODELLER_CONTEXT_H
