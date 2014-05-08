#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include "Surface.h"
#include "Map.h"

#include <string>

class SpriteAnimation {

private:
	Surface* image_surface;
	bool image_loaded;

	int nb_directions;
	const int loop_on_frame;
	const uint32_t frame_delay;
	
	SpriteAnimationDirection** directions;

public:
	SpriteAnimation(const std::string& image, int nb_directions, 
		SpriteAnimationDirection** directions, uint32_t frame_interval, int loop_on_frame);
	~SpriteAnimation();

	const SpriteAnimationDirection* get_direction(int direction) const;
	int get_next_frame(int current_direction, int current_frame) const;
	uint32_t get_frame_delay() const; 

	void set_map(Map& map);

	void display(Surface& dst_surface, const Rectangle& dst_position,
		int current_direction, int current_frame);
};
#endif