#ifndef COLOR_H
#define COLOR_H

#include <SDL.h>
#include "Globals.h"

class Color {
	friend class Surface;

private:
	static SDL_Surface* format_surface;
	uint32_t value;
	SDL_Color color; 

	//predefined colors
	static Color black;
	static Color white;
	static Color green;
	static Color red;
	static Color blue;

	uint32_t get_value() const;
	SDL_Color* get_color();

public:
	static void init();
	static void quit();

	static Color& get_black();
	static Color& get_white();
	static Color& get_green();
	static Color& get_red();
	static Color& get_blue();

	Color();
	Color(const Color& other);
	Color(int red, int green, int blue);

};

inline Color& Color::get_black() {
	return black;
}

inline Color& Color::get_white() {
	return white;
}

inline Color& Color::get_red() {
	return red;
}

inline Color& Color::get_green() {
	return green;
}

inline Color& Color::get_blue() {
	return blue;
}

#endif