#include "intersections.h"
#include "../entities/point.h"
#include "../entities/line.h"
#include "../entities/circle.h"
#include <math.h>
#include <float.h>

static const int DEFAULT_BORDER_MARGIN = 0;

int cad::geometry::get_border_margin()
{
    return DEFAULT_BORDER_MARGIN;
}

void cad::geometry::calculate_intersections(Entity *entity_1, Entity *entity_2, std::vector<Point> &points)
{
    Line *line_1 = dynamic_cast<Line*>(entity_1);
    Line *line_2 = dynamic_cast<Line*>(entity_2);
    Circle *circle_1 = dynamic_cast<Circle*>(entity_1);
    Circle *circle_2 = dynamic_cast<Circle*>(entity_2);

    // Line-line intersection
    if(line_1 && line_2)
        intersections(line_1, line_2, points);
    // Circle-line intersection
    if(line_1 && circle_2)
        intersections(line_1, circle_2, points);
    if(circle_1 && line_2)
        intersections(line_2, circle_1, points);
    // Circle-circle intersection
    if(circle_1 && circle_2)
        intersections(circle_1, circle_2, points);
}

// Line-line intersection
void cad::geometry::intersections(Line *line_1, Line *line_2, std::vector<Point> &points)
{
    double x1, x2, y1, y2;
    double x3, x4, y3, y4;

    // First line
    const Point &pt_start_1 = line_1->GetStartPoint();
    const Point &pt_end_1 = line_1->GetEndPoint();
    x1 = pt_start_1.GetX();
    y1 = pt_start_1.GetY();
    x2 = pt_end_1.GetX();
    y2 = pt_end_1.GetY();
    if(x1>x2)
    {
        std::swap(x1,x2);
        std::swap(y1,y2);
    }

    // Second line
    const Point &pt_start_2 = line_2->GetStartPoint();
    const Point &pt_end_2 = line_2->GetEndPoint();
    x3 = pt_start_2.GetX();
    y3 = pt_start_2.GetY();
    x4 = pt_end_2.GetX();
    y4 = pt_end_2.GetY();
    if(x3>x4)
    {
        std::swap(x3,x4);
        std::swap(y3,y4);
    }

    double t_denominator = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
    double u_denominator = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
    if((t_denominator==0)||(u_denominator==0))
        return;

    double t = ((x1 - x3)*(y3 - y4) - (y1 - y3)*(x3 - x4))/t_denominator;
    double u = -((x1 - x2)*(y1 - y3) - (y1 - y2)*(x1 - x3))/u_denominator;
    double x = x1 + t*(x2 - x1);
    double y = y1 + t*(y2 - y1);

    if((t>=0.0)&&(t<=1.0)&&(u>=0.0)&&(u<=1.0))
        points.push_back(Point(x,y));
}

// Line-circle intersection
void cad::geometry::intersections(Line *line, Circle *circle, std::vector<Point> &points)
{
    const Point &pt_1 = line->GetStartPoint();
    const Point &pt_2 = line->GetEndPoint();

    double x1 = pt_1.GetX();
    double y1 = pt_1.GetY();
    double x2 = pt_2.GetX();
    double y2 = pt_2.GetY();
    if(x1>x2)
    {
        std::swap(x1,x2);
        std::swap(y1,y2);
    }

    double x0 = circle->GetCenterPoint().GetX();
    double y0 = circle->GetCenterPoint().GetY();
    double r = circle->GetRadius();

    double A = y2 - y1;
    double B = x1 - x2;
    double C = x2*y1 - x1*y2;

    // Vertical line case
    if(fabs(B)<DBL_EPSILON)
    {
        // Out of circle
        if(fabs(x0-x1)>r)
            return;

        double na = 1;
        double nb = -2*y0;
        double nc = pow(y0,2) - pow(r,2) + pow(x0,2) + pow(x1,2) - 2*x1*x0;
        double nsq_val = pow(nb,2) - 4*na*nc;
        if(nsq_val<0)   // no roots
            return;

        if(y1>y2)
            std::swap(y1,y2);

        double y = (-nb + sqrt(nsq_val))/(2*na);
        if((y<=y2)&&(y>=y1))
            points.push_back(Point(x1, y));
        // One root case
        if(fabs(nsq_val)<DBL_EPSILON)
            return;

        y = (-nb - sqrt(nsq_val))/(2*na);
        if((y<=y2)&&(y>=y1))
            points.push_back(Point(x1, y));
        return;
    }

    // General case
    double a = pow(A,2) + pow(B,2);
    double b = 2*A*C + 2*A*B*y0 - 2*pow(B,2)*x0;
    double c = pow(C,2) + 2*B*C*y0 - pow(B,2)*(pow(r,2) - pow(x0,2) - pow(y0,2));

    double sq_val = pow(b,2) - 4*a*c;
    if(sq_val<0)
        return;

    double x = (-b + sqrt(sq_val))/(2*a);
    double y = -(A*x + C)/B;
    if((x1<=x)&&(x2>=x))
        points.push_back(Point(x, y));

    // Whether the entities has only one intersection point
    if(fabs(x)<DBL_EPSILON)
        return;

    x = (-b - sqrt(sq_val))/(2*a);
    y = -(A*x + C)/B;
    if((x1<=x)&&(x2>=x))
        points.push_back(Point(x, y));
}

