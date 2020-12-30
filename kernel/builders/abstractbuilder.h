#ifndef ABSTRACTBUILDER_H_INCLUDED
#define ABSTRACTBUILDER_H_INCLUDED

#include "../entities/point.h"
#include "../entities/entity.h"
#include "../graphics/dc.h"
#include <vector>

// Builder interface for implementing graphical interaction during entity creating.
// An object implementing the interface is to be transferred to the panel where points are picking.
// The builder does not create entity until Create-method is called.
// Uncreated entity can be drawn on screen using Redraw-method.
class AbstractBuilder
{
    public:
        AbstractBuilder()
        { }

        virtual ~AbstractBuilder()
        { }

        // Pushes point value into points vector
        // Returns true if an entity can be created from existing points
        // Otherwise -- false
        virtual bool AppendPoint(const Point &pt) = 0;

        // Redraws unbuilt entity during creating.
        // x, y -- coordinates of mouse cursor to show current entity image
        virtual void Redraw(IAdapterDC &dc, double x, double y) = 0;

        // Creates entity
        // Returns built entity if no errors, otherwise returns null-pointer
        virtual Entity* Create(void) = 0;

        // Is a single entity has to be built
        // or multiply entities has to be built one by one.
        // For example, if we want to draw multiply lines the method should return true
        // and Create-method has to clean all picked points excepting the last one.
        // The last point will be the first point for the next line.
        // Multiply calls for the Create-method can be done in this case.
        // Default value is a single entity creating.
        virtual bool IsMultiBuild(void) const
        {
            return false;
        }

    protected:
        // Picked points for entity drafting
        std::vector<Point> points;
};

#endif // ABSTRACTBUILDER_H_INCLUDED
