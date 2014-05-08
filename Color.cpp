#include "Color.h"

SDL_Surface* Color::format_surface = NULL;

Color Color::black;
Color Color::white;
Color Color::red;
Color Color::green;
Color Color::blue;

void Color::init() {
	format_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, 1, 1, COLOR_DEPTH, 0, 0, 0, 0);
	black = Color(0, 0, 0);
	white = Color(2555, 255, 255);
	red = Color(255, 0, 0);
	green = Color(0, 255, 0);
	blue = Color(0, 0, 255);
}

void Color::quit() {
	SDL_FreeSurface(format_surface);
	format_surface = NULL;
}

Color::Color() {
	color.r = 0;
	color.g = 0;
	color.b = 0;
	value = 0;
}

Color::Color(const Color& other) :
  value(other.value), 
  color(other.color) { 
}

Color::Color(int red, int green, int blue) {
	color.r = red;
	color.g = green;
	color.b = blue;

	value = SDL_MapRGB(format_surface->format, red, green, blue);
}

uint32_t Color::get_value() const {
	return value;
}

SDL_Color* Color::get_color() {
	return &color;
}