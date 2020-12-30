#include "dcadapter_wx.h"

// Default borders positions
static const double DEFAULT_LEFT_BORDER = 0;
static const double DEFAULT_RIGHT_BORDER = 200;
static const double DEFAULT_TOP_BORDER = 200;
static const double DEFAULT_BOTTOM_BORDER = 0;

// Out of screen coordinate value
static const int COORD_OUT_OF_SCREEN = 1;


wxAdapterDC::wxAdapterDC(wxWindow *win, wxSize size)
                :wxBufferedPaintDC(win)
{
    m_height = size.GetHeight();
    m_width = size.GetWidth();
    m_borders.left = DEFAULT_LEFT_BORDER;
    m_borders.right = DEFAULT_RIGHT_BORDER;
    m_borders.top = DEFAULT_TOP_BORDER;
    m_borders.bottom = DEFAULT_BOTTOM_BORDER;
    this->SetBrush(wxBrush(*wxTRANSPARENT_BRUSH));
    this->SetPen(wxPen(wxColour(m_colour.R, m_colour.G, m_colour.B)));
}


wxAdapterDC::~wxAdapterDC()
 { }


void wxAdapterDC::CadDrawPoint(const Point &pt)
{
    double x = pt.GetX();
    double y = pt.GetY();
    TransformCoordinatesToView(x, y);

    //wxPen pen(5);
    //this->SetPen(pen);

    this->DrawPoint(static_cast<int>(x), static_cast<int>(y));
}

void wxAdapterDC::CadDrawLine(const Point &pt1, const Point &pt2)
{
    double x1 = pt1.GetX();
    double y1 = pt1.GetY();
    TransformCoordinatesToView(x1, y1);
    double x2 = pt2.GetX();
    double y2 = pt2.GetY();
    TransformCoordinatesToView(x2, y2);
    this->DrawLine(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));
}

void wxAdapterDC::CadDrawLine(double x1, double y1, double x2, double y2)
{
    TransformCoordinatesToView(x1, y1, x2, y2);
    this->DrawLine(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));
}

void wxAdapterDC::CadDrawCircle(const Point &pt, const double &radius)
{
    double x = pt.GetX();
    double y = pt.GetY();
    double rad = x + radius;
    double dummy_coord = 0;
    TransformCoordinatesToView(x, y, rad, dummy_coord);
    this->DrawCircle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(rad - x));
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

void wxAdapterDC::SetBorders(double left, double right, double top, double bottom)
{
    m_borders.left = left;
    m_borders.right = right;
    m_borders.top = top;
    m_borders.bottom = bottom;
}

void wxAdapterDC::GetBorders(double *left, double *right, double *top, double *bottom) const
{
    *left = m_borders.left;
    *right = m_borders.right;
    *top = m_borders.top;
    *bottom = m_borders.bottom;
}

void wxAdapterDC::CadSetColour(const Colour &colour)
{
    m_colour = colour;
    this->SetPen(wxPen(wxColour(m_colour.R, m_colour.G, m_colour.B)));
}
