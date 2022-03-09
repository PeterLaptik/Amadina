#ifndef CAD_GEOMETRY_H_INCLUDED
#define CAD_GEOMETRY_H_INCLUDED

#include "../api/exports.h"

namespace geometry {

    ///\brief Calculates angle of point (x,y) in coordinates system centered in point (x0,y0)
    /// Following scheme shows angles values on a flat surface:
    ///
    ///                     90 deg.
    ///                       |
    ///                       |
    ///   180 deg. --------(x0,y0)--------- 0 deg.
    ///                       |
    ///                       |
    ///                     270 deg.
    ///
    ///\param x0 - coordinate system ceneter's x
    ///\param y0 - coordinate system ceneter's y
    ///\param x - point's x
    ///\param y - point's y
    ///\return angle value in degrees, always positive. See scheme above
	double DLL_EXPORT calculate_angle(double x0, double y0, double x, double y);


    ///\brief Calculates angle of point (x,y) in coordinates system centered in point (x0,y0)
    ///\param x0 - coordinate system ceneter's x
    ///\param y0 - coordinate system ceneter's y
    ///\param x - point's x
    ///\param y - point's y
    ///\return angle value in radians
	double DLL_EXPORT calculate_angle_rad(double x0, double y0, double x, double y);


	///\brief Calculates distance between two points with coordinates [x1,y1] and [x2,y2]
    ///\param x1, y1 - first point coordinates
    ///\param x2, y2 - second point coordinate
	double DLL_EXPORT calculate_distance(double x1, double y1, double x2, double y2);


	///\brief Calculates distance between two points with coordinates [x1,y1,z1] and [x2,y2,z2]
    ///\param x1, y1, z1 - first point coordinates
    ///\param x2, y2, z2 - second point coordinate
	double DLL_EXPORT calculate_distance(double x1, double y1, double z1,
                           double x2, double y2, double z2);


    ///\brief Calculates center point on the line
    ///\param x1, y1 - first line point coordinates
    ///\param x2, y2 - second line point coordinates
    ///\param xc, yc - center point coordinates values (result)
    void DLL_EXPORT calculate_center_point(double x1, double y1, double x2, double y2,
                                             double &xc, double &yc);
}

#endif
