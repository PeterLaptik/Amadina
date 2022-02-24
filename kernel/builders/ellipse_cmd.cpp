#include "ellipse_cmd.h"
#include "../entities/ellipse.h"
#include "../geometry/geometry.h"

CmdEllipse::CmdEllipse(Context *context)
    : Command(context),
    p1_selected(false),
    p2_selected(false)
{ }

CmdEllipse::~CmdEllipse()
{ }

void CmdEllipse::Run()
{
    CMDResult result;

    PrintMessage("Pick first edge point");
    result = EnterPoint(&pt1);
    if(result!=RES_OK)
        return;
    p1_selected = true;

    PrintMessage("Pick second edge point");
    result = EnterPoint(&pt2);
    if(result!=RES_OK)
        return;
    p2_selected = true;

    PrintMessage("Pick radius point");
    result = EnterPoint(&pt3);
    if(result!=RES_OK)
        return;
}

void CmdEllipse::Redraw(IAdapterDC &dc, double x, double y)
{
    if(p1_selected && !p2_selected)
        dc.CadDrawConstraintLine(pt1.GetX(), pt1.GetY(), x, y);

    if(p1_selected && p2_selected)
    {
        double val_1 = (pt1.GetX()-pt2.GetX())*(pt1.GetY()-y)
                        - (pt1.GetX()-x)*(pt2.GetY()-pt1.GetY());
        double val_2 = (pt2.GetX()-pt1.GetX())*(pt2.GetX()-pt1.GetX())
                        + (pt2.GetY()-pt1.GetY())*(pt2.GetY()-pt1.GetY());
        double b = fabs(val_1)/sqrt(val_2);
        if(b<DBL_EPSILON)
            return;

        double a = geometry::calculate_distance(pt1.GetX(), pt1.GetY(), pt2.GetX(), pt2.GetY())/2;
        double e = sqrt(1 - b*b/(a*a));

        //Ellipse ellipse(pt1, pt2, a, b);
        dc.CadDrawEllipse(pt1.GetX(),pt1.GetY(),pt2.GetX(),pt2.GetY(),a,b);
    }
}

Command* CmdEllipse::Clone(Context *context)
{
    return new CmdEllipse(context);
}
