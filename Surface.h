#ifndef SURFACE_H
#define SURFACE_H

#include <iostream>
#include "Displayable.h"
#include "Color.h"

class Surface : public Displayable {
	friend class VideoManager;

//protected:
public:
	void raw_display(Surface& dst_surface, const Rectangle& dst_position);

private:
	SDL_Surface* surface;           /* encapsulated surface */
	bool surface_loaded;            /* indicator if surface loaded */
	
public:
	SDL_Surface* get_surface();

	Surface(int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT);
	Surface(const std::string& file_name);
	Surface(SDL_Surface* surface);
	Surface(const Surface& other);
	~Surface();

	bool is_surface_loaded(const std::string& name);

	int get_width() const;
	int get_height() const;
	const Rectangle get_size() const;
	void set_size(int w, int h);

	void set_opacity(int opacity);
	void fill_with_color(Color color);

	void display(Surface& dst_surface);
	void display(Surface& dst_surface, Rectangle dst_position);

	void display_region(const Rectangle &src_position, Surface &dst_surface);
	void display_region(const Rectangle &src_position, Surface &dst_surface,
		                const Rectangle &dst_position);
};

#endif