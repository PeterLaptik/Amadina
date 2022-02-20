#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "../graphics/dc.h"
#include "layer.h"
#include <limits>
#include <vector>
#include <set>
#include "../api/exports.h"

// Abstract entity that can be drawn on a screen
// Each element of a drawing has to implement the interface
class DLL_EXPORT Entity
{
    public:
        Entity();

        virtual ~Entity();

        // Main drawing routine
        virtual void Draw(IAdapterDC &dc) = 0;

        // TODO
        // Add quick computing flag
        // Remove default implementation
        // Returns minimum distance between the entity and point
        virtual double DistanceFrom(const Point&) const
        {
            return std::numeric_limits<double>::max();
        }

        virtual bool IsNearPoint(const Point &pt, double region_radius) = 0;

        // Is entity in square
        virtual bool IsInSquare(const Point &top_left, const Point &bottom_right) = 0;

        // TODO change extarnal calls of manager to this method
        virtual bool IsCloseTo(const Point&) const
        {
            return false;
        }

        // Returns points for snap to constraints, edge points etc.
        virtual void GetSnapPoints(std::vector<Point>&) const
        { }

        // Returns points for snap to center
        virtual void GetCenterPoints(std::vector<Point>&) const
        { }

        // Returns pointers to sub-shapes (primitives).
        // The method has to be overridden for composite objects.
        // Primitive sub-shapes are: line, circle, point.
        // The result can be used for intersections computing, geometric transformations etc.
        virtual void GetPrimitives(std::vector<Entity*>& vec)
        {
            vec.push_back(this);
        }

        virtual Entity* Clone(void) const = 0;

        // TODO
        // Remove default implementation
        virtual void MoveTo(double delta_x, double delta_y, double delta_z = 0.0) = 0;

        void SetLayer(Layer *layer);
        Layer* GetLayer(void) const;

    protected:
        Layer *m_layer;
        int m_id;
        static std::set<int> m_id_cash;
};

#endif // ENTITY_H_INCLUDED
