#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "../graphics/dc.h"
#include "layer.h"
#include <vector>
#include <set>

// Abstract entity that can be drawn on a screen
// Each element of a drawing has to implement the interface
class Entity
{
    public:
        Entity();

        virtual ~Entity();

        // Main drawing routine
        virtual void Draw(IAdapterDC &dc) = 0;

        // Getting points for snap and edit
        // Each entity is able to push its own points for snapping
        virtual void GetSnapPoints(std::vector<std::pair<Entity*, Point>> &vec)
        { }

        // Points for snap to center
        virtual void GetCenterPoints(std::vector<std::pair<Entity*, Point>> &vec)
        { }

        void SetLayer(Layer *layer);
        Layer* GetLayer(void) const;

    protected:
        Layer *m_layer;
        int m_id;
        static std::set<int> m_id_cash;
};

#endif // ENTITY_H_INCLUDED
