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

        virtual void Draw(IAdapterDC &dc) override;
        virtual double DistanceFrom(const Point &pt) const override;
        virtual bool IsNearPoint(const Point &pt, double region_radius) override;
        virtual bool IsInSquare(const Point &top_left, const Point &bottom_right) override;
        virtual void GetSnapPoints(std::vector<Point> &vec) const override;
        virtual void MoveTo(double delta_x, double delta_y, double delta_z = 0.0) override;
        Entity* Clone(void) const override;

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
