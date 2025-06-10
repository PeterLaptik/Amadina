#ifndef OP_BOOL_COMMON_OCCT_INCLUDED_H
#define OP_BOOL_COMMON_OCCT_INCLUDED_H

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

    using cad::model::solid::OpBoolean;

    class OpBoolCommonOcct : public OpBoolOcct
    {
        public:
            using OpBoolOcct::OpBoolOcct;

            DLL_EXPORT ~OpBoolCommonOcct() final = default;

            DLL_EXPORT void DrawShape() final;
    };
}

#endif // OP_BOOL_COMMON_OCCT_INCLUDED_H

