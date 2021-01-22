#include "drawmanager.h"
#include "default_commands.h"
#include "../geometry/intersections.h"
#include <algorithm>

// Each grid step value will be equal to base_number*10^x, where x = ... -2, -1, 0, 1, 2, ...
static const int DEFAULT_GRID_STEP_BASE_NUMBER = 5;

// Return value for preference if the one is not defined
static const float DEFAULT_PREFERENCE_EMPTY_VALUE = -1;

// Size multiplier value for snap symbols
static const float SNAP_SYMBOL_MULTIPLIER = 1.5;


enum SnapType
{
    GRID,           // point on grid if it is shown
    POINT,          // constraint points of an entity
    CENTER,         // center of line, circle, square etc.
    INTERSECTION,   // intersection of two entities
    ORTHO           // orthogonal intersection of building entity and existing shape
};

DrawManager::DrawManager()
        : m_snap_point(nullptr)
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
    // Find snap points for the entity
    AppendSnapPointsFor(entity);
}

void DrawManager::DrawAll(IAdapterDC &dc)
{
    std::map<std::string,float>::iterator pref_iterator;

    //Colour default_black(255,255,255);
    m_snap_point = nullptr;
    // Show grid if necessary
    pref_iterator = m_preferences.find(cad::preferences::PREF_GRID_SHOW);
    if((pref_iterator!=m_preferences.end())&&(static_cast<bool>(pref_iterator->second)==1))
        ShowGrid(dc);

    // Draw all entities
    for(std::vector<Entity*>::iterator it=m_elements.begin(); it!=m_elements.end(); ++it)
    {
        //dc.CadSetColour(default_black);
        (*it)->Draw(dc);
    }

    for(std::vector<Entity*>::iterator it=m_selected_entities.begin(); it!=m_selected_entities.end(); ++it)
        (*it)->DrawHighlighted(dc);
}

// Finds the best fit snap point.
// The method is called each time on screen redraw.
// Following sequence is being checked:
// - constraint points
// - center points
// - grid points
// Found point pointer is being kept in m_snap_point variable.
// The m_snap_point is equals to null-pointer if a snap is not found.
// dc - device context
// x, y - current mouse coordinates
// snap_radius - maximum distance between mouse pointer and snap point
void DrawManager::ShowSnapPoints(IAdapterDC &dc, double x, double y, double snap_radius)
{
    SnapType snap_type;
    Point mouse_point(x, y);
    double min_distance = snap_radius + 1;
    m_snap_point = nullptr;
    // Snap points
    if(m_preferences.find(cad::preferences::PREF_SNAP_POINT)->second)
    {
        for(std::vector<std::pair<Entity*,Point>>::iterator it=m_snap_points.begin(); it!=m_snap_points.end(); ++it)
        {
            double distance = Point::GetDistanceBetween(mouse_point, it->second);
            if(min_distance>distance)
            {
                min_distance = distance;
                m_snap_point = &it->second;
                snap_type = POINT;
            }
        }
    }
    // Snap center points
    if(m_preferences.find(cad::preferences::PREF_SNAP_CENTER)->second)
    {
        for(std::vector<std::pair<Entity*,Point>>::iterator it=m_snap_center.begin(); it!=m_snap_center.end(); ++it)
        {
            double distance = Point::GetDistanceBetween(mouse_point, it->second);
            if(min_distance>distance)
            {
                min_distance = distance;
                m_snap_point = &it->second;
                snap_type = CENTER;
            }
        }
    }
    // Intersection points
    if(m_preferences.find(cad::preferences::PREF_SNAP_INTERSECTION)->second)
    {
        for(std::vector<std::pair<std::pair<Entity*,Entity*>,Point>>::iterator it=m_snap_intersections.begin(); it!=m_snap_intersections.end(); ++it)
        {
            double distance = Point::GetDistanceBetween(mouse_point, it->second);
            if(min_distance>distance)
            {
                min_distance = distance;
                m_snap_point = &(it->second);
                snap_type = INTERSECTION;
            }
        }
    }
    // Find snap points among grid points
    // Apply snap if grid is shown
    if((m_preferences.find(cad::preferences::PREF_SNAP_GRID)->second)&&(m_preferences.find(cad::preferences::PREF_GRID_SHOW)->second))
    {
        for(std::vector<Point>::iterator it=m_snap_grid.begin(); it!=m_snap_grid.end(); ++it)
        {
            double distance = Point::GetDistanceBetween(mouse_point, *it);
            if(min_distance>distance)
            {
                min_distance = distance;
                m_snap_point = &(*it);
                snap_type = POINT;
            }
        }
    }
    // Draw snap symbol
    if(min_distance<snap_radius + 1)
    {
        dc.CadSetColour(Colour(255, 255, 0));
        switch(snap_type)
        {
        case POINT:
            {
                double sx = m_snap_point->GetX();
                double sy = m_snap_point->GetY();
                dc.CadDrawLine(Point(sx-snap_radius,sy-snap_radius),Point(sx+snap_radius,sy-snap_radius));
                dc.CadDrawLine(Point(sx-snap_radius,sy+snap_radius),Point(sx+snap_radius,sy+snap_radius));
                dc.CadDrawLine(Point(sx-snap_radius,sy-snap_radius),Point(sx-snap_radius,sy+snap_radius));
                dc.CadDrawLine(Point(sx+snap_radius,sy-snap_radius),Point(sx+snap_radius,sy+snap_radius));
                break;
            }
        case CENTER:
            {
                dc.CadDrawCircle(*m_snap_point, snap_radius);
                break;
            }
        case INTERSECTION:
            {
                dc.CadDrawLine(Point(m_snap_point->GetX()-snap_radius, m_snap_point->GetY()-snap_radius),
                               Point(m_snap_point->GetX()+snap_radius, m_snap_point->GetY()+snap_radius));
                dc.CadDrawLine(Point(m_snap_point->GetX()-snap_radius, m_snap_point->GetY()+snap_radius),
                               Point(m_snap_point->GetX()+snap_radius, m_snap_point->GetY()-snap_radius));
                dc.CadDrawLine(Point(m_snap_point->GetX()-snap_radius*SNAP_SYMBOL_MULTIPLIER, m_snap_point->GetY()),
                               Point(m_snap_point->GetX()+snap_radius*SNAP_SYMBOL_MULTIPLIER, m_snap_point->GetY()));
                dc.CadDrawLine(Point(m_snap_point->GetX(), m_snap_point->GetY()+snap_radius*SNAP_SYMBOL_MULTIPLIER),
                               Point(m_snap_point->GetX(), m_snap_point->GetY()-snap_radius*SNAP_SYMBOL_MULTIPLIER));
                break;
            }
        }
    }
    dc.CadSetColour(Colour(255, 255, 255));
}

