#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED

#include "entity.h"
#include "point.h"

class Square: public Entity
{
    public:
        Square(Point pt, double width, double height);
        virtual ~Square();

        virtual void Draw(IAdapterDC &dc);

        virtual void GetSnapPoints(std::vector<Point> &vec) const;

        virtual void GetCenterPoints(std::vector<Point> &vec) const;

    protected:

    private:
        Square();

        Point m_center;
        double m_width;
        double m_height;
};

#endif // SQUARE_H_INCLUDED
