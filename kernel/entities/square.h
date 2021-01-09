#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED

#include "entity.h"
#include "point.h"
#include "line.h"

class Square: public Entity
{
    public:
        Square(Point pt, double width, double height);
        virtual ~Square();

        virtual void Draw(IAdapterDC &dc);

        virtual void GetSnapPoints(std::vector<Point> &vec) const;

        virtual void GetCenterPoints(std::vector<Point> &vec) const;

        virtual void GetPrimitives(std::vector<Entity*> &vec);

    protected:

    private:
        Square();

        Point m_center;
        double m_width;
        double m_height;
        Line line_top;
        Line line_left;
        Line line_bottom;
        Line line_right;
};

#endif // SQUARE_H_INCLUDED
