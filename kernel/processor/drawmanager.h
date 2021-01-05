#ifndef DRAWMANAGER_H_INCLUDED
#define DRAWMANAGER_H_INCLUDED

#include "../entities/point.h"
#include "../entities/entity.h"
#include "../graphics/dc.h"
#include <vector>
#include <map>
#include <unordered_map>

class DrawManager
{
    public:
        DrawManager();
        virtual ~DrawManager();

        void AddEntity(Entity *entity);

        void DrawAll(IAdapterDC &dc);

        void ShowSnapPoints(IAdapterDC &dc, double x, double y, double snap_radius);

        Point* GetSnapPoint(void) const;

        bool HasPreference(const std::string &pref) const;

        void SetPreference(const std::string &pref, float val);

        float GetPreference(const std::string &pref) const;

    protected:

    private:
        void ShowGrid(IAdapterDC &dc);
        void AppendSnapPointsFor(Entity *entity);
        void AssignDefaultPreferences(void);

        std::unordered_map<std::string,Layer> m_layers;
        Layer *current_layer;

        // Shapes
        std::vector<Entity*> m_elements;
        // Snap points
        Point *m_snap_point;
        std::vector<Point> m_snap_grid;
        std::vector<std::pair<Entity*,Point>> m_snap_points;
        std::vector<std::pair<Entity*,Point>> m_snap_center;
        std::vector<Point> m_snap_intersections;

        // Preferences
        std::map<std::string, float> m_preferences;
};

#endif // DRAWMANAGER_H_INCLUDED
