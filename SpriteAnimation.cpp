#include "Surface.h"
#include "SpriteAnimation.h"
#include "SpriteAnimationDirection.h"

SpriteAnimation::SpriteAnimation(const std::string& image, int nb_directions, 
	SpriteAnimationDirection** directions, uint32_t frame_delay, int loop_on_frame) :
  image_surface(NULL),
  image_loaded(false),
  nb_directions(nb_directions),
  loop_on_frame(loop_on_frame),
  directions(directions),
  frame_delay(frame_delay) {
	if(!image_loaded) {
        image_surface = new Surface(image);
	    image_loaded = true;
	}
}

SpriteAnimation::~SpriteAnimation() {
	for(int i = 0; i < nb_directions; i++) {
		delete directions[i];
	}
	delete [] directions;
	if(image_loaded)
        delete image_surface;
}

const SpriteAnimationDirection* SpriteAnimation::get_direction(int direction) const {
	return directions[direction];
}

int SpriteAnimation::get_next_frame(int current_direction, int current_frame) const{
	int next_frame = current_frame + 1;
	if(next_frame == directions[current_direction]->get_nb_frames()) {
		next_frame = loop_on_frame;
	}
	return next_frame;
}

/**
 * Return frame delay between two frames for this sprite animation.
 */
uint32_t SpriteAnimation::get_frame_delay() const {
	return frame_delay;
}

void SpriteAnimation::set_map(Map& map) {
	//TODO
}

void SpriteAnimation::display(Surface& dst_surface, const Rectangle& dst_position,
    int current_direction, int current_frame) {
	if(image_surface != NULL) {
		directions[current_direction]->display(dst_surface, dst_position, current_frame, *image_surface);
	}
}

