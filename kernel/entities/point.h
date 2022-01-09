#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include "entity.h"
#include "../graphics/dc.h"
#include "../api/exports.h"

class DLL_EXPORT Point: public Entity
{
    public:
        Point();

        Point(double x_coord, double y_coord, double z_coord = 0);

        virtual ~Point();

        bool operator==(const Point &pt);

        virtual void Draw(IAdapterDC &dc);

        virtual void DrawHighlighted(IAdapterDC &dc);

        virtual double DistanceFrom(const Point &pt) const;

        static double GetDistanceBetween(const Point &pt1, const Point &pt2);

        void GetSnapPoints(std::vector<Point> &vec) const;

        Entity* Clone(void);

        void SetX(double x_coord) {x = round(x_coord*1000)/1000;}
        void SetY(double y_coord) {y = round(y_coord*1000)/1000;}
        void SetZ(double z_coord) {z = round(z_coord*1000)/1000;}

        double GetX(void) const {return x;}
        double GetY(void) const {return y;}
        double GetZ(void) const {return z;}

    private:
        double x;
        double y;
        double z;
};

#endif // POINT_H_INCLUDED
