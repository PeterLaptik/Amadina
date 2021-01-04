#include "drawmanager.h"
#include "default_commands.h"

static const int DEFAULT_GRID_STEP_BASE_NUMBER = 5;
static const float DEFAULT_PREFERENCE_EMPTY_VALUE = -1;

enum SnapType
{
    GRID,           // point on grid if it is shown
    POINT,          // constraint points of an entity
    CENTER,         // center of line, circle, square etc.
    INTERSECTION,   // intersection of two entities
    ORTHO           // orthogonal intersection of building entity and existing shape
};

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
    std::map<std::string,float>::iterator pref_iterator;

    Colour default_black(255,255,255);
    snap_point = nullptr;
    // Show grid if necessary
    pref_iterator = m_preferences.find(cad::preferences::PREF_GRID_SHOW);
    if((pref_iterator!=m_preferences.end())&&(static_cast<bool>(pref_iterator->second)==1))
        ShowGrid(dc);

    // Draw all entities
    for(std::vector<Entity*>::iterator it=m_elements.begin(); it!=m_elements.end(); ++it)
    {
        dc.CadSetColour(default_black);
        (*it)->Draw(dc);
    }
}

void DrawManager::ShowSnapPoints(IAdapterDC &dc, double x, double y, double snap_radius)
{
    SnapType snap_type;
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
            snap_type = POINT;
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
            snap_type = CENTER;
        }
    }

    // Find snap points among grid points
    // Apply snap only if grid is shown
    if((m_preferences.find(cad::preferences::PREF_SNAP_GRID)->second)&&(m_preferences.find(cad::preferences::PREF_GRID_SHOW)->second))
    {
        for(std::vector<Point>::iterator it=m_snap_grid.begin(); it!=m_snap_grid.end(); ++it)
        {
            double distance = Point::GetDistanceBetween(mouse_point, *it);
            if(min_distance>distance)
            {
                min_distance = distance;
                snap_point = &(*it);
                snap_type = POINT;
            }
        }
    }

    if(min_distance<snap_radius + 1)
    {
        dc.CadSetColour(Colour(255, 255, 0));
        switch(snap_type)
        {
        case POINT:
            {
                double sx = snap_point->GetX();
                double sy = snap_point->GetY();
                dc.CadDrawLine(Point(sx-snap_radius,sy-snap_radius),Point(sx+snap_radius,sy-snap_radius));
                dc.CadDrawLine(Point(sx-snap_radius,sy+snap_radius),Point(sx+snap_radius,sy+snap_radius));
                dc.CadDrawLine(Point(sx-snap_radius,sy-snap_radius),Point(sx-snap_radius,sy+snap_radius));
                dc.CadDrawLine(Point(sx+snap_radius,sy-snap_radius),Point(sx+snap_radius,sy+snap_radius));
                break;
            }
        case CENTER:
            {
                dc.CadDrawCircle(*snap_point, snap_radius);
                break;
            }
        }
    }
    dc.CadSetColour(Colour(255, 255, 255));

}

void DrawManager::AppendSnapPointsFor(Entity *entity)
{
    std::vector<Point> points;
    // Get constraint points
    entity->GetSnapPoints(points);
    for(std::vector<Point>::iterator it=points.begin(); it!=points.end(); ++it)
        m_snap_points.push_back(std::pair<Entity*,Point>(entity, *it));
    // Get center points
    points.clear();
    entity->GetCenterPoints(points);
    for(std::vector<Point>::iterator it=points.begin(); it!=points.end(); ++it)
        m_snap_center.push_back(std::pair<Entity*,Point>(entity, *it));
}

Point* DrawManager::GetSnapPoint(void) const
{
    return snap_point;
}

void DrawManager::ShowGrid(IAdapterDC &dc)
{
    double left, right, top, bottom;
    dc.GetBorders(&left, &right, &top, &bottom);
    // Smart scale and positioning
    double delta_x = (right - left);
    double delta_y = (top - bottom);
    double delta = delta_x < delta_y ? delta_x : delta_y;
    // Exponent for step base number
    int x_log = static_cast<int>(log10(right - left)) - 1;
    int y_log = static_cast<int>(log10(top - bottom)) - 1;
    int num_log = x_log < y_log ? x_log : y_log;
    // Step values
    double x_num = DEFAULT_GRID_STEP_BASE_NUMBER*pow(10,num_log);
    double y_num = DEFAULT_GRID_STEP_BASE_NUMBER*pow(10,num_log);
    // Start values for dots
    int x_multiplier = left/x_num;
    int y_multiplier = bottom/y_num;
    // Draw grid
    dc.CadSetColour(Colour(255, 255, 255));
    m_snap_grid.clear();
    bool snap_to_grid = m_preferences.find(cad::preferences::PREF_SNAP_GRID)->second;
    for(double i=x_num*x_multiplier; i<right; i+=x_num)
        for(double j=y_num*y_multiplier; j<top; j+=y_num)
        {
            Point pt(i,j);
            dc.CadDrawPoint(pt);
            if(snap_to_grid)
                m_snap_grid.push_back(pt);
        }
}

// Default preferences for a drawing
// Initial GUI controls states are to be synchronized width the default values
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
    std::map<std::string,float>::iterator it = m_preferences.find(pref);
    if(it==m_preferences.end())
        return;

    it->second = val;
}

float DrawManager::GetPreference(const std::string &pref) const
{
    float result = DEFAULT_PREFERENCE_EMPTY_VALUE;
    std::map<std::string,float>::const_iterator it = m_preferences.find(pref);
    if(it!=m_preferences.end())
        result = it->second;
    return result;
}