// Highlight the nearest entity to the mouse pointer
void DrawManager::ShowSnapEntities(IAdapterDC &dc, double x, double y, double snap_radius)
{
    Point pt(x,y);
    m_selecting_entity = nullptr;
    double min_distance = std::numeric_limits<double>::max();
    double distance = std::numeric_limits<double>::max();
    for(std::vector<Entity*>::iterator it=m_elements.begin(); it!=m_elements.end(); ++it)
    {
        distance = (*it)->DistanceFrom(pt);
        if(distance<min_distance)
        {
            min_distance = distance;
            m_selecting_entity = *it;
        }
    }
    if(min_distance<snap_radius)
    {
        m_selecting_entity->DrawHighlighted(dc);
    }
}

void DrawManager::SelectInPoint(double x, double y, double snap_radius)
{
    Point pt(x,y);
    m_selecting_entity = nullptr;
    double min_distance = std::numeric_limits<double>::max();
    double distance = std::numeric_limits<double>::max();
    for(std::vector<Entity*>::iterator it=m_elements.begin(); it!=m_elements.end(); ++it)
    {
        distance = (*it)->DistanceFrom(pt);
        if(distance<min_distance)
        {
            min_distance = distance;
            m_selecting_entity = *it;
        }
    }
    if(min_distance<snap_radius)
        m_selected_entities.push_back(m_selecting_entity);
}

void DrawManager::ClearSelection()
{
    m_selected_entities.clear();
}

void DrawManager::DeleteSelection()
{
    Entity *item_ptr = nullptr;
    if(m_selected_entities.empty())
        return;
    // Delete selected items
    for(std::vector<Entity*>::iterator it=m_selected_entities.begin(); it!=m_selected_entities.end(); ++it)
    {
        // Delete entity itself
        item_ptr = *it;
        m_elements.erase(std::remove_if(m_elements.begin(), m_elements.end(),
                        [item_ptr](Entity *x)
                        {
                            if(x==item_ptr)
                                return true;
                            else
                                return false;
                        }),
                        m_elements.end());

        delete item_ptr;
        // Remove cache data
        RemoveSnapPointsFor(item_ptr);
    }
    // Clear selection
    m_selected_entities.clear();
}

