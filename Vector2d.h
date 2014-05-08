#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>
#include <iosfwd>
#include <limits>

class Vector2d {

public:
	double x;
	double y;

	Vector2d() : x(0.0), y(0.0) {}
	Vector2d(double a, double b) : x(a), y(b) {}

	void zero() { 
		x = 0.0; 
		y=0.0;
	}

	bool is_zero() const { return (x*x + y*y) < 0; }

	inline double length() const;

	inline double length_sq() const;

	inline void normalize();

	inline double dot(const Vector2d& v2) const;

	inline int sign(const Vector2d& v2) const;

	inline Vector2d perp() const;

	inline void truncate(double max);

	inline double distance(const Vector2d &v2) const;

	inline double distance_sq(const Vector2d &v2) const;

	inline void reflect(const Vector2d& norm);

	inline Vector2d get_reverse() const;

	const Vector2d& operator+=(const Vector2d &rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	const Vector2d& operator-=(const Vector2d &rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	const Vector2d& operator*=(const double& rhs) {
		x *= rhs;
		y *= rhs;
		return *this;
	}

	const Vector2d& operator/=(const double& rhs) {
		x /= rhs;
		y /= rhs;
		return *this;
	}

	bool operator==(const Vector2d& rhs) const {
		return (rhs.x == 0) && (rhs.y ==0);
	}

	bool operator!=(const Vector2d& rhs) const {
		return (x != rhs.x) || (y != rhs.y);
	}
};

inline Vector2d operator*(const Vector2d &lhs, double rhs);
inline Vector2d operator*(double lhs, const Vector2d &rhs);
inline Vector2d operator-(const Vector2d &lhs, const Vector2d &rhs);
inline Vector2d operator+(const Vector2d &lhs, const Vector2d &rhs);
inline Vector2d operator/(const Vector2d &lhs, double val);
std::ostream& operator<<(std::ostream& os, const Vector2d& rhs);
std::ifstream& operator>>(std::ifstream& is, Vector2d& lhs);

inline double Vector2d::length() const {
	return sqrt(x*x + y*y);
}

inline double Vector2d::length_sq() const {
	return (x*x + y*y);
}

inline double Vector2d::dot(const Vector2d &v2) const {
	return x*v2.x + y*v2.y;
}

enum {clockwise = 1, anticlockwise = -1};

inline int Vector2d::sign(const Vector2d& v2) const {
	if (y*v2.x > x*v2.y) { 
		return anticlockwise;
	} else  {
		return clockwise;
	}
}

inline Vector2d Vector2d::perp() const {
	return Vector2d(-y, x);
}

inline double Vector2d::distance(const Vector2d &v2)const {
	double ySeparation = v2.y - y;
	double xSeparation = v2.x - x;
	return sqrt(ySeparation*ySeparation + xSeparation*xSeparation);
}

inline double Vector2d::distance_sq(const Vector2d &v2) const {
	double ySeparation = v2.y - y;
	double xSeparation = v2.x - x;
	return ySeparation*ySeparation + xSeparation*xSeparation;
}

inline void Vector2d::truncate(double max) {
	if (this->length() > max) {
		this->normalize();
		*this *= max;
	} 
}

inline void Vector2d::reflect(const Vector2d& norm) {
	*this += 2.0 * this->dot(norm) * norm.get_reverse();
}

inline Vector2d Vector2d::get_reverse()const {
	return Vector2d(-this->x, -this->y);
}

inline void Vector2d::normalize() { 
	double vector_length = this->length();

	if(vector_length > std::numeric_limits<double>::epsilon()) {
		this->x /= vector_length;
		this->y /= vector_length;
	}
}

inline Vector2d Vec2d_normalize(const Vector2d &v) {
	Vector2d vec = v;
	double vector_length = vec.length();

	if (vector_length > std::numeric_limits<double>::epsilon()) {
		vec.x /= vector_length;
		vec.y /= vector_length;
	}
	return vec;
}


inline double Vec2d_distance(const Vector2d &v1, const Vector2d &v2) {
	double ySeparation = v2.y - v1.y;
	double xSeparation = v2.x - v1.x;
	return sqrt(ySeparation*ySeparation + xSeparation*xSeparation);
}

inline double Vec2d_distance_sq(const Vector2d &v1, const Vector2d &v2) {
	double ySeparation = v2.y - v1.y;
	double xSeparation = v2.x - v1.x;
	return ySeparation*ySeparation + xSeparation*xSeparation;
}

inline double Vec2d_length(const Vector2d& v) {
	return sqrt(v.x*v.x + v.y*v.y);
}

inline double Vec2d_length_sq(const Vector2d& v) {
	return (v.x*v.x + v.y*v.y);
}

inline Vector2d operator*(const Vector2d &lhs, double rhs) {
	Vector2d result(lhs);
	result *= rhs;
	return result;
}

inline Vector2d operator*(double lhs, const Vector2d &rhs) {
	Vector2d result(rhs);
	result *= lhs;
	return result;
}

inline Vector2d operator-(const Vector2d &lhs, const Vector2d &rhs) {
	Vector2d result(lhs);
	result.x -= rhs.x;
	result.y -= rhs.y;
	return result;
}

inline Vector2d operator+(const Vector2d &lhs, const Vector2d &rhs) {
	Vector2d result(lhs);
	result.x += rhs.x;
	result.y += rhs.y;
	return result;
}

inline Vector2d operator/(const Vector2d &lhs, double val) {
	Vector2d result(lhs);
	result.x /= val;
	result.y /= val;
	return result;
}

#endif