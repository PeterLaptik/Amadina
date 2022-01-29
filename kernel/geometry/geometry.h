#ifndef CAD_GEOMETRY_H_INCLUDED
#define CAD_GEOMETRY_H_INCLUDED

namespace geometry {

	double calculate_angle(double x0, double y0, double x, double y);

	double calculate_distance(double x1, double y1, double x2, double y2);

	double calculate_distance(double x1, double y1, double z1,
                           double x2, double y2, double z2);
}

#endif
