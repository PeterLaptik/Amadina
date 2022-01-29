#ifndef ARC_H_INCLUDED
#define ARC_H_INCLUDED

#include "entity.h"
#include "point.h"

class Arc: public Entity
{
    public:
        Arc(const Point &center,
            const Point &start,
            const Point &end);

        virtual ~Arc();

        virtual void Draw(IAdapterDC &dc) override;
        virtual void DrawHighlighted(IAdapterDC &dc) override;
        virtual bool IsNearPoint(const Point &pt, double region_radius) override;
        virtual double DistanceFrom(const Point &pt) const override;
        virtual void GetSnapPoints(std::vector<Point> &vec) const override;
        virtual void GetCenterPoints(std::vector<Point> &vec) const override;
        virtual void MoveTo(double delta_x, double delta_y, double delta_z = 0.0) override;
        virtual Entity* Clone(void) const override;

        const Point& GetCenterPoint(void) const;
        const Point& GetStartPoint(void) const;
        const Point& GetEndPoint(void) const;

    private:
        Point m_center;
        Point m_start;
        Point m_end;
        double m_radius;
        double m_start_angle;
        double m_end_angle;

};

#endif // ARC_H_INCLUDED