void cad::geometry::intersections(Circle *circle_1, Circle *circle_2, std::vector<Point> &points)
{
    Point pt1 = circle_1->GetCenterPoint();
    Point pt2 = circle_2->GetCenterPoint();

    double x0 = pt1.GetX();
    double y0 = pt1.GetY();
    double x1 = pt2.GetX();
    double y1 = pt2.GetY();
    double r0 = circle_1->GetRadius();
    double r1 = circle_2->GetRadius();

    double d = pow((pow(x1-x0,2) + pow(y1-y0,2)), 0.5);
    if((d>(r0+r1))||(d<fabs(r1-r0))||(fabs(d)<=DBL_EPSILON))
        return; // no intersections or the circles matches to each other

    double a = (pow(r0,2) - pow(r1,2) + pow(d,2))/(2*d);
    double h = sqrt(pow(r0,2) - pow(a,2));

    double x2 = x0 + a*(x1 - x0)/d;
    double y2 = y0 + a*(y1 - y0)/d;

    double x = x2 + h*(y1 - y0)/d;
    double y = y2 - h*(x1 - x0)/d;
    points.push_back(Point(x,y));

    x = x2 - h*(y1 - y0)/d;
    y = y2 + h*(x1 - x0)/d;
    points.push_back(Point(x,y));
}


bool cad::geometry::border_intersection(double &x1, double &y1, double &x2, double &y2,
                                        const Point &top_left, const Point &bottom_right)
{
    Point point;
    Line line(x1, y1, x2, y2);
    bool has_intersections = false;

    Line right(bottom_right.GetX() - DEFAULT_BORDER_MARGIN, bottom_right.GetY() + DEFAULT_BORDER_MARGIN,
               bottom_right.GetX() - DEFAULT_BORDER_MARGIN, top_left.GetY() - DEFAULT_BORDER_MARGIN);
    if (line_line_intersection(line, right, point))
    {
        has_intersections = true;
        if (x1 > x2)
        {
            x1 = point.GetX();
            y1 = point.GetY();
        }
        else
        {
            x2 = point.GetX();
            y2 = point.GetY();
        }
    }

    Line top(bottom_right.GetX() - DEFAULT_BORDER_MARGIN, top_left.GetY() - DEFAULT_BORDER_MARGIN,
             top_left.GetX() + DEFAULT_BORDER_MARGIN, top_left.GetY() - DEFAULT_BORDER_MARGIN);
    if (line_line_intersection(line, top, point))
    {
        has_intersections = true;
        if (y1 > y2)
        {
            x1 = point.GetX();
            y1 = point.GetY();
        }
        else
        {
            x2 = point.GetX();
            y2 = point.GetY();
        }
    }

    Line left(top_left.GetX() + DEFAULT_BORDER_MARGIN, top_left.GetY() - DEFAULT_BORDER_MARGIN,
              top_left.GetX() + DEFAULT_BORDER_MARGIN, bottom_right.GetY() + DEFAULT_BORDER_MARGIN);
    if (line_line_intersection(line, left, point))
    {
        has_intersections = true;
        if (x1 < x2)
        {
            x1 = point.GetX();
            y1 = point.GetY();
        }
        else
        {
            x2 = point.GetX();
            y2 = point.GetY();
        }
    }

    Line bottom(top_left.GetX() + DEFAULT_BORDER_MARGIN, bottom_right.GetY() + DEFAULT_BORDER_MARGIN,
                bottom_right.GetX() - DEFAULT_BORDER_MARGIN, bottom_right.GetY() + DEFAULT_BORDER_MARGIN);
    if (line_line_intersection(line, bottom, point))
    {
        has_intersections = true;
        if (y1 < y2)
        {
            x1 = point.GetX();
            y1 = point.GetY();
        }
        else
        {
            x2 = point.GetX();
            y2 = point.GetY();
        }
    }
    return has_intersections;
}

bool cad::geometry::line_line_intersection(const Line& line_1, const Line& line_2, Point& p)
{
    double x1, x2, y1, y2;
    double x3, x4, y3, y4;

    // First line
    const Point& pt_start_1 = line_1.GetStartPoint();
    const Point& pt_end_1 = line_1.GetEndPoint();
    x1 = pt_start_1.GetX();
    y1 = pt_start_1.GetY();
    x2 = pt_end_1.GetX();
    y2 = pt_end_1.GetY();
    if (x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    // Second line
    const Point& pt_start_2 = line_2.GetStartPoint();
    const Point& pt_end_2 = line_2.GetEndPoint();
    x3 = pt_start_2.GetX();
    y3 = pt_start_2.GetY();
    x4 = pt_end_2.GetX();
    y4 = pt_end_2.GetY();
    if (x3 > x4)
    {
        std::swap(x3, x4);
        std::swap(y3, y4);
    }

    double t_denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    double u_denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if ((t_denominator == 0) || (u_denominator == 0))
        return false;

    double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / t_denominator;
    double u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / u_denominator;
    double x = x1 + t * (x2 - x1);
    double y = y1 + t * (y2 - y1);

    if ((t >= 0.0) && (t <= 1.0) && (u >= 0.0) && (u <= 1.0))
    {
        p.SetX(x);
        p.SetY(y);
        return true;
    }
    return false;
}
