#ifndef OP_BOOL_FUSE_OCCT_INCLUDED_H
#define OP_BOOL_FUSE_OCCT_INCLUDED_H

#include "op_bool_occt.h"
#include "occt_object.h"
#include <AIS_Shape.hxx>

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace cad::model::occt::solid
{
    class OpBoolFuseOcct : public OpBoolOcct
    {
        public:
            using OpBoolOcct::OpBoolOcct;

            DLL_EXPORT ~OpBoolFuseOcct() final = default;

            private:
            DLL_EXPORT void DrawShape() final;

            DLL_EXPORT void RemoveShape() final;
    };
}

#endif // OP_BOOL_FUSE_OCCT_INCLUDED_H
