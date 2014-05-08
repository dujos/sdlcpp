#ifndef COUNTER_H
#define COUNTER_H

#include "Globals.h"
#include "Rectangle.h"
#include "Surface.h"

class Counter {

public:
	enum Style {BIG_DIGITS, SMALL_DIGITS};

private:
	Style style;
	unsigned int nb_digits;
	unsigned int maximum;
	unsigned int value;

	Surface surface_displayed;
	Rectangle dst_position;
	Surface image_digits;

	void rebuild(unsigned value);

public:
	Counter(unsigned int nb_digits, int x, int y);
	~Counter();

	void set_style(Style style);
	void set_value(unsigned int value);

	void display(Surface& dst_surface);
	void display(Surface& dst_surface, const Rectangle dst_position);

};


#endif