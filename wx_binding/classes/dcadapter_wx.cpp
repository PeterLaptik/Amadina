#include "dcadapter_wx.h"
#include "geometry/intersections.h"
#include "geometry/geometry.h"
#include <wx/graphics.h>

// Default borders positions
static const double DEFAULT_LEFT_BORDER = 0;
static const double DEFAULT_RIGHT_BORDER = 200;
static const double DEFAULT_TOP_BORDER = 200;
static const double DEFAULT_BOTTOM_BORDER = 0;

// Out of screen coordinate value
static const int COORD_OUT_OF_SCREEN = 1;

static const int HIGHLIGHT_THICKNESS = 2;

// Default colours
Colour DEFAULT_COLOUR_BLACK(0,0,0);
Colour DEFAULT_COLOUR_WHITE(255,255,255);


wxAdapterDC::wxAdapterDC(wxWindow *win, wxSize size)
                :wxBufferedPaintDC(win)
{
    m_background_colour = DEFAULT_COLOUR_BLACK;
    m_height = size.GetHeight();
    m_width = size.GetWidth();
    m_borders.left = DEFAULT_LEFT_BORDER;
    m_borders.right = DEFAULT_RIGHT_BORDER;
    m_borders.top = DEFAULT_TOP_BORDER;
    m_borders.bottom = DEFAULT_BOTTOM_BORDER;
    BORDER_MARGIN = cad::geometry::get_border_margin();
    this->SetBrush(wxBrush(*wxTRANSPARENT_BRUSH));
    this->SetPen(wxPen(wxColour(m_colour.R, m_colour.G, m_colour.B)));
    x_scale = (m_borders.right -  m_borders.left)/m_width;
    y_scale = (m_borders.top -  m_borders.bottom)/m_height;
    m_is_highlited = false;
}


wxAdapterDC::~wxAdapterDC()
 { }


void wxAdapterDC::CadClear()
{
   this->Clear();
}

void wxAdapterDC::CadDrawPoint(const Point &pt)
{
    double x = pt.GetX();
    double y = pt.GetY();
    // Is out of screen
    if(x>m_borders.right || x<m_borders.left
       || y>m_borders.top || y<m_borders.bottom)
        return;

    TransformCoordinatesToView(x, y);
    //wxPen pen(5);
    //this->SetPen(pen);
    this->DrawPoint(static_cast<int>(x), static_cast<int>(y));
}

void wxAdapterDC::CadDrawLine(const Point &pt1, const Point &pt2)
{
    CadDrawLine(pt1.GetX(), pt1.GetY(), pt2.GetX(), pt2.GetY());
}


void wxAdapterDC::CadDrawLine(double x1, double y1, double x2, double y2)
{
    // Out of screen check
    if (x1 > m_borders.right - BORDER_MARGIN && x2 > m_borders.right - BORDER_MARGIN)
        return;

    if (y1 > m_borders.top - BORDER_MARGIN && y2 > m_borders.top - BORDER_MARGIN)
        return;

    if (x1 < m_borders.left + BORDER_MARGIN && x2 < m_borders.left + BORDER_MARGIN)
        return;

    if (y1 < m_borders.bottom - BORDER_MARGIN && y2 < m_borders.bottom - BORDER_MARGIN)
        return;

    Point top_left(m_borders.left, m_borders.top);
    Point bottom_right(m_borders.right, m_borders.bottom);
    bool intesects_with_border = cad::geometry::border_intersection(x1, y1, x2, y2, top_left, bottom_right);
    bool is_line_in_screen = IsLineInsideScreen(x1, y1, x2, y2);
    if (!intesects_with_border && !is_line_in_screen)
        return;

    TransformCoordinatesToView(x1, y1, x2, y2);
    DrawLine(static_cast<int>(x1), static_cast<int>(y1),
             static_cast<int>(x2), static_cast<int>(y2));

    // Highlighted
    if(m_is_highlited)
    {
        wxPen current_pen = GetPen();
        wxColour current_colour = current_pen.GetColour();
        wxPen highlight_pen = current_pen;
        wxColour hcolour = GetHighlightColour().Red();

        double length = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
        for(int i=-HIGHLIGHT_THICKNESS; i<HIGHLIGHT_THICKNESS; i++)
        {
            if(i==0)
                continue;

            unsigned char c_val = IncrementColourValue(hcolour.Red(), i*10);
            wxColour col(c_val,c_val,c_val);
            highlight_pen.SetColour(col);
            SetPen(highlight_pen);

            double ax1 = x1 + i*(y2 - y1)/length;
            double ay1 = y1 + i*(x1 - x2)/length;
            double ax2 = x2 + i*(y2 - y1)/length;
            double ay2 = y2 + i*(x1 - x2)/length;
            DrawLine(static_cast<int>(ax1), static_cast<int>(ay1),
             static_cast<int>(ax2), static_cast<int>(ay2));
        }
        SetPen(current_pen);
    }
}

