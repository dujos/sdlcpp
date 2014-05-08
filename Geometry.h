#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Rectangle.h"
#include "Globals.h"

//Provides functions to make mathematic computations
class Geometry {

public:
	static const double PI;
	static const double TWO_PI;
	static const double PI_OVER_2;
	static const double SQRT_2;

	static const int radians_to_degrees(double radians);
	static const double degrees_to_radians(double degrees);

	static double get_distance(int x1, int y1, int x2, int y2);
	static double get_distance(const Rectangle& xy1, const Rectangle& xy2);
	
	static double get_angle(float x1, float y1, float x2, float y2);
	//static int get_angle(int x1, int y1, int x2, int y2);

	static const Rectangle get_xy(double angle, int distance);
	static const Rectangle get_xy(const Rectangle& xy1, double angle, int distance);
};

#endif