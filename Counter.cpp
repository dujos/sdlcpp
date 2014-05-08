#include "Counter.h"
#include "Color.h"
#include "Surface.h"

Counter::Counter(unsigned int nb_digits, int x, int y) :
  style(SMALL_DIGITS),
  nb_digits(nb_digits),
  maximum(999),
  surface_displayed(nb_digits * 8, 8),
  image_digits("digits.png") {
	surface_displayed.fill_with_color(Color::get_white());
	dst_position.set_xy(x, y);
}

Counter::~Counter() {}

void Counter::set_style(Style style) {
	if(this->style != style) {
		this->style = style;
		rebuild(0);
	}
}

void Counter::set_value(unsigned int value) {
	if(this->value != value) {
		this->value = value;
		rebuild(this->value);
	}
}

void Counter::rebuild(unsigned int value) {
	this->value = value;
	surface_displayed.fill_with_color(Color::get_white());
	
	Rectangle digit_src_position(0, 8, 8, 8);
	Rectangle digit_counter_position(0, 0, 8, 8);
	bool right_digit = true;

	for(int i = nb_digits; i >= 0; i--) {
		uint8_t digit = value % 10;
		value /= 10;
		if(value != 0 || digit != 0 || right_digit) {
			digit_src_position.set_x(digit * 8);
			digit_counter_position.set_x((i-1) * 8);

			image_digits.display_region(digit_src_position, surface_displayed, digit_counter_position);
			right_digit = false;
		}
	}
}

void Counter::display(Surface& dst_surface, const Rectangle dst_position) {
	surface_displayed.display(dst_surface, dst_position);
}

void Counter::display(Surface& dst_surface) {
	surface_displayed.display(dst_surface, dst_position);
}