void wxAdapterDC::CadDrawCircle(const Point &pt, const double &radius)
{
    double x = pt.GetX();
    double y = pt.GetY();
    double rad = x + radius;
    double dummy_coord = 0;
    TransformCoordinatesToView(x, y, rad, dummy_coord);
    DrawCircle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(rad - x));

    // Highlighted
    if(m_is_highlited)
    {
        wxPen current_pen = GetPen();
        wxColour current_colour = current_pen.GetColour();
        wxPen highlight_pen = current_pen;
        wxColour hcolour = GetHighlightColour().Red();

        for(int i=-HIGHLIGHT_THICKNESS; i<HIGHLIGHT_THICKNESS; i++)
        {
            if(i==0)
                continue;

            unsigned char c_val = IncrementColourValue(hcolour.Red(), i*10);
            wxColour col(c_val,c_val,c_val);
            highlight_pen.SetColour(col);
            SetPen(highlight_pen);
            DrawCircle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(rad - x + i));
        }
        SetPen(current_pen);
    }
}

static const double CURVE_SMOOTH = 0.1;
static const int STEP_NUMBER = 2*3.14/CURVE_SMOOTH;

void wxAdapterDC::CadDrawEllipse(double x1, double y1, double x2, double y2, double a, double b)
{
    if(x1>x2)
        std::swap(x1,x2);
    if(y2>y1)
        std::swap(y1,y2);

    Point points[STEP_NUMBER];
    double delta_x = x1 + (x2 - x1)/2;
    double delta_y = y1 + (y2 - y1)/2;

    double e = sqrt(1 - b*b/(a*a));

    double angle = geometry::calculate_angle_rad(x1, y1, x2, y2);

    double t = -3.14;
    for(int i=0; i<STEP_NUMBER; i++)
    {
        double A = e*e/8 + e*e*e*e/16 + 71*e*e*e*e*e*e/2048;
        double B = 5*e*e*e*e/256 + 5*e*e*e*e*e*e/256;
        double C = 29*e*e*e*e*e*e/6144;
        double teta = t + A*sin(2*t) + B*sin(4*t) + C*sin(6*t);

        //double x = delta_x + a*cos(t);
        //double y = delta_y + b*sin(t);

        //double rot_x = x*cos(angle) - y*sin(angle);
        //double rot_y = y*sin(angle) + y*cos(angle);

        double x = a*cos(t);
        double y = b*sin(t);

        angle = 3.14/4;
        //x = x*cos(angle) - y*sin(angle);
        //y = -x*sin(angle) + y*cos(angle);

        x += delta_x;
        y += delta_y;

        t += CURVE_SMOOTH;
        points[i] = Point(x, y);
    }

    // Draw by multi-lines
    for(int i=0; i<STEP_NUMBER-1; i++)
    {
        CadDrawLine(points[i], points[i+1]);
    }
    CadDrawLine(points[0], points[STEP_NUMBER-1]);
}

void wxAdapterDC::CadDrawArc(const Point &pt_center, const Point &pt_start, const Point &pt_end)
{
    double xc = pt_center.GetX();
    double yc = pt_center.GetY();
    double x1 = pt_start.GetX();
    double y1 = pt_start.GetY();
    double x2 = pt_end.GetX();
    double y2 = pt_end.GetY();
    TransformCoordinatesToView(xc, yc);
    TransformCoordinatesToView(x1, y1);
    TransformCoordinatesToView(x2, y2);
    DrawArc(x1, y1, x2, y2, xc, yc);

    // Highlighted
    if(m_is_highlited)
    {
        wxPen current_pen = GetPen();
        wxColour current_colour = current_pen.GetColour();
        wxPen highlight_pen = current_pen;
        wxColour hcolour = GetHighlightColour().Red();

        double angle_1 = geometry::calculate_angle(xc, yc, x1, y1);
        double angle_2 = geometry::calculate_angle(xc, yc, x2, y2);
        angle_1 = angle_1*3.14/180;
        angle_2 = angle_2*3.14/180;

        for(int i=-HIGHLIGHT_THICKNESS; i<HIGHLIGHT_THICKNESS; i++)
        {
            if(i==0)
                continue;

            unsigned char c_val = IncrementColourValue(hcolour.Red(), i*10);
            wxColour col(c_val,c_val,c_val);
            highlight_pen.SetColour(col);
            SetPen(highlight_pen);
            x1 += i*cos(angle_1);
            y1 += i*sin(angle_1);
            x2 += i*cos(angle_2);
            y2 += i*sin(angle_2);
            DrawArc(x1, y1, x2, y2, xc, yc);
        }
        SetPen(current_pen);
    }
}

