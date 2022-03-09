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

    //Ellipse ellipse = BuildEllipse();
//    if(ellipse.GetSemiAxisLong()>0)
//    {
//        //AppendEntity(ellipse.Clone());
//        PrintMessage("OK. Ellipse created");
//    }
//    else
//    {
//        PrintMessage("Wrong geometric values for the ellipse!");
//        result = RES_ERROR;
//    }
}

void CmdEllipse::Redraw(IAdapterDC &dc, double x, double y)
{
    if(p1_selected && !p2_selected)
        dc.CadDrawConstraintLine(pt1.GetX(), pt1.GetY(), x, y);

    if(p1_selected && p2_selected)
    {
        // Long semiaxis
        double a = geometry::calculate_distance(pt1.GetX(),pt1.GetY(),pt2.GetX(),pt2.GetY())/2;
        // Center point coordinates
        double xc, yc;
        geometry::calculate_center_point(pt1.GetX(),pt1.GetY(),pt2.GetX(),pt2.GetY(),xc,yc);
        // Short semiaxis
        double b = geometry::calculate_distance(xc, yc, x, y);

        //if(a<b)
            //std::swap(a,b);

        // Eccentricity
        double e = sqrt(fabs(1 - b*b/(a*a)));
        // Focal distance
        double c = a*e;
        // Focal parameter
        double p = (1 - e*e);
        // Axis angle
        double angle = geometry::calculate_angle_rad(xc, yc,
                                    std::max(pt1.GetX(),pt2.GetX()),
                                    std::max(pt1.GetY(),pt2.GetY()));
        // Focal coordinates
        double x1 = xc - c;
        double x2 = xc + c;
        double y1 = std::min(pt1.GetY(),pt2.GetY());
        double y2 = std::max(pt1.GetY(),pt2.GetY());


        // Ellipse angle in radians
        double f_angle = geometry::calculate_angle_rad(xc, yc, x2, y2);
        double delta_angle = fabs(angle - f_angle);

        y1 -= x1/sin(delta_angle);
        //y2 -= x2/cos(delta_angle);

        // Focal points
        Point f1 = Point(x1,y1);
        Point f2 = Point(x2,y2);
        dc.CadDrawCircle(f1, 5);
        dc.CadDrawCircle(f2, 5);
        //dc.CadDrawCircle(Point((xc - c)/cos(delta_angle),y1), 2);
        //dc.CadDrawCircle(Point((xc + c)/cos(delta_angle),y2), 2);
        /*
        double val_1 = (pt1.GetX()-pt2.GetX())*(pt1.GetY()-y)
                        - (pt1.GetX()-x)*(pt2.GetY()-pt1.GetY());
        double val_2 = (pt2.GetX()-pt1.GetX())*(pt2.GetX()-pt1.GetX())
                        + (pt2.GetY()-pt1.GetY())*(pt2.GetY()-pt1.GetY());
        double b = fabs(val_1)/sqrt(val_2);
        if(b<DBL_EPSILON)
            return;

        // Center point coordinates (between focus points)
        double xc, yc;
        geometry::calculate_center_point(pt1.GetX(),pt1.GetY(),pt2.GetX(),pt2.GetY(),xc,yc);

        dc.CadDrawCircle(Point(xc,yc), 5);
        double a = geometry::calculate_distance(xc, yc, x, y);
        */

        /*
        double e = sqrt(1 - b*b/(a*a));
        double angle = geometry::calculate_angle_rad(pt1.GetX(),pt1.GetY(),pt2.GetX(),pt2.GetY());
        */
        //a = a*cos(angle);


        dc.CadDrawConstraintLine(xc, yc, x, y);
        /*
        dc.CadDrawConstraintLine(pt1.GetX(),pt1.GetY(),pt2.GetX(),pt2.GetY());
        */


        dc.CadDrawConstraintLine(f1.GetX(),f1.GetY(),f2.GetX(),f2.GetY());

        dc.CadDrawCircle(pt1, 5);
        dc.CadDrawCircle(pt2, 5);
        dc.CadDrawEllipse(f1.GetX(),f1.GetY(),f2.GetX(),f2.GetY(),a,b);
    }
}

Ellipse CmdEllipse::BuildEllipse()
{
    Ellipse result;

    double val_1 = (pt1.GetX()-pt2.GetX())*(pt1.GetY()-pt3.GetY())
                        - (pt1.GetX()-pt3.GetX())*(pt2.GetY()-pt1.GetY());
    double val_2 = (pt2.GetX()-pt1.GetX())*(pt2.GetX()-pt1.GetX())
                        + (pt2.GetY()-pt1.GetY())*(pt2.GetY()-pt1.GetY());
    double b = fabs(val_1)/sqrt(val_2);
    if(b<DBL_EPSILON)
    {
        result.SetSemiAxisLong(-1.0);
        return result;
    }

    double xc, yc;
    geometry::calculate_center_point(pt1.GetX(),pt1.GetY(),pt2.GetX(),pt2.GetY(),xc,yc);
    double a = geometry::calculate_distance(xc, yc, pt3.GetX(),pt3.GetY());
    double e = sqrt(1 - b*b/(a*a));

    result.SetFocuses(pt1, pt2);
    result.SetSemiAxisLong(a);
    result.SetSemiAxisShort(b);
    return result;
}

Command* CmdEllipse::Clone(Context *context)
{
    return new CmdEllipse(context);
}
