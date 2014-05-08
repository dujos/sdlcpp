#ifndef SPRITE_ANIMATION_DIRECTION_H
#define SPRITE_ANIMATION_DIRECTION_H

#include "Rectangle.h"
#include "Surface.h"

/**
 * A sequence of frames representing a sprite animated in a specific direction.
 * Animation direction is a sequence of frames representing a sprite with 
 * a specific animation and a specific direction. 
 */
class SpriteAnimationDirection {

private:
	const int nb_frames;		/** number of frames in this sequence */
	Rectangle origin;
	Rectangle* frames;

public:
	SpriteAnimationDirection(int nb_frames, Rectangle* frames,
		int origin_x, int origin_y);
	virtual ~SpriteAnimationDirection();

	//properties
	const Rectangle& get_size() const;
	const Rectangle& get_origin() const;
	int get_nb_frames() const;
	const Rectangle& get_frame(int frame) const;

	void display(Surface& dst_surface, const Rectangle& dst_position,
		int current_frame, Surface& src_image);

};


#endif