#include "circlep_cmd.h"
#include "../entities/line.h"
#include "../entities/circle.h"
#include "../geometry/geometry.h"

CmdCircleP::CmdCircleP(Context *context)
    : Command(context),
        m_pt_1_picked(false),
        m_pt_2_picked(false)
{ }

CmdCircleP::~CmdCircleP()
{ }

void CmdCircleP::Run(void)
{
    CMDResult result;
    PrintMessage("Pick first point");
    result = EnterPoint(&pt1);
    if(result!=RES_OK)
        return;

    m_pt_1_picked = true;
    PrintMessage("Pick second point");
    result = EnterPoint(&pt2);
    if(result!=RES_OK)
        return;

    m_pt_2_picked = true;
    PrintMessage("Pick third point");
    result = EnterPoint(&pt3);
    if(result!=RES_OK)
        return;

    Circle circle = BuildCircle(pt3.GetX(), pt3.GetY());
    AppendEntity(circle.Clone());
}

void CmdCircleP::Redraw(IAdapterDC &dc, double x, double y)
{
    if(!m_pt_1_picked)
        return;

    if(!m_pt_2_picked)
    {
        dc.CadDrawConstraintLine(pt1.GetX(), pt1.GetY(), x, y);
    }
    else
    {
        dc.CadDrawConstraintLine(pt1.GetX(), pt1.GetY(), pt2.GetX(), pt2.GetY());
        dc.CadDrawConstraintLine(pt1.GetX(), pt1.GetY(), x, y);
        dc.CadDrawConstraintLine(pt2.GetX(), pt2.GetY(), x, y);
        Circle circle = BuildCircle(x, y);
        circle.Draw(dc);
    }
}

Circle CmdCircleP::BuildCircle(double x, double y)
{
    Point pt_current(x,y);
    Line line_a(pt2, pt_current);
    Line line_b(pt1, pt_current);
    Line line_c(pt1, pt2);
    double a = line_a.GetLength();
    double b = line_b.GetLength();
    double c = line_c.GetLength();

    double k1 = a * a * (b * b + c * c - a * a);
    double k2 = b * b * (a * a + c * c - b * b);
    double k3 = c * c * (b * b + a * a - c * c);

    double Ox = (k1 * pt1.GetX() + k2 * pt2.GetX() + k3 * pt_current.GetX()) / (k1 + k2 + k3);
    double Oy = (k1 * pt1.GetY() + k2 * pt2.GetY() + k3 * pt_current.GetY()) / (k1 + k2 + k3);

    Point p_center(Ox, Oy);
    double radius = geometry::calculate_distance(Ox, Oy,
                                pt_current.GetX(), pt_current.GetY());

    return Circle(p_center, radius);
}

Command* CmdCircleP::Clone(Context *context)
{
    return new CmdCircleP(context);
}
