#include "Geometry.h"

#include <math.h>

//PI constant
const double Geometry::PI = 4 * std::atan(1.0);

const double Geometry::degrees_to_radians(double degrees) {
	return degrees * (PI / 180.0);
}

const int Geometry::radians_to_degrees(double radians) {
	return radians * (180.0 / PI);
}

//Return the distance between two points
double Geometry::get_distance(int x1, int y1, int x2, int y2) {
	int dx = x2 - x1;
	int dy = y2 - y1;
	return  std::sqrt((double) (dx * dx + dy * dy));
}

//Return the distance between two points
double Geometry::get_distance(const Rectangle& xy1, const Rectangle& xy2) {
	return get_distance(xy1.get_x(), xy1.get_y(), xy2.get_x(), xy2.get_y());
}

double Geometry::get_angle(float x1, float y1, float x2, float y2) {
	float dx = x2 - x1;
	float dy = y2 - y1;
	float angle;
    if(dx != 0) {
		angle =  std::atan((float) -dy / (float) dx);
		if (dx < 0) {
			angle += PI;
		}
	}
	else {
		angle = (dy > 0) ? -PI/2 : PI/2;
	}
	return angle;
}


//Returns the coordinates of a vector that starts from the origin
const Rectangle Geometry::get_xy(double angle, int distance) {
	return Rectangle((int) (distance * std::cos(angle)), (int) (-distance * std::sin(angle)));
}

const Rectangle Geometry::get_xy(const Rectangle& xy1, double angle, int distance) {
	Rectangle xy2 = get_xy(angle, distance);
	xy2.move_xy(xy1.get_x(), xy1.get_y());
	return xy2;
}