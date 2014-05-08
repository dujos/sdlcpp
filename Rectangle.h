#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL.h>
#include <iostream>

class Rectangle {
	friend class Surface;

private:
	SDL_Rect rect;                   /* encapsulated SDL_Rect */
	SDL_Rect* get_rect();     

public:

	Rectangle(int x = 0, int y = 0, int w = 0, int h = 0);
	Rectangle(const Rectangle &other);
	~Rectangle();

	Rectangle& operator=(const Rectangle& rect);

	int get_x() const;
	int get_y() const;
	int get_width() const;
	int get_height() const;

	void set_x(int x_new);
	void set_y(int y_new);
	void set_width(int width_new);
	void set_height(int height_new);

	void set_xy(int x_new, int y_new);
	void set_xy(const Rectangle &rectangle);
	void set_size(int width_new, int height_new);
	void set_size(const Rectangle &other);

	void move_x(int dx);
	void move_y(int dy);
	void move_xy(int dx, int dy);
	void move_xy(const Rectangle &other);

	bool contains(int x, int y) const;
	bool contains(const Rectangle &other) const;
	bool overlaps(const Rectangle &other) const;
	Rectangle get_center();

	bool equals(const Rectangle &rectangle) const;
	bool equals_xy(const Rectangle &rectangle) const;
};

std::ostream& operator << (std::ostream& stream, const Rectangle &rectangle);

inline int Rectangle::get_x() const {
	return rect.x;
}

inline int Rectangle::get_y() const {
	return rect.y;
}

inline int Rectangle::get_width() const {
	return rect.w;
}

inline int Rectangle::get_height() const {
	return rect.h;
}

inline void Rectangle::set_x(int x_new) {
	rect.x = x_new;
}

inline void Rectangle::set_y(int y_new) {
	rect.y = y_new;
}

inline void Rectangle::set_width(int w_new) {
	rect.w = w_new;
}

inline void Rectangle::set_height(int h_new) {
	rect.h = h_new;
}

inline void Rectangle::set_xy(int x_new, int y_new) {
	set_x(x_new);
	set_y(y_new);
}

inline void Rectangle::set_xy(const Rectangle &rectangle) {
	set_xy(rectangle.get_x(), rectangle.get_y());
}

inline void Rectangle::set_size(int w_new, int h_new) {
	set_width(w_new);
	set_height(h_new);
}

inline void Rectangle::set_size(const Rectangle &rectangle) {
	set_size(rectangle.get_width(), rectangle.get_height());
}

inline void Rectangle::move_x(int dx) {
	set_x(get_x() + dx);
}

inline void Rectangle::move_y(int dy) {
	set_y(get_y() + dy);
}

inline void Rectangle::move_xy(int dx, int dy) {
	move_x(dx);
	move_y(dy);
}

inline void Rectangle::move_xy(const Rectangle &drectangle) {
	move_xy(drectangle.get_x(), drectangle.get_y());
}

/*
inline bool operator==(const Rectangle& lhs, const Rectangle& rhs);
inline bool operator==(const Rectangle& lhs, const Rectangle& rhs) {
	return lhs.get_x() == rhs.get_x() && lhs.get_y() == rhs.get_y() &&
		lhs.get_width() == rhs.get_width() && lhs.get_height() == rhs.get_height();
}

inline bool operator!=(const Rectangle& lhs, const Rectangle& rhs);
inline bool operator!=(const Rectangle& lhs, const Rectangle& rhs) {
	return !(lhs==rhs);
}
*/

//compare rectangles
inline bool Rectangle::equals(const Rectangle &rectangle) const {
	return this->equals_xy(rectangle) 
		   && rectangle.get_width() == this->get_width() 
		   && rectangle.get_height() == this->get_height();
}

//compare x and y values of rectangles
inline bool Rectangle::equals_xy(const Rectangle &rectangle) const {
	return rectangle.get_x() == this->get_x()
		   && rectangle.get_y() == this->get_y(); 
}

#endif