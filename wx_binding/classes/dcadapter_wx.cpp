#include "dcadapter_wx.h"
#include "geometry/intersections.h"

// Default borders positions
static const double DEFAULT_LEFT_BORDER = 0;
static const double DEFAULT_RIGHT_BORDER = 200;
static const double DEFAULT_TOP_BORDER = 200;
static const double DEFAULT_BOTTOM_BORDER = 0;

// Out of screen coordinate value
static const int COORD_OUT_OF_SCREEN = 1;

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
}

void wxAdapterDC::CadDrawCircle(const Point &pt, const double &radius)
{
    double x = pt.GetX();
    double y = pt.GetY();
    double rad = x + radius;
    double dummy_coord = 0;
    TransformCoordinatesToView(x, y, rad, dummy_coord);
    DrawCircle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(rad - x));
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
void wxAdapterDC::TransformCoordinatesToView(double &x, double &y)
{
    x = m_width*(x - m_borders.left)/(m_borders.right - m_borders.left);
    y = m_height*(y - m_borders.bottom)/(m_borders.top - m_borders.bottom);
    y = m_height - y;
}

// Transforms coordinates from real values to device coordinates
void wxAdapterDC::TransformCoordinatesToView(double &x1, double &y1, double &x2, double &y2)
{
    TransformCoordinatesToView(x1, y1);
    TransformCoordinatesToView(x2, y2);
}

bool wxAdapterDC::IsLineInsideScreen(const double& x1, const double& y1, const double& x2, const double& y2)
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
    this->SetPen(wxPen(wxColour(m_colour.R, m_colour.G, m_colour.B)));
}

const Colour& wxAdapterDC::GetBackgroundColour(void) const
{
    return m_colours.background;
}

void wxAdapterDC::SetBackgroundColour(const Colour &colour)
{
    m_colours.background = colour;
}

