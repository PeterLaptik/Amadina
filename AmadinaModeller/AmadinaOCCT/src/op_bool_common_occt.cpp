#include "op_bool_common_occt.h"
#include "occt_canvas.h"
#include <BRepAlgoAPI_Common.hxx>

void cad::model::occt::solid::OpBoolCommonOcct::DrawShape()
{
    if (!IsValid())
    {
        m_body.Nullify();
        return;
    }

    // List of shapes for the common intersection
    std::vector<AbstractShape *> shapes;
    GetShapes(shapes);

    // List of real OCCT-objects for the common intersection
    std::vector<Handle(AIS_InteractiveObject)> ais_objects;
    for (auto shape : shapes)
    {
        auto *occt_obj = dynamic_cast<OcctObject *>(shape);
        if (occt_obj)
            occt_obj->GetAisInteractiveObjects(ais_objects);
    }

    auto it = std::remove_if(ais_objects.begin(), ais_objects.end(),
        [](Handle(AIS_InteractiveObject) obj) {
            return dynamic_cast<AIS_Shape *>(obj.get()) == nullptr;
        });
    ais_objects.erase(it, ais_objects.end());

    if (ais_objects.size() <= 1)
        return;

    auto object_1 = dynamic_cast<AIS_Shape *>(ais_objects[0].get());
    auto object_2 = dynamic_cast<AIS_Shape *>(ais_objects[1].get());

    BRepAlgoAPI_Common common(object_1->Shape(), object_2->Shape());
    common.Build();

    // Result
    TopoDS_Shape result = common.Shape();
    m_body.reset(new AIS_Shape(result));

    ShowOcctObject(m_body);

    // Output
    if (IsVisible())
    {
        // Hide initial sub-elements
        for (auto shape : shapes)
        {
            shape->Remove();
        }

        // TODO
    }
}


