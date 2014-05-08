#include "Vector2d.h"
#include <fstream>

std::ostream& operator<<(std::ostream& os, const Vector2d& rhs) {
	os << " " << rhs.x << " " << rhs.y;
	return os;
}

  
std::ifstream& operator>>(std::ifstream& is, Vector2d& lhs) {
	is >> lhs.x >> lhs.y;
	return is;
}

