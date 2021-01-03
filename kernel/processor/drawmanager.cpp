#include "drawmanager.h"
#include "default_commands.h"

DrawManager::DrawManager()
        : snap_point(nullptr)
{
    // Create default layer
    std::string DEFAULT_LAYER_NAME = "Default";
    Layer layer(DEFAULT_LAYER_NAME);
    m_layers.insert(std::pair<std::string,Layer>(DEFAULT_LAYER_NAME, layer));
    current_layer = &(m_layers.find(DEFAULT_LAYER_NAME)->second);
    AssignDefaultPreferences();
}

DrawManager::~DrawManager()
{
    for(std::vector<Entity*>::iterator it=m_elements.begin(); it!=m_elements.end(); ++it)
        delete (*it);
}

void DrawManager::AddEntity(Entity *entity)
{
    if(!entity)
        return;

    entity->SetLayer(current_layer);
    m_elements.push_back(entity);
    AppendSnapPointsFor(entity);

}

void DrawManager::DrawAll(IAdapterDC &dc)
{
    Colour default_black(255,255,255);
    snap_point = nullptr;
    for(std::vector<Entity*>::iterator it=m_elements.begin(); it!=m_elements.end(); ++it)
    {
        dc.CadSetColour(default_black);
        (*it)->Draw(dc);
    }
}

void DrawManager::ShowSnapPoints(IAdapterDC &dc, double x, double y, double snap_radius)
{
    Point mouse_point(x, y);
    double min_distance = snap_radius + 1;
    snap_point = nullptr;
    // Snap points
    for(std::vector<std::pair<Entity*,Point>>::iterator it=m_snap_points.begin(); it!=m_snap_points.end(); ++it)
    {
        double distance = Point::GetDistanceBetween(mouse_point, it->second);
        if(min_distance>distance)
        {
            min_distance = distance;
            snap_point = &it->second;
        }
    }
    // Center points
    for(std::vector<std::pair<Entity*,Point>>::iterator it=m_snap_center.begin(); it!=m_snap_center.end(); ++it)
    {
        double distance = Point::GetDistanceBetween(mouse_point, it->second);
        if(min_distance>distance)
        {
            min_distance = distance;
            snap_point = &it->second;
        }
    }

    if(min_distance<snap_radius + 1)
    {
        dc.CadSetColour(Colour(255, 0, 0));
        dc.CadDrawCircle(*snap_point, snap_radius);
    }
    dc.CadSetColour(Colour(255, 255, 255));

}

void DrawManager::AppendSnapPointsFor(Entity *entity)
{
    entity->GetSnapPoints(m_snap_points);
    entity->GetCenterPoints(m_snap_center);
}

Point* DrawManager::GetSnapPoint(void) const
{
    return snap_point;
}

void DrawManager::AssignDefaultPreferences()
{
    m_preferences = {
        {cad::preferences::PREF_GRID_SHOW, 1},
        {cad::preferences::PREF_SNAP_GRID, 0}
    };
}

bool DrawManager::HasPreference(const std::string &pref) const
{
    return m_preferences.find(pref)!=m_preferences.end();
}

void DrawManager::SetPreference(const std::string &pref, float val)
{
    m_preferences.insert(std::pair<std::string,float>(pref, val));
}