// Finds snap points and appends them into a lists.
// Snap points are found once when an entity is being appended.
void DrawManager::AppendSnapPointsFor(Entity *entity)
{
    std::vector<Point> points;              // found points
    std::vector<Entity*> primitives;        // primitives of the entity
    std::vector<Entity*> primitives_ext;    // primitives of existing entity

    // Get constraint points
    entity->GetSnapPoints(points);
    for(std::vector<Point>::iterator it=points.begin(); it!=points.end(); ++it)
        m_snap_points.push_back(std::pair<Entity*,Point>(entity, *it));

    // Get center points
    points.clear();
    entity->GetCenterPoints(points);
    for(std::vector<Point>::iterator it=points.begin(); it!=points.end(); ++it)
        m_snap_center.push_back(std::pair<Entity*,Point>(entity, *it));

    // Get entities intersections
    for(std::vector<Entity*>::iterator it=m_elements.begin(); it!=m_elements.end(); ++it)
    {
        if(*it==entity)
            continue;

        primitives.clear();
        primitives_ext.clear();
        entity->GetPrimitives(primitives);
        (*it)->GetPrimitives(primitives_ext);
        // Iterate over all sub-entities of appending item and sub-entities of overall existing items
        for(std::vector<Entity*>::iterator it_prim=primitives.begin(); it_prim!=primitives.end(); ++it_prim)
        {
            for(std::vector<Entity*>::iterator it_ext=primitives_ext.begin(); it_ext!=primitives_ext.end(); ++it_ext)
            {
                points.clear();
                cad::geometry::calculate_intersections((*it_ext), (*it_prim), points);
                // Write intersections points
                for(std::vector<Point>::iterator it_point=points.begin(); it_point!=points.end(); ++it_point)
                    m_snap_intersections.push_back(std::pair<std::pair<Entity*,Entity*>,Point>(std::pair<Entity*,Entity*>(*it, entity), *it_point));
            }
        }
    }
}

// Deletes snap points related to the entity
void DrawManager::RemoveSnapPointsFor(Entity *entity)
{
    // Intersections points
    m_snap_intersections.erase(std::remove_if(m_snap_intersections.begin(), m_snap_intersections.end(),
                                [entity](std::pair<std::pair<Entity*,Entity*>,Point> x)
                                {
                                    if((x.first.first==entity)||(x.first.second==entity))
                                        return true;
                                    else
                                        return false;
                                }),
                                m_snap_intersections.end());
    // Center points
    m_snap_center.erase(std::remove_if(m_snap_center.begin(), m_snap_center.end(),
                                [entity](std::pair<Entity*,Point> x)
                                {
                                    if(x.first==entity)
                                        return true;
                                    else
                                        return false;
                                }),
                                m_snap_center.end());
    // Snap points
    m_snap_points.erase(std::remove_if(m_snap_points.begin(), m_snap_points.end(),
                                [entity](std::pair<Entity*,Point> x)
                                {
                                    if(x.first==entity)
                                        return true;
                                    else
                                        return false;
                                }),
                                m_snap_points.end());
}

Point* DrawManager::GetSnapPoint(void) const
{
    return m_snap_point;
}

void DrawManager::ShowGrid(IAdapterDC &dc)
{
    double left, right, top, bottom;
    dc.GetBorders(&left, &right, &top, &bottom);
    // Smart scale and positioning
    // Exponent for step base number
    int x_log = static_cast<int>(log10(right - left)) - 1;
    int y_log = static_cast<int>(log10(top - bottom)) - 1;
    int num_log = x_log < y_log ? x_log : y_log;
    // Step values
    double x_step = DEFAULT_GRID_STEP_BASE_NUMBER*pow(10,num_log);
    double y_step = DEFAULT_GRID_STEP_BASE_NUMBER*pow(10,num_log);
    // Start values for dots
    int x_multiplier = left/x_step;
    int y_multiplier = bottom/y_step;
    // Draw grid
    dc.CadSetColour(Colour(255, 255, 255));
    m_snap_grid.clear();
    bool snap_to_grid = m_preferences.find(cad::preferences::PREF_SNAP_GRID)->second;
    for(double i=x_step*x_multiplier; i<right; i+=x_step)
        for(double j=y_step*y_multiplier; j<top; j+=y_step)
        {
            Point pt(i,j);
            dc.CadDrawPoint(pt);
            if(snap_to_grid)
                m_snap_grid.push_back(pt);
        }
}

// Default preferences for a drawing
// Initial GUI controls states are to be synchronized with the default values
void DrawManager::AssignDefaultPreferences()
{
    m_preferences = {
        {cad::preferences::PREF_GRID_SHOW, 1},
        {cad::preferences::PREF_SNAP_GRID, 0},
        {cad::preferences::PREF_SNAP_POINT, 1},
        {cad::preferences::PREF_SNAP_CENTER, 1},
        {cad::preferences::PREF_SNAP_INTERSECTION, 1},
        {cad::preferences::PREF_SNAP_ORTHO, 1},
        {cad::preferences::PREF_SNAP_TANGENT, 1},
        {cad::preferences::PREF_SNAP_ANGLE, 1}
    };
}

bool DrawManager::HasPreference(const std::string &pref) const
{
    return m_preferences.find(pref)!=m_preferences.end();
}

//Sets preference value
//pref -- preference name
//val - value to set
void DrawManager::SetPreference(const std::string &pref, float val)
{
    std::map<std::string,float>::iterator it = m_preferences.find(pref);
    if(it==m_preferences.end())
        return;

    it->second = val;
}

// Returns preference value if has been found
float DrawManager::GetPreference(const std::string &pref) const
{
    float result = DEFAULT_PREFERENCE_EMPTY_VALUE;
    std::map<std::string,float>::const_iterator it = m_preferences.find(pref);
    if(it!=m_preferences.end())
        result = it->second;
    return result;
}