// Shows dot-line as a constraint line
void wxAdapterDC::CadDrawConstraintLine(double x1, double y1, double x2, double y2)
{
    double x_val, y_val;
    double distance = pow(pow(x1 - x2, 2) + pow(y1 - y2, 2), 0.5);
    int pixel_num = static_cast<int>(distance/x_scale/10);
    if(pixel_num<2)
        return;

    double start_x = x2;
    double start_y = y2;
    double delta_x = (x1 - x2)/pixel_num;
    double delta_y = (y1 - y2)/pixel_num;
    for(int step=0; step<pixel_num; step++)
    {
        x_val = start_x + delta_x*step;
        y_val = start_y + delta_y*step;
        TransformCoordinatesToView(x_val, y_val);
        this->DrawPoint(static_cast<int>(x_val), static_cast<int>(y_val));
    }
}

static const int HIGHLIGHT_DELTA = 30;

void wxAdapterDC::CadDrawConstraintSquare(double x1, double y1, double x2, double y2)
{
    int sign = m_background_colour.IsDark() ? +1 : -1;
    Colour::colour_t red = m_background_colour.R + sign*HIGHLIGHT_DELTA;
    Colour::colour_t green = m_background_colour.G + sign*HIGHLIGHT_DELTA;
    Colour::colour_t blue = m_background_colour.B + sign*HIGHLIGHT_DELTA;
    wxColour brush_colour(red, green, blue);

    wxBrush brush(wxBRUSHSTYLE_SOLID);
    brush.SetColour(brush_colour);
    SetBrush(brush);
    TransformCoordinatesToView(x1, y1);
    TransformCoordinatesToView(x2, y2);
    double coord_x = std::min(x1, x2);
    double coord_y = std::min(y1, y2);
    double width = fabs(x1-x2);
    double height = fabs(y1-y2);
    DrawRectangle(coord_x, coord_y, width, height);
    brush.SetStyle(wxBRUSHSTYLE_TRANSPARENT);
    SetBrush(brush);
}

// Transforms coordinates from real values to device coordinates
void wxAdapterDC::TransformCoordinatesToView(double &x, double &y) const
{
    x = m_width*(x - m_borders.left)/(m_borders.right - m_borders.left);
    y = m_height*(y - m_borders.bottom)/(m_borders.top - m_borders.bottom);
    y = m_height - y;
}

// Transforms coordinates from real values to device coordinates
void wxAdapterDC::TransformCoordinatesToView(double &x1, double &y1, double &x2, double &y2) const
{
    TransformCoordinatesToView(x1, y1);
    TransformCoordinatesToView(x2, y2);
}

bool wxAdapterDC::IsLineInsideScreen(const double& x1, const double& y1,
                                     const double& x2, const double& y2) const
{
    double x_left = std::min(x1, x2);
    double x_right = std::max(x1, x2);
    double y_top = std::max(y1, y2);
    double y_bottom = std::min(y1, y2);
    return (x_right<m_borders.right - BORDER_MARGIN
            && x_left>m_borders.left + BORDER_MARGIN
            && y_top<m_borders.top - BORDER_MARGIN
            && y_bottom>m_borders.bottom + BORDER_MARGIN);
}

void wxAdapterDC::SetBorders(double left, double right, double top, double bottom)
{
    m_borders.left = left;
    m_borders.right = right;
    m_borders.top = top;
    m_borders.bottom = bottom;
    x_scale = (m_borders.right -  m_borders.left)/m_width;
    y_scale = (m_borders.top -  m_borders.bottom)/m_height;
}

void wxAdapterDC::CadSetLayer(Layer *layer)
{
    m_layer = layer;
}

void wxAdapterDC::CadSetColour(const Colour &colour)
{
    m_colour = colour;
    m_colour.CheckAndInverse(m_colours.background);
    wxPen updated_pen = GetPen();
    updated_pen.SetColour(wxColour(m_colour.R, m_colour.G, m_colour.B));
    SetPen(updated_pen);
}

const Colour& wxAdapterDC::GetBackgroundColour(void) const
{
    return m_colours.background;
}

void wxAdapterDC::SetBackgroundColour(const Colour &colour)
{
    m_colours.background = colour;
}

void wxAdapterDC::CadSetHighlited(bool is_highlited)
{
    m_is_highlited = is_highlited;
    //wxPen updated_pen = GetPen();
    //updated_pen.SetStyle(wxPENSTYLE_STIPPLE);
    //updated_pen.SetJoin(wxJOIN_ROUND);
    //SetPen(updated_pen);
}

wxColour wxAdapterDC::GetHighlightColour() const
{
    unsigned char colour = m_background_colour.R>120 ? 100 : 220;
    return wxColour(colour,colour,colour);
}

unsigned int wxAdapterDC::IncrementColourValue(unsigned int val, int step) const
{
    val += fabs(step);
    if(val>255)
        val = 255;
    return val;
}
