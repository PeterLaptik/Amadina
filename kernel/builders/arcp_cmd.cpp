#include "arcp_cmd.h"
#include "../entities/arc.h"
#include "../entities/line.h"
#include "../geometry/geometry.h"

CmdArcP::CmdArcP(Context *context)
    : Command(context),
        has_pt_1(false),
        has_pt_2(false)
{ }

CmdArcP::~CmdArcP()
{ }

void CmdArcP::Run()
{
    CMDResult result;

    PrintMessage("Pick first point");
    result = EnterPoint(&pt_1);
    if(result!=RES_OK)
        return;

    has_pt_1 = true;
    PrintMessage("Pick second point");
    result = EnterPoint(&pt_2);
    if(result!=RES_OK)
        return;

    if(pt_1==pt_2)
    {
        result = RES_ERROR;
        return;
    }

    has_pt_2 = true;
    PrintMessage("Pick third point");
    result = EnterPoint(&pt_3);
    if(result!=RES_OK)
        return;

    if(pt_1==pt_3 || pt_2==pt_3)
    {
        result = RES_ERROR;
        return;
    }
    AppendEntity(new Arc(BuildByThreePoints(pt_1, pt_2, pt_3)));
}

void CmdArcP::Redraw(IAdapterDC &dc, double x, double y)
{
    if(has_pt_1 && has_pt_2)
    {
        Point pt(x,y);
        if(pt==pt_2 || pt==pt_1)
            return;

        Arc arc = BuildByThreePoints(pt_1, pt_2, pt);
        const Point &center = arc.GetCenterPoint();
        const Point &start = arc.GetStartPoint();
        const Point &end = arc.GetEndPoint();
        dc.CadDrawConstraintLine(center.GetX(), center.GetY(),
                                 start.GetX(), start.GetY());
        dc.CadDrawConstraintLine(center.GetX(), center.GetY(),
                                 end.GetX(), end.GetY());
        dc.CadDrawConstraintLine(pt_1.GetX(), pt_1.GetY(),
                                 pt_2.GetX(), pt_2.GetY());
        dc.CadDrawConstraintLine(pt_1.GetX(), pt_1.GetY(), x, y);
        arc.Draw(dc);
    }
    else if(has_pt_1)
    {
        dc.CadDrawConstraintLine(pt_1.GetX(), pt_1.GetY(), x, y);
    }
}

Arc CmdArcP::BuildByThreePoints(const Point& p_A,
    const Point& p_B, const Point& p_C)
{
    Line line_a(p_B, p_C);
    Line line_b(p_A, p_C);
    Line line_c(p_A, p_B);
    double a = line_a.GetLength();
    double b = line_b.GetLength();
    double c = line_c.GetLength();

    double k1 = a * a * (b * b + c * c - a * a);
    double k2 = b * b * (a * a + c * c - b * b);
    double k3 = c * c * (b * b + a * a - c * c);

    double Ox = (k1 * p_A.GetX() + k2 * p_B.GetX() + k3 * p_C.GetX()) / (k1 + k2 + k3);
    double Oy = (k1 * p_A.GetY() + k2 * p_B.GetY() + k3 * p_C.GetY()) / (k1 + k2 + k3);

    Point p_center(Ox, Oy);
    double angle_a = geometry::calculate_angle(p_center.GetX(), p_center.GetY(), p_A.GetX(), p_A.GetY());
    double angle_b = geometry::calculate_angle(p_center.GetX(), p_center.GetY(), p_B.GetX(), p_B.GetY());
    double angle_c = geometry::calculate_angle(p_center.GetX(), p_center.GetY(), p_C.GetX(), p_C.GetY());

    Point p_start = p_A;
    Point p_end = p_C;

    // Quadrant
    int quadrant_start = GetQuadrant(Ox, Oy, p_A.GetX(), p_A.GetY());
    int quadrant_middle = GetQuadrant(Ox, Oy, p_B.GetX(), p_B.GetY());
    int quadrant_end = GetQuadrant(Ox, Oy, p_C.GetX(), p_C.GetY());

    // Direction conditions
    
    double opp_angle = angle_a - 180;
    if (opp_angle < 0)
        opp_angle = 360 + opp_angle;

    bool is_reversed = false;
    if (opp_angle > angle_a)
    {
        if(angle_b>opp_angle || angle_b < angle_a)
            is_reversed = true;
    }
    else
    {
        if(angle_b<angle_a && angle_b>opp_angle)
            is_reversed = true;
    }

    if(is_reversed)
        std::swap(p_start, p_end);

    return Arc(p_center, p_start, p_end);
}

// Returns quadrant value
//
//   2      |      1
//          |
// --------------------
//   3      |      4
//          |
//
int CmdArcP::GetQuadrant(double x0, double y0, double x, double y)
{
    int cuadrant = 1; // x>x0, y>y0
    if (x<=x0 && y>=y0)
        cuadrant = 2;
    else if (x <= x0 && y <= y0)
        cuadrant = 3;
    else if (x >= x0 && y <= y0)
        cuadrant = 4;
    return cuadrant;
}

Command* CmdArcP::Clone(Context *context)
{
    return new CmdArcP(context);
}
