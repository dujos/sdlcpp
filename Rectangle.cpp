#include "Rectangle.h"

//ctor
Rectangle::Rectangle(int x, int y, int w, int h) {
	rect.x = x;
	rect.y = y;
	rect.h = h;
	rect.w = w;
}

//copy ctor
Rectangle::Rectangle(const Rectangle &rectangle) :
    rect(rectangle.rect) {}

//destructor
Rectangle::~Rectangle() {}

Rectangle& Rectangle::operator=(const Rectangle& other) {
	if (this != &other)
		this->rect = other.rect;
	return *this;
}

//is the point inside rectangle
bool Rectangle::contains(int x, int y) const {
	return x >= this->get_x() && x <= this->get_x() + this->get_width()
		   && y >= this->get_y() && y <= this->get_y() + this->get_height();
}

//is rectangle inside rectangle
bool Rectangle::contains(const Rectangle &rectangle) const {
	return this->contains(rectangle.get_x(), rectangle.get_y())
		   && this->contains(rectangle.get_x() + rectangle.get_width(),
		   rectangle.get_y() + rectangle.get_height());
}

//are rectangles overlapping
bool Rectangle::overlaps(const Rectangle &rectangle) const {
	int x1 = rectangle.get_x();
	int x2 = x1 + rectangle.get_width();
	int x3 = this->get_x();
	int x4 = x3 + this->get_width();

	bool overlap_x = (x1 < x4 && x3 < x2);

	int y1 = rectangle.get_y();
	int y2 = y1 + rectangle.get_width();
	int y3 = this->get_y();
	int y4 = y3 + this->get_width();

	bool overlap_y = (y1 < y4 && y3 < y2);

	return overlap_x && overlap_y;
}

//return center point of rectangle
Rectangle Rectangle::get_center() {
	return Rectangle(this->get_x() + this->get_width()/2, 
		              this->get_y() + this->get_height()/2);
}

std::ostream& operator << (std::ostream &stream, const Rectangle &rectangle) {
	return stream << "(" << rectangle.get_x() << ", " << rectangle.get_y() << ", "
		          << rectangle.get_width() << ", " << rectangle.get_height() << ")";
}

SDL_Rect* Rectangle::get_rect() {
	return &rect;
}