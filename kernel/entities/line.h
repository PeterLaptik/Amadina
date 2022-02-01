#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include "entity.h"
#include "point.h"
#include "../geometry/intersections.h"
#include "../api/exports.h"

// Forward declaration for intersections calculations
class Circle;

class DLL_EXPORT Line: public Entity
{
    public:
        Line();
        Line(const Point &pt1, const Point &pt2);
        Line(const double &x1, const double &y1, const double &x2, const double &y2);
        virtual ~Line();

        virtual void Draw(IAdapterDC &dc) override;
        virtual void DrawHighlighted(IAdapterDC &dc) override;
        virtual bool IsNearPoint(const Point &pt, double region_radius) override;
        virtual bool IsInSquare(const Point &top_left, const Point &bottom_right) override;
        virtual double DistanceFrom(const Point &pt) const override;
        virtual void GetSnapPoints(std::vector<Point> &vec) const override;
        virtual void GetCenterPoints(std::vector<Point> &vec) const override;
        virtual void MoveTo(double delta_x, double delta_y, double delta_z = 0.0) override;
        virtual Entity* Clone(void) const override;

        void SetStartPoint(const Point &pt);
        void SetEndPoint(const Point &pt);
        const Point& GetStartPoint(void) const;
        const Point& GetEndPoint(void) const;
        double GetLength(void) const;

    protected:

    private:
        inline void CalculateLength(void);
        Point m_pt1;
        Point m_pt2;
        double m_length;
};

#endif // LINE_H_INCLUDED
