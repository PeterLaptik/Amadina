#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include "entity.h"
#include "../graphics/dc.h"

class Point: public Entity
{
    public:
        Point():
            x(0), y(0), z(0)
        { }

        Point(double x_coord, double y_coord, double z_coord = 0):
            x(x_coord), y(y_coord), z(z_coord)
        { }

        virtual ~Point()
        { }

//        Point& operator=(Point p) volatile
//        {
//            x = p.x;
//            y = p.y;
//            z = p.z;
//            return *this;
//        }

        bool operator==(const Point &pt);

        virtual void Draw(IAdapterDC &dc);

        virtual void DrawHighlighted(IAdapterDC &dc);

        virtual double DistanceFrom(const Point &pt) const;

        static double GetDistanceBetween(const Point &pt1, const Point &pt2);

        void GetSnapPoints(std::vector<Point> &vec) const;

        void SetX(double x_coord) {x = x_coord;}
        void SetY(double y_coord) {y = y_coord;}
        void SetZ(double z_coord) {z = z_coord;}

        double GetX(void) const {return x;}
        double GetY(void) const {return y;}
        double GetZ(void) const {return z;}

    private:
        double x;
        double y;
        double z;
};

#endif // POINT_H_INCLUDED
