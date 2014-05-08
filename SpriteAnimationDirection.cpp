#include "Surface.h"
#include "SpriteAnimationDirection.h"

SpriteAnimationDirection::SpriteAnimationDirection(int nb_frames, Rectangle* frames, 
    int origin_x, int origin_y) :
  nb_frames(nb_frames),
  frames(frames) {
	origin.set_xy(origin_x, origin_y);
}

SpriteAnimationDirection::~SpriteAnimationDirection() {
	delete[] frames;
}

const Rectangle& SpriteAnimationDirection::get_size() const {
	return frames[0];
}

const Rectangle& SpriteAnimationDirection::get_origin() const {
	return origin;
}

int SpriteAnimationDirection::get_nb_frames() const {
	return nb_frames;
}

const Rectangle& SpriteAnimationDirection::get_frame(int frame) const {
	if(frame < 0 || frame > get_nb_frames())
		frame = 0;
	return frames[frame];
}

void SpriteAnimationDirection::display(Surface& dst_surface, const Rectangle& dst_position,
	int current_frame, Surface& src_image) {

	const Rectangle& current_frame_rec = get_frame(current_frame);
	Rectangle position(dst_position);
	position.move_xy(-origin.get_x(), -origin.get_y());
	position.set_size(current_frame_rec);
	
	src_image.display_region(current_frame_rec, dst_surface, position);
}
  