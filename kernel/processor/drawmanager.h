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

        void SelectInPoint(double x, double y, double snap_radius);

        void DeleteSelection(void);

        void ClearSelection(void);

        void ShowSnapPoints(IAdapterDC &dc, double x, double y, double snap_radius);

        void ShowSnapEntities(IAdapterDC &dc, double x, double y, double snap_radius);

        Point* GetSnapPoint(void) const;

        bool HasPreference(const std::string &pref) const;

        void SetPreference(const std::string &pref, float val);

        float GetPreference(const std::string &pref) const;

    protected:

    private:
        void ShowGrid(IAdapterDC &dc);
        void AppendSnapPointsFor(Entity *entity);
        void RemoveSnapPointsFor(Entity *entity);
        void AssignDefaultPreferences(void);

//        std::vector layer_list;
        std::unordered_map<std::string,Layer> m_layers;
        Layer *current_layer;

        // Shapes
        std::vector<Entity*> m_elements;

        // Data cache for quick access:
        // snap points, entities etc.
        Entity *m_selecting_entity;
        std::vector<Entity*> m_selected_entities;

        // Snap points
        // last found snap point. The value is reset to null-pointer on each screen refresh
        Point *m_snap_point;

        std::vector<Point> m_snap_grid;
        std::vector<std::pair<Entity*,Point>> m_snap_points;
        std::vector<std::pair<Entity*,Point>> m_snap_center;
        std::vector<std::pair<std::pair<Entity*,Entity*>,Point>> m_snap_intersections;

        // Preferences
        std::map<std::string, float> m_preferences;
};

#endif // DRAWMANAGER_H_INCLUDED
