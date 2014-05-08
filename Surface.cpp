#include "Surface.h"

//Create an empty surface wit specified size.
Surface::Surface(int width, int height) :
  Displayable(),
  surface_loaded(true) {
	  this->surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0, 0, 0, 0);
}

//Create a surface from a specified image file.
Surface::Surface(const std::string& file_name) :
 Displayable(),
 surface_loaded(true) {
	this->surface = IMG_Load(file_name.c_str());
	//is_surface_loaded(file_name.c_str());
}

//Creates a surface from the specified SDL surface.
Surface::Surface(SDL_Surface* surface) :
  Displayable(),
  surface(surface),
  surface_loaded(false) {
}

Surface::Surface(const Surface& other) :
  Displayable(),
  surface(SDL_ConvertSurface(other.surface, other.surface->format, other.surface->flags)),
  surface_loaded(true) {
}

//Destructors
Surface::~Surface() {
	if(surface_loaded) {
		SDL_FreeSurface(surface);
	}
}

bool Surface::is_surface_loaded(const std::string& name) {
	if(name.size() > 0) {
		if(surface == NULL) {
			std::cout << name.c_str() << "Load Image Failed!" << std::endl;
			return false;
		}
		std::cout << name.c_str() << "Load Image Success!" << std::endl;
		return true;
	}
}

//Returns the width of the surface.
int Surface::get_width() const {
	return surface->w;
}

//Returns the height of the surface.
int Surface::get_height() const {
	return surface->h;
}

//Return the size of this surface.
const Rectangle Surface::get_size() const {
	return Rectangle(0, 0, get_width(), get_height());
}

void Surface::set_size(int w, int h) {
	surface->w = w;
	surface->h = h;
}

void Surface::set_opacity(int opacity) {
	SDL_SetAlpha(this->surface, SDL_SRCALPHA, opacity);
}

//Fills the entire surface.
void Surface::fill_with_color(Color color) {
	SDL_FillRect(surface, NULL, color.get_value());
}

void Surface::display(Surface& dst_surface) {
	raw_display(dst_surface, Rectangle(0, 0));
}

void Surface::display(Surface& dst_surface, Rectangle dst_position) {
	raw_display(dst_surface, dst_position);
}

//Blits this surface on another surface.
void Surface::raw_display(Surface& dst_surface, 
	const Rectangle& dst_position) {
    Rectangle dst_position2(dst_position);
	SDL_BlitSurface(surface, NULL, dst_surface.surface, dst_position2.get_rect());
}

//Blits a region of this surface on another surface.
void Surface::display_region(const Rectangle& src_position,
	Surface& dst_surface) {
    Rectangle src_position2(src_position);
	SDL_BlitSurface(surface, src_position2.get_rect(), dst_surface.surface, NULL);
}

//Blits a region of this surface on a specified location of another surface.
void Surface::display_region(const Rectangle &src_position, Surface &dst_surface,
	const Rectangle &dst_position) {
	Rectangle src_position2(src_position);
	Rectangle dst_position2(dst_position);
    SDL_BlitSurface(surface, src_position2.get_rect(), dst_surface.surface, dst_position2.get_rect());
}

//Returns the SDL surface encapsulated by this object.
SDL_Surface* Surface::get_surface() {
	return surface;
}