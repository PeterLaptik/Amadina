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
        virtual void Draw(IAdapterDC &dc);
        void DrawHighlighted(IAdapterDC &dc);
        double DistanceFrom(const Point &pt) const;
        void GetSnapPoints(std::vector<Point> &vec) const;
        void GetCenterPoints(std::vector<Point> &vec) const;
        virtual void MoveTo(double delta_x, double delta_y, double delta_z = 0.0) override;
        const Point& GetCenterPoint(void) const;
        const Point& GetStartPoint(void) const;
        const Point& GetEndPoint(void) const;
        virtual Entity* Clone(void);

    private:
        Point m_center;
        Point m_start;
        Point m_end;
        double m_start_angle;
        double m_end_angle;

};

#endif // ARC_H_INCLUDED
