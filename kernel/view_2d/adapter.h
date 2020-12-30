#ifndef ADAPTER_H_INCLUDED
#define ADAPTER_H_INCLUDED

#include "../entities/point.h"

class Adapter
{
    public:
        Adapter();
        virtual ~Adapter();


        virtual void ReDraw(void) = 0;



        // Sets real coordinates for the center of a panel
        // The panel is positioned using center point and width/height values
        void SetCenterPosition(Point point);
        void SetCenterPosition(double x, double y);

        // Returns center point (coordinates) of the panel
        Point GetCenterPosition(void) const;

        // Sets screen size to draft
        // After screen size changed the screen panel is to be refreshed to redraw all entities
        void SetScreenSize(double width, double height);

//        virtual void MoveScreen(double delta_x, double delta_y) = 0;

    protected:

    private:
        Point m_center_coord;
        double m_width;
        double m_height;


};

/**
struct Colour
{
    typedef colour_int_t unsigned char;

    Colour(colour_int r, colour_int g, colour_int b):
        red(r), green(g), blue(b)
    { }

    colour_int_t GetR(void) {return red;}
    colour_int_t GetG(void) {return green;}
    colour_int_t GetB(void) {return blue;}

    private:
        colour_int_t red;
        colour_int_t green;
        colour_int_t blue;
};
**/
#endif // ADAPTER_H_INCLUDED
